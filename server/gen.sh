protoc -I. --go_out=. --go-grpc_out=. --go_opt=paths=source_relative --go-grpc_opt=paths=source_relative api/api.proto
uv run -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. api/api.proto
