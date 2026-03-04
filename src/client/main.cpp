#include <asio.hpp>
#include <iostream>
#include <string>

using asio::ip::tcp;

int main() {
  try {
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "8080");

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    std::cout << "Connected to server.\n";

    std::string request = "GET / HTTP/1.1\r\n"
                          "Host: localhost\r\n"
                          "Connection: close\r\n"
                          "\r\n";

    asio::write(socket, asio::buffer(request));

    asio::streambuf response;
    asio::error_code ec;

    while (asio::read(socket, response, asio::transfer_at_least(1), ec)) {
    }

    if (ec != asio::error::eof)
      throw asio::system_error(ec);

    std::cout << "Response:\n";
    std::cout << &response;

  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
