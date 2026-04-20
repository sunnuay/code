#pragma once
#include "pg_connection.hpp"
#include <asio.hpp>
#include <asio/experimental/channel.hpp>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class PgPool : public std::enable_shared_from_this<PgPool> {
public:
  PgPool(asio::io_context &io, const std::string &conninfo, size_t pool_size)
      : io_context_(io), conninfo_(conninfo), pool_size_(pool_size), channel_(io, pool_size) {}

  asio::awaitable<void> init() {
    for (size_t i = 0; i < pool_size_; ++i) {
      auto conn = std::make_unique<PgConnection>(io_context_);
      co_await conn->connect(conninfo_);
      channel_.try_send(asio::error_code{}, conn.get());
      connections_.push_back(std::move(conn));
    }
  }

  using PgSession = std::unique_ptr<PgConnection, std::function<void(PgConnection *)>>;
  asio::awaitable<PgSession> acquire() {
    PgConnection *raw = co_await channel_.async_receive(asio::use_awaitable);
    auto self = shared_from_this();
    co_return PgSession(raw, [self](PgConnection *c) { self->release(c); });
  }

private:
  void release(PgConnection *c) { channel_.try_send(asio::error_code{}, c); }

  asio::io_context &io_context_;
  std::string conninfo_;
  size_t pool_size_;
  std::vector<std::unique_ptr<PgConnection>> connections_;
  asio::experimental::channel<void(asio::error_code, PgConnection *)> channel_;
};
