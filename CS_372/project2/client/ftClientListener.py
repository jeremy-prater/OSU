import socket

class ftClientListener:
    def __init__(self, clientPort):
        self.clientPort = clientPort
        print("ftclient listening on port {}".format(self.clientPort))

    def close(self):
        print("ftclient closing port {}".format(self.clientPort))