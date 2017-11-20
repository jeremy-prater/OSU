import socket
from ftClientListener import ftClientListener

class ftClientConnection:
    def __init__(self, serverHost, serverPort, clientPort, command, file):
        self.serverHost = serverHost
        self.serverPort = serverPort
        self.clientPort = clientPort
        self.command = command
        self.file = file

        # Setup listner socket
        self.listener = ftClientListener(clientPort)
        self.listener.start()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        print("Closing connection to ftserver {}:{}".format(self.serverHost, self.serverPort))
        self.listener.listening = False
        self.ftSock.close()
        
    def ftConnect(self):
        print("Connecting to ftserver {}:{}".format(self.serverHost, self.serverPort))
        self.ftSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.ftSock.connect((self.serverHost, self.serverPort))
        except:
            print("Connecting to ftserver {}:{} failed!".format(self.serverHost, self.serverPort))
            return False
        return True
        
    def ftSendCommand(self):
        self.ftSock.send((self.command, self.file))