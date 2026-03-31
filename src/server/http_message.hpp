#pragma once
#include <string>
#include <unordered_map>

struct HttpRequest {
  std::string method;
  std::string url;
  std::unordered_map<std::string, std::string> headers;
  std::string body;
};

struct HttpResponse {
  int status_code = 200;
  std::string status_message = "OK";
  std::unordered_map<std::string, std::string> headers;
  std::string body;

  std::string to_string() const {
    std::string res = "HTTP/1.1 " + std::to_string(status_code) + " " +
                      status_message + "\r\n";
    for (const auto &[k, v] : headers) {
      res += k + ": " + v + "\r\n";
    }
    res += "Content-Length: " + std::to_string(body.size()) + "\r\n\r\n";
    res += body;
    return res;
  }
};
