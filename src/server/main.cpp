#include <asio.hpp>
#include <iostream>
#include <llhttp.h>
#include <memory>
#include <string>

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
  Session(tcp::socket socket) : socket_(std::move(socket)) {
    // 1. 初始化 llhttp 设置和回调
    llhttp_settings_init(&settings_);

    // 当 HTTP 报文解析完成时触发
    settings_.on_message_complete = [](llhttp_t *parser) -> int {
      auto *self = static_cast<Session *>(parser->data);
      self->request_complete_ = true;
      return 0; // 返回 0 表示继续执行
    };

    // 2. 初始化解析器为 Request 模式
    llhttp_init(&parser_, HTTP_REQUEST, &settings_);
    parser_.data = this; // 绑定上下文
  }

  void start() { do_read(); }

private:
  void do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(
        asio::buffer(data_, max_length),
        [this, self](std::error_code ec, std::size_t length) {
          if (!ec) {
            // 3. 将收到的数据喂给 llhttp
            enum llhttp_errno err = llhttp_execute(&parser_, data_, length);
            if (err != HPE_OK) {
              std::cerr << "Parse error: " << llhttp_errno_name(err) << " "
                        << parser_.reason << "\n";
              return;
            }

            // 4. 如果请求解析完成，则发送响应
            if (request_complete_) {
              do_write();
            } else {
              do_read(); // 继续读
            }
          }
        });
  }

  void do_write() {
    auto self(shared_from_this());
    // 构造简单的 HTTP 响应
    response_ = "HTTP/1.1 200 OK\r\n"
                "Content-Length: 13\r\n"
                "Content-Type: text/plain\r\n"
                "Connection: close\r\n\r\n"
                "Hello, World!";

    asio::async_write(socket_, asio::buffer(response_),
                      [this, self](std::error_code ec, std::size_t /*length*/) {
                        // 发送完成后，由于启用了 Connection: close，Asio
                        // session 销毁时 socket 会自动断开
                      });
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];

  llhttp_t parser_;
  llhttp_settings_t settings_;
  bool request_complete_ = false;
  std::string response_;
};

class Server {
public:
  Server(asio::io_context &io_context, short port)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
  }

private:
  void do_accept() {
    acceptor_.async_accept([this](std::error_code ec, tcp::socket socket) {
      if (!ec) {
        std::make_shared<Session>(std::move(socket))->start();
      }
      do_accept();
    });
  }

  tcp::acceptor acceptor_;
};

int main() {
  try {
    asio::io_context io_context;
    Server server(io_context, 8080);
    std::cout << "Server running on port 8080...\n";
    io_context.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}
