#include "http_message.hpp"
#include "pg_pool.hpp"
#include "router.hpp"
#include "server.hpp"
#include <asio.hpp>
#include <csignal>
#include <exception>
#include <format>
#include <memory>
#include <print>
#include <thread>
#include <vector>

asio::awaitable<void> async_main(asio::io_context &io_context) {
  try {
    auto pg_pool = std::make_shared<PgPool>(io_context, "host=127.0.0.1 port=5432 dbname=postgres", 10);
    co_await pg_pool->init();

    auto router = std::make_shared<Router>();

    router->get("/", [](const HttpRequest &req) -> asio::awaitable<HttpResponse> {
      HttpResponse res;
      res.headers["Content-Type"] = "text/plain";
      res.body = "hello";
      co_return res;
    });

    router->get("/users", [pg_pool](const HttpRequest &req) -> asio::awaitable<HttpResponse> {
      HttpResponse res;
      res.headers["Content-Type"] = "text/plain";
      auto conn = co_await pg_pool->acquire();
      auto rows = co_await conn->query("SELECT * FROM users");
      for (const auto &row : rows) {
        res.body += std::format("{}, {}, {}\n", row[0], row[1], row[2]);
      }
      co_return res;
    });

    short port = 10001;
    Server server(io_context, port, router);
    server.start();
    std::println("Serving on {}", port);

    asio::signal_set signals(io_context, SIGINT, SIGTERM);
    co_await signals.async_wait(asio::use_awaitable);
    server.stop();

  } catch (const std::exception &e) {
    std::println("async_main: {}", e.what());
  }
}

int main() {
  asio::io_context io_context;
  asio::co_spawn(io_context, async_main(io_context), asio::detached);

  int num_threads = 8;
  std::vector<std::jthread> threads;
  while (--num_threads) {
    threads.emplace_back([&io_context]() { io_context.run(); });
  }
  io_context.run();
  std::println("Event loop exited");
}
