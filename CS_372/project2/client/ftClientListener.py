import socket

class ftClientListener:
    def __init__(self, clientPort):
        self.clientPort = clientPort
        print("ftclient listening on port {}".format(self.clientPort))

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        print("ftclient closing port {}".format(self.clientPort))