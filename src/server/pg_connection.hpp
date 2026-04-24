#pragma once
#include <asio.hpp>
#include <libpq-fe.h>
#include <string>
#include <vector>

class PgConnection {
public:
  PgConnection(asio::io_context &io_context);
  ~PgConnection();

  asio::awaitable<void> connect(const std::string &conninfo);
  asio::awaitable<std::vector<std::vector<std::string>>> query(const std::string &sql,
                                                               const std::vector<std::string> &params = {});

private:
  asio::awaitable<void> wait_read();
  asio::awaitable<void> wait_write();

  asio::posix::stream_descriptor socket_desc_;
  PGconn *conn_ = nullptr;
};
