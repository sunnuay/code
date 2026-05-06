#include "pg_connection.hpp"
#include <libpq-fe.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

PgConnection::PgConnection(asio::io_context &io_context) : socket_desc_(io_context) {}

PgConnection::~PgConnection() {
  if (socket_desc_.is_open()) {
    socket_desc_.release();
  }
  PQfinish(conn_);
}

asio::awaitable<void> PgConnection::wait_read() {
  co_await socket_desc_.async_wait(asio::posix::descriptor_base::wait_read, asio::use_awaitable);
}

asio::awaitable<void> PgConnection::wait_write() {
  co_await socket_desc_.async_wait(asio::posix::descriptor_base::wait_write, asio::use_awaitable);
}

asio::awaitable<void> PgConnection::connect(const std::string &conninfo) {
  conn_ = PQconnectStart(conninfo.c_str());
  if (PQstatus(conn_) == CONNECTION_BAD) {
    throw std::runtime_error(PQerrorMessage(conn_));
  }

  int fd = PQsocket(conn_);
  socket_desc_.assign(fd);

  while (true) {
    PostgresPollingStatusType status = PQconnectPoll(conn_);
    if (status == PGRES_POLLING_OK) {
      break;
    } else if (status == PGRES_POLLING_READING) {
      co_await wait_read();
    } else if (status == PGRES_POLLING_WRITING) {
      co_await wait_write();
    } else if (status == PGRES_POLLING_FAILED) {
      throw std::runtime_error(PQerrorMessage(conn_));
    }
  }
}

asio::awaitable<std::vector<std::vector<std::string>>> PgConnection::query(const std::string &sql) {
  if (!PQsendQuery(conn_, sql.c_str())) {
    throw std::runtime_error(PQerrorMessage(conn_));
  }

  while (true) {
    PQconsumeInput(conn_);
    if (PQisBusy(conn_)) {
      co_await wait_read();
    } else {
      break;
    }
  }

  std::vector<std::vector<std::string>> rows;
  PGresult *res;
  while ((res = PQgetResult(conn_)) != nullptr) {
    ExecStatusType status = PQresultStatus(res);
    if (status != PGRES_TUPLES_OK && status != PGRES_COMMAND_OK) {
      PQclear(res);
      throw std::runtime_error(PQerrorMessage(conn_));
    }

    int n_rows = PQntuples(res);
    int n_cols = PQnfields(res);

    for (int i = 0; i < n_rows; ++i) {
      std::vector<std::string> row;
      for (int j = 0; j < n_cols; ++j) {
        row.push_back(PQgetvalue(res, i, j));
      }
      rows.push_back(std::move(row));
    }
    PQclear(res);
  }
  co_return rows;
}
