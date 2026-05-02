import grpc
from concurrent import futures

from api import api_pb2
from api import api_pb2_grpc

import _sklearn
import _torch


class CoreServicer(api_pb2_grpc.CoreServicer):
    def Handle(self, request, context):
        print(context.peer())
        method = request.text
        if method == "sklearn":
            result = _sklearn.run()
        elif method == "torch":
            result = _torch.run()
        else:
            result = "unknown method"
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
