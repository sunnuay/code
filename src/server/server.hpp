#pragma once
#include "router.hpp"
#include <asio.hpp>
#include <memory>

using asio::ip::tcp;

class Server {
public:
  Server(asio::io_context &io_context, short port,
         std::shared_ptr<Router> router);
  void start();

private:
  asio::awaitable<void> accept_loop();

  tcp::acceptor acceptor_;
  std::shared_ptr<Router> router_;
};
