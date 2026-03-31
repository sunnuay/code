#include "connection.hpp"

Connection::Connection(tcp::socket socket, std::shared_ptr<Router> router)
    : socket_(std::move(socket)), router_(std::move(router)) {}

void Connection::start() {
  asio::co_spawn(
      socket_.get_executor(),
      [self = shared_from_this()] { return self->process_request(); },
      asio::detached);
}

asio::awaitable<void> Connection::process_request() {
  try {
    while (true) {
      // 纯异步读取 (使用协程 co_await)
      std::size_t bytes_read = co_await socket_.async_read_some(
          asio::buffer(buffer_), asio::use_awaitable);

      // 解析 HTTP 流 (llhttp 状态机)
      if (!parser_.parse(buffer_, bytes_read)) {
        break; // 解析错误，断开连接
      }

      // 报文完整，执行路由分发
      if (parser_.is_complete()) {
        HttpResponse response = router_->dispatch(parser_.get_request());
        response.headers["Server"] = "Modern-Cpp-Async-Server";

        std::string res_str = response.to_string();

        // 纯异步写入
        co_await asio::async_write(socket_, asio::buffer(res_str),
                                   asio::use_awaitable);

        // 判断是否是 Keep-Alive (简单实现，默认非 keep-alive 则退出)
        auto it = parser_.get_request().headers.find("Connection");
        if (it == parser_.get_request().headers.end() ||
            it->second != "keep-alive") {
          break;
        }

        parser_.reset(); // 准备下一个请求
      }
    }
  } catch (const std::exception &e) {
    // Socket 关闭或 I/O 错误正常抛出，静默处理以提升健壮性
  }

  // 协程结束，连接对象由于 shared_ptr 引用归零自动析构，socket 自动关闭
}
