import socket
import threading

class ftClientListener(threading.Thread):
    def __init__(self, clientPort):
        threading.Thread.__init__(self);
        self.clientPort = clientPort
    
    def run(self):
        print("ftclient listener thread on port {}".format(self.clientPort))
        self.ftSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ftSocket.bind (('127.0.0.1', self.clientPort))
        self.ftSocket.settimeout(1)
        self.ftSocket.listen(1)
        self.listening = True
        print ('Waiting for accept on {}'.format(self.clientPort))
        while self.listening:
            try:
                self.ftConnection, self.ftAddress = self.ftSocket.accept()
                print ('New connection from {}'.format(self.ftAddress))
                while True:
                    data = ftConnection.recv(1024)
                    if not data: break
                    print ('Data: {}'.format(data))

            except socket.timeout as t:
                pass

        print("ftclient closing port {}".format(self.clientPort))