#pragma once
#include "http_message.hpp"
#include <asio.hpp>
#include <concepts>
#include <functional>
#include <string>
#include <unordered_map>

template <typename T>
concept HttpHandler = requires(T t, const HttpRequest &req) {
  { t(req) } -> std::same_as<asio::awaitable<HttpResponse>>;
};

class Router {
public:
  template <HttpHandler Handler> void get(const std::string &path, Handler handler) {
    routes_["GET|" + path] = handler;
  }

  template <HttpHandler Handler> void post(const std::string &path, Handler handler) {
    routes_["POST|" + path] = handler;
  }

  asio::awaitable<HttpResponse> dispatch(const HttpRequest &req) const {
    std::string key = req.method + "|" + req.url;
    if (auto it = routes_.find(key); it != routes_.end()) {
      co_return co_await it->second(req);
    }
    HttpResponse res;
    res.status_code = 404;
    res.status_message = "Not Found";
    res.body = "404 Not Found";
    co_return res;
  }

private:
  std::unordered_map<std::string, std::function<asio::awaitable<HttpResponse>(const HttpRequest &)>> routes_;
};
