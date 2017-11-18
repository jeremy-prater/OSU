import socket
import threading

class ftClientListener(threading.Thread):
    def __init__(self, clientPort):
        threading.Thread.__init__(self);
        self.clientPort = clientPort
    
    def run(self):
        print("ftclient listener thread on port {}".format(self.clientPort))
        print("ftclient closing port {}".format(self.clientPort))