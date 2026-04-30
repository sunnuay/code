protoc -I server --go_out=server --go-grpc_out=server server/api.proto
uv run -m grpc_tools.protoc -I server --python_out=server --grpc_python_out=server server/api.proto
