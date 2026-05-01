cd "$(dirname "$0")"

protoc \
  --go_out=. \
  --go-grpc_out=. \
  --proto_path=. api/api.proto

uv run -m grpc_tools.protoc \
  --python_out=. \
  --grpc_python_out=. \
  --proto_path=. api/api.proto
