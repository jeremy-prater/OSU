#! /bin/python2

from socket import *
import argparse

def GetCommandArguments():
    parser = argparse.ArgumentParser(description='Start the chatserve server')
    parser.add_argument('port', metavar='port', type=int,
                    help='port number to listen for connections on')

    args = parser.parse_args()
    return args.port


serverPort = GetCommandArguments()
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print "Server listening on port {0}".format(serverPort)

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