import grpc
from concurrent import futures

from api import api_pb2
from api import api_pb2_grpc

import mlp


class CoreServicer(api_pb2_grpc.CoreServicer):
    def Handle(self, request, context):
        print(context.peer())
        print(f"received: {request.text}")
        result = mlp.run(request.text)
        return api_pb2.Response(text=result)  # type: ignore


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    api_pb2_grpc.add_CoreServicer_to_server(CoreServicer(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    print("gRPC server listening on [::]:50051")
    server.wait_for_termination()


if __name__ == "__main__":
    serve()
