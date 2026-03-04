#include <asio.hpp>
#include <iostream>
#include <string>

using asio::ip::tcp;

int main() {
  try {
    asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
    std::cout << "HTTP Server listening on port 8080...\n";

    while (true) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::cout << "Client connected: " << socket.remote_endpoint()
                << std::endl;

      asio::streambuf request;
      asio::read_until(socket, request, "\r\n\r\n");

      std::istream request_stream(&request);
      std::string request_line;
      std::getline(request_stream, request_line);

      std::cout << "Request: " << request_line << std::endl;

      std::string response_body = "Hello from Asio HTTP Server!";
      std::string response = "HTTP/1.1 200 OK\r\n"
                             "Content-Length: " +
                             std::to_string(response_body.size()) +
                             "\r\n"
                             "Content-Type: text/plain\r\n"
                             "Connection: close\r\n"
                             "\r\n" +
                             response_body;

      asio::write(socket, asio::buffer(response));
    }
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
