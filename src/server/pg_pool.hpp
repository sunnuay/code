#pragma once
#include "pg_connection.hpp"
#include <asio.hpp>
#include <asio/experimental/channel.hpp>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

class PgPool {
public:
  PgPool(asio::io_context &io, const std::string &conninfo, size_t pool_size)
      : io_context_(io), conninfo_(conninfo), pool_size_(pool_size), channel_(io, pool_size) {}

  asio::awaitable<void> init() {
    for (size_t i = 0; i < pool_size_; ++i) {
      auto conn = std::make_shared<PgConnection>(io_context_);
      co_await conn->connect(conninfo_);
      channel_.try_send(asio::error_code{}, conn);
    }
  }

  asio::awaitable<std::shared_ptr<PgConnection>> acquire() {
    co_return co_await channel_.async_receive(asio::use_awaitable);
  }

  void release(std::shared_ptr<PgConnection> conn) { channel_.try_send(asio::error_code{}, conn); }

private:
  asio::io_context &io_context_;
  std::string conninfo_;
  size_t pool_size_;
  asio::experimental::channel<void(asio::error_code, std::shared_ptr<PgConnection>)> channel_;
};

class PgConnectionGuard {
public:
  PgConnectionGuard(std::shared_ptr<PgPool> pool, std::shared_ptr<PgConnection> conn)
      : pool_(std::move(pool)), conn_(std::move(conn)) {}

  ~PgConnectionGuard() {
    if (pool_ && conn_) {
      pool_->release(conn_);
    }
  }

  PgConnection *operator->() { return conn_.get(); }

private:
  std::shared_ptr<PgPool> pool_;
  std::shared_ptr<PgConnection> conn_;
};
