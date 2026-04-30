import grpc
from concurrent import futures

import api_pb2
import api_pb2_grpc


class CoreServicer(api_pb2_grpc.CoreServicer):
    def Handle(self, request, context):
        print(f"received: {request.text}")
        return api_pb2.Response(text=f"echo: {request.text}")


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    api_pb2_grpc.add_CoreServicer_to_server(CoreServicer(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    print("gRPC server listening on [::]:50051")
    server.wait_for_termination()


if __name__ == "__main__":
    serve()
