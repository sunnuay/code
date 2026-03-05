#include <asio.hpp>
#include <iostream>
#include <llhttp.h>
#include <string>

using asio::ip::tcp;

class Client {
public:
  Client(asio::io_context &io_context, const std::string &host,
         const std::string &port)
      : socket_(io_context), resolver_(io_context) {

    // 1. 初始化 llhttp 设置和回调
    llhttp_settings_init(&settings_);

    // 解析到响应体 Body 时触发
    settings_.on_body = [](llhttp_t *parser, const char *at,
                           size_t length) -> int {
      std::cout.write(at, length);
      return 0;
    };

    // 报文结束时触发
    settings_.on_message_complete = [](llhttp_t *parser) -> int {
      auto *self = static_cast<Client *>(parser->data);
      self->response_complete_ = true;
      std::cout << "\n[Message Complete]\n";
      return 0;
    };

    // 2. 初始化解析器为 Response 模式
    llhttp_init(&parser_, HTTP_RESPONSE, &settings_);
    parser_.data = this;

    // 3. 解析域名并连接
    resolver_.async_resolve(
        host, port,
        [this](std::error_code ec, tcp::resolver::results_type results) {
          if (!ec) {
            asio::async_connect(socket_, results,
                                [this](std::error_code ec, tcp::endpoint) {
                                  if (!ec)
                                    do_write();
                                });
          }
        });
  }

private:
  void do_write() {
    request_ = "GET / HTTP/1.1\r\n"
               "Host: 127.0.0.1\r\n"
               "Connection: close\r\n\r\n";

    asio::async_write(socket_, asio::buffer(request_),
                      [this](std::error_code ec, std::size_t /*length*/) {
                        if (!ec)
                          do_read();
                      });
  }

  void do_read() {
    socket_.async_read_some(
        asio::buffer(data_, max_length),
        [this](std::error_code ec, std::size_t length) {
          if (!ec) {
            // 4. 解析服务端传回的数据
            enum llhttp_errno err = llhttp_execute(&parser_, data_, length);
            if (err != HPE_OK) {
              std::cerr << "Parse error: " << llhttp_errno_name(err) << "\n";
              return;
            }
            if (!response_complete_) {
              do_read(); // 继续读
            }
          } else if (ec != asio::error::eof) {
            std::cerr << "Read error: " << ec.message() << "\n";
          }
        });
  }

  tcp::socket socket_;
  tcp::resolver resolver_;
  std::string request_;
  enum { max_length = 1024 };
  char data_[max_length];

  llhttp_t parser_;
  llhttp_settings_t settings_;
  bool response_complete_ = false;
};

int main() {
  try {
    asio::io_context io_context;
    Client client(io_context, "127.0.0.1", "8080");
    io_context.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}
