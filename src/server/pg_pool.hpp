#pragma once
#include "pg_connection.hpp"
#include <asio.hpp>
#include <asio/experimental/channel.hpp>
#include <memory>

class PgPool : public std::enable_shared_from_this<PgPool> {
public:
  class ConnectionProxy {
  public:
    ConnectionProxy(std::shared_ptr<PgPool> pool, std::shared_ptr<PgConnection> conn)
        : pool_(std::move(pool)), conn_(std::move(conn)) {}

    ~ConnectionProxy() {
      if (pool_ && conn_) {
        pool_->release(conn_);
      }
    }

    ConnectionProxy(ConnectionProxy &&) = default;
    ConnectionProxy &operator=(ConnectionProxy &&) = default;
    ConnectionProxy(const ConnectionProxy &) = delete;
    ConnectionProxy &operator=(const ConnectionProxy &) = delete;

    PgConnection *operator->() { return conn_.get(); }

  private:
    std::shared_ptr<PgPool> pool_;
    std::shared_ptr<PgConnection> conn_;
  };

  PgPool(asio::io_context &io, const std::string &conninfo, size_t pool_size)
      : io_context_(io), conninfo_(conninfo), pool_size_(pool_size), channel_(io, pool_size) {}

  asio::awaitable<void> init() {
    for (size_t i = 0; i < pool_size_; ++i) {
      auto conn = std::make_shared<PgConnection>(io_context_);
      co_await conn->connect(conninfo_);
      channel_.try_send(asio::error_code{}, conn);
    }
  }

  asio::awaitable<ConnectionProxy> acquire() {
    auto conn = co_await channel_.async_receive(asio::use_awaitable);
    co_return ConnectionProxy(shared_from_this(), std::move(conn));
  }

  void release(std::shared_ptr<PgConnection> conn) { channel_.try_send(asio::error_code{}, conn); }

private:
  asio::io_context &io_context_;
  std::string conninfo_;
  size_t pool_size_;
  asio::experimental::channel<void(asio::error_code, std::shared_ptr<PgConnection>)> channel_;
};
