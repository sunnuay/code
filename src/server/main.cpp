#include "router.hpp"
#include "server.hpp"
#include <asio.hpp>
#include <iostream>

int main() {
  try {
    // 1. 实例化 Router
    auto router = std::make_shared<Router>();

    // 2. 注册路由 (利用 C++20 Lambda 和 Concept 类型安全检查)
    router->get("/", [](const HttpRequest &req) -> HttpResponse {
      HttpResponse res;
      res.body = "<h1>Welcome to Modern C++ Async Web Server!</h1>";
      res.headers["Content-Type"] = "text/html";
      return res;
    });

    router->post("/echo", [](const HttpRequest &req) -> HttpResponse {
      HttpResponse res;
      res.body = "You said: " + req.body;
      res.headers["Content-Type"] = "text/plain";
      return res;
    });

    // 3. 设置 Asio IO 上下文 (Proactor 核心)
    // 提示: 在多核机器上可以通过运行多个 io_context.run() 线程实现更高并发
    // (这里演示单线程异步)
    asio::io_context io_context(1);

    // 4. 启动 Server
    short port = 8080;
    Server server(io_context, port, router);
    server.start();

    std::cout << "Server is running on http://127.0.0.1:" << port << "\n";

    // 5. 挂起主线程，事件循环接管
    io_context.run();

  } catch (const std::exception &e) {
    std::cerr << "Fatal Error: " << e.what() << "\n";
  }

  return 0;
}
