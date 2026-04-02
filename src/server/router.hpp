#pragma once
#include "http_message.hpp"
#include <functional>

template <typename T>
concept HttpHandler = requires(T t, const HttpRequest &req) {
  { t(req) } -> std::same_as<HttpResponse>;
};

class Router {
public:
  template <HttpHandler Handler> void get(const std::string &path, Handler handler) {
    routes_["GET|" + path] = handler;
  }

  template <HttpHandler Handler> void post(const std::string &path, Handler handler) {
    routes_["POST|" + path] = handler;
  }

  HttpResponse dispatch(const HttpRequest &req) const {
    std::string key = req.method + "|" + req.url;
    if (auto it = routes_.find(key); it != routes_.end()) {
      return it->second(req);
    }
    HttpResponse res;
    res.status_code = 404;
    res.status_message = "Not Found";
    res.body = "404 Not Found";
    return res;
  }

private:
  std::unordered_map<std::string, std::function<HttpResponse(const HttpRequest &)>> routes_;
};
