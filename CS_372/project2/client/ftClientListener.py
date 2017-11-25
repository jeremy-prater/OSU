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

    def GetData (self):
        payload = bytearray();
        while True:
            data = self.ftConnection.recv(1024);
            if not data:
                return payload
            payload.extend(data)

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
                data = self.GetData();
                # Send response payload length...
                if self.command == 0:
                    # list command
                    print ("{}".format(data.decode('ASCII')))
                elif self.command == 1:
                    # get file command
                    print("file...")
                    if os.path.isfile(self.file):
                        print ("File {} exists in local directory Not overwriting!".format(self.file))
                    else:
                        if len(data) > 0:
                            outFile = open(self.file, 'wb')
                            outFile.write(data)
                            outFile.close()
                            print ("Wrote {} bytes to file {}".format(len(data), self.file))
                        else:
                            print ("File {} not found on server.".format(self.file))
                            
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