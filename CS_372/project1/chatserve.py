#! /bin/python2

from socket import *

serverPort = 12000

serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print "Server listening on port"

while 1:
    connectionSocket, addr = serverSocket.accept()

    running = True
    while running:
        serverData = connectionSocket.recv(1024);
        print serverData
        connectionSocket.send('server> ' + serverData);
        if serverData == '\\quit':
            running = False
            serverSocket.close()