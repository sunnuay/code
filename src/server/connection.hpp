#pragma once
#include "http_parser.hpp"
#include "router.hpp"
#include <asio.hpp>
#include <memory>

using asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection> {
public:
  Connection(tcp::socket socket, std::shared_ptr<Router> router);
  void start();

private:
  asio::awaitable<void> process_request();

  tcp::socket socket_;
  std::shared_ptr<Router> router_;
  HttpParser parser_;
  char buffer_[4096];
};
