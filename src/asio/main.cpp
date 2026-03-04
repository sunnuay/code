#include <asio.hpp>
#include <iostream>

int main() {
  asio::io_context io;
  asio::steady_timer timer(io, std::chrono::seconds(1));
  timer.async_wait([](const asio::error_code &ec) {
    if (!ec) {
      std::cout << "Timer fired!" << std::endl;
    }
  });
  io.run();
}
