#include "server.hpp"
#include "connection.hpp"
#include "router.hpp"
#include <asio.hpp>
#include <exception>
#include <memory>
#include <print>
#include <utility>

Server::Server(asio::io_context &io_context, short port, std::shared_ptr<Router> router)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), router_(std::move(router)) {}

void Server::start() { asio::co_spawn(acceptor_.get_executor(), accept_loop(), asio::detached); }

void Server::stop() { acceptor_.close(); }

asio::awaitable<void> Server::accept_loop() {
  try {
    while (true) {
      tcp::socket socket = co_await acceptor_.async_accept(asio::use_awaitable);
      std::make_shared<Connection>(std::move(socket), router_)->start();
    }
  } catch (const std::exception &e) {
    std::println("Server: {}", e.what());
  }
}
