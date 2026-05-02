cd $(dirname $0)

protoc api/api.proto \
  --go_out=. \
  --go-grpc_out=.

uv run -m grpc_tools.protoc api/api.proto \
  --proto_path=. \
  --python_out=. \
  --grpc_python_out=.
