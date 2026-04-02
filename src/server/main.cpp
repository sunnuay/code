#include "router.hpp"
#include "server.hpp"
#include <print>

int main() {
  try {
    auto router = std::make_shared<Router>();

    router->get("/", [](const HttpRequest &req) -> HttpResponse {
      HttpResponse res;
      res.body = "<h1>Welcome to MCPP Web Server!</h1>";
      res.headers["Content-Type"] = "text/html";
      return res;
    });

    router->post("/echo", [](const HttpRequest &req) -> HttpResponse {
      HttpResponse res;
      res.body = "You said: " + req.body;
      res.headers["Content-Type"] = "text/plain";
      return res;
    });

    asio::io_context io_context(1);
    short port = 10001;
    Server server(io_context, port, router);
    server.start();
    std::println("Port: {}", port);
    io_context.run();

  } catch (const std::exception &e) {
    std::println("Error: {}", e.what());
  }
}
