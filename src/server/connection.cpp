#include "connection.hpp"
#include "http_message.hpp"
#include "router.hpp"
#include <asio.hpp>
#include <cstddef>
#include <exception>
#include <memory>
#include <string>
#include <utility>

Connection::Connection(tcp::socket socket, std::shared_ptr<Router> router)
    : socket_(std::move(socket)), router_(std::move(router)) {}

void Connection::start() {
  auto task = [self = shared_from_this()]() { return self->process_request(); };
  asio::co_spawn(socket_.get_executor(), std::move(task), asio::detached);
}

asio::awaitable<void> Connection::process_request() {
  try {
    while (true) {
      std::size_t bytes_read = co_await socket_.async_read_some(asio::buffer(buffer_), asio::use_awaitable);

      if (!parser_.parse(buffer_, bytes_read)) {
        break;
      }

      if (parser_.is_complete()) {
        HttpResponse response = co_await router_->dispatch(parser_.get_request());
        std::string res_str = response.to_string();

        co_await asio::async_write(socket_, asio::buffer(res_str), asio::use_awaitable);

        auto it = parser_.get_request().headers.find("Connection");
        if (it == parser_.get_request().headers.end() || it->second != "keep-alive") {
          break;
        }

        parser_.reset();
      }
    }
  } catch (const std::exception &e) {
  }
}
