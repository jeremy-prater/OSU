import socket
import threading
import subprocess
import struct
import os

class ftClientListener(threading.Thread):
    def __init__(self, clientPort, command, file):
        threading.Thread.__init__(self);
        self.clientPort = clientPort
        self.command = command
        self.file = file

    def SendData (self, payload):
        payloadLength = bytearray()
        payloadLength.extend(struct.pack("H", len(payload)))
        print("Sending bytes: {}".format(len(payload)))
        self.ftConnection.send (payloadLength);
        self.ftConnection.send (payload);

    def run(self):
        print("ftclient listener thread on port {}".format(self.clientPort))
        self.ftSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ftSocket.bind ((socket.gethostname(), self.clientPort))
        self.ftSocket.settimeout(1)
        self.ftSocket.listen(1)
        self.listening = True
        self.timeoutCounter = 0;
        print ('Waiting for accept on {}'.format(self.clientPort))
        while self.listening:
            try:
                self.ftConnection, self.ftAddress = self.ftSocket.accept()
                print ('New data connection from {}'.format(self.ftAddress))
                # Send response payload length...
                if self.command == 0:
                    # list command
                    result = subprocess.run(['ls', '-l'], stdout=subprocess.PIPE)
                    self.SendData (result.stdout)
                elif self.command == 1:
                    # get file command
                    print("file...")
                else:
                    self.ftConnection.send(0);
                self.listening = False

            except socket.timeout as t:
                print("waiting...")
                self.timeoutCounter += 1
                if self.timeoutCounter < 5:
                    pass
                else:
                    raise socket.timeout
                    

        self.ftSocket.close()
        print("ftclient closing port {}".format(self.clientPort))