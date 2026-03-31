#include "server.hpp"
#include "connection.hpp"
#include <iostream>

Server::Server(asio::io_context &io_context, short port,
               std::shared_ptr<Router> router)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      router_(std::move(router)) {}

void Server::start() {
  asio::co_spawn(acceptor_.get_executor(), accept_loop(), asio::detached);
}

asio::awaitable<void> Server::accept_loop() {
  try {
    while (true) {
      // 异步 Accept 协程
      tcp::socket socket = co_await acceptor_.async_accept(asio::use_awaitable);

      // 接入新连接，创建 Connection 对象并启动处理协程
      std::make_shared<Connection>(std::move(socket), router_)->start();
    }
  } catch (const std::exception &e) {
    std::cerr << "Server accept error: " << e.what() << "\n";
  }
}
