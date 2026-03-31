#pragma once
#include "http_message.hpp"
#include <llhttp.h>

class HttpParser {
public:
  HttpParser();
  ~HttpParser() = default;

  bool parse(const char *data, size_t len);
  bool is_complete() const { return complete_; }
  void reset();
  HttpRequest &get_request() { return request_; }

private:
  llhttp_t parser_;
  llhttp_settings_t settings_;
  HttpRequest request_;
  bool complete_ = false;

  std::string current_header_field_;
  std::string current_header_value_;
  bool last_was_value_ = false;

  // llhttp C callbacks
  static int on_url(llhttp_t *parser, const char *at, size_t length);
  static int on_header_field(llhttp_t *parser, const char *at, size_t length);
  static int on_header_value(llhttp_t *parser, const char *at, size_t length);
  static int on_headers_complete(llhttp_t *parser);
  static int on_body(llhttp_t *parser, const char *at, size_t length);
  static int on_message_complete(llhttp_t *parser);
};
