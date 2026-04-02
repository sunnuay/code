#include "http_parser.hpp"

HttpParser::HttpParser() {
  llhttp_settings_init(&settings_);
  settings_.on_url = on_url;
  settings_.on_header_field = on_header_field;
  settings_.on_header_value = on_header_value;
  settings_.on_headers_complete = on_headers_complete;
  settings_.on_body = on_body;
  settings_.on_message_complete = on_message_complete;

  llhttp_init(&parser_, HTTP_REQUEST, &settings_);
  parser_.data = this;
}

bool HttpParser::parse(const char *data, size_t len) {
  llhttp_errno_t err = llhttp_execute(&parser_, data, len);
  return err == HPE_OK;
}

void HttpParser::reset() {
  llhttp_reset(&parser_);
  request_ = HttpRequest();
  complete_ = false;
  current_header_field_.clear();
  current_header_value_.clear();
  last_was_value_ = false;
}

int HttpParser::on_url(llhttp_t *parser, const char *at, size_t length) {
  auto *self = static_cast<HttpParser *>(parser->data);
  self->request_.url.append(at, length);
  return 0;
}

int HttpParser::on_header_field(llhttp_t *parser, const char *at, size_t length) {
  auto *self = static_cast<HttpParser *>(parser->data);
  if (self->last_was_value_) {
    self->request_.headers[self->current_header_field_] = self->current_header_value_;
    self->current_header_field_.clear();
    self->current_header_value_.clear();
  }
  self->current_header_field_.append(at, length);
  self->last_was_value_ = false;
  return 0;
}

int HttpParser::on_header_value(llhttp_t *parser, const char *at, size_t length) {
  auto *self = static_cast<HttpParser *>(parser->data);
  self->current_header_value_.append(at, length);
  self->last_was_value_ = true;
  return 0;
}

int HttpParser::on_headers_complete(llhttp_t *parser) {
  auto *self = static_cast<HttpParser *>(parser->data);
  if (!self->current_header_field_.empty()) {
    self->request_.headers[self->current_header_field_] = self->current_header_value_;
  }
  self->request_.method = llhttp_method_name(static_cast<llhttp_method>(parser->method));
  return 0;
}

int HttpParser::on_body(llhttp_t *parser, const char *at, size_t length) {
  auto *self = static_cast<HttpParser *>(parser->data);
  self->request_.body.append(at, length);
  return 0;
}

int HttpParser::on_message_complete(llhttp_t *parser) {
  auto *self = static_cast<HttpParser *>(parser->data);
  self->complete_ = true;
  return 0;
}
