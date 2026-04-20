#include "http_message.hpp"
#include "pg_pool.hpp"
#include "router.hpp"
#include "server.hpp"
#include <asio.hpp>
#include <csignal>
#include <exception>
#include <memory>
#include <print>

asio::awaitable<void> async_main(asio::io_context &io_context) {
  try {
    auto pg_pool = std::make_shared<PgPool>(io_context, "host=/tmp port=5432 user=sunnuay dbname=postgres", 10);
    co_await pg_pool->init();
    std::println("PostgreSQL poll initialized");

    auto router = std::make_shared<Router>();

    router->get("/", [](const HttpRequest &req) -> asio::awaitable<HttpResponse> {
      HttpResponse res;
      res.body = "<h1>Welcome to MCPP Web Server!</h1>";
      res.headers["Content-Type"] = "text/html";
      co_return res;
    });

    router->get("/users", [pg_pool](const HttpRequest &req) -> asio::awaitable<HttpResponse> {
      HttpResponse res;
      try {
        auto conn = co_await pg_pool->acquire();
        auto rows = co_await conn->query("SELECT id, name FROM users LIMIT 10");
        res.body = "Users:\n";
        for (const auto &row : rows) {
          res.body += "ID: " + row[0] + ", Name: " + row[1] + "\n";
        }
      } catch (const std::exception &e) {
        res.status_code = 500;
        res.body = std::string("DB Error: ") + e.what();
      }
      res.headers["Content-Type"] = "text/plain";
      co_return res;
    });

    short port = 10001;
    Server server(io_context, port, router);
    server.start();
    std::println("Web Server is running");

    asio::signal_set signals(io_context, SIGINT, SIGTERM);
    co_await signals.async_wait(asio::use_awaitable);
    server.stop();

  } catch (const std::exception &e) {
    std::println("main: {}", e.what());
  }
}

int main() {
  asio::io_context io_context(1);
  asio::co_spawn(io_context, async_main(io_context), asio::detached);
  io_context.run();
  std::println("Event loop exited");
}
