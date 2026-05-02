import grpc
from concurrent import futures

import _sklearn
import _torch
from api import api_pb2
from api import api_pb2_grpc


class CoreServicer(api_pb2_grpc.CoreServicer):
    def Handle(self, request, context):
        print(context.peer())
        if request.text == "sklearn":
            res = _sklearn.run()
        elif request.text == "torch":
            res = _torch.run()
        else:
            res = ""
        return api_pb2.Response(text=str(res))  # type: ignore


def server():
    server = grpc.server(futures.ThreadPoolExecutor(10))
    api_pb2_grpc.add_CoreServicer_to_server(CoreServicer(), server)
    server.add_insecure_port("127.0.0.1:50051")
    server.start()
    print("lisening")
    server.wait_for_termination()


if __name__ == "__main__":
    server()
