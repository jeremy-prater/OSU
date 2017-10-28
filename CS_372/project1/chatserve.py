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

while 1:
    serverSocket.listen(1)
    print "Server listening on port {0}".format(serverPort)
    connectionSocket, addr = serverSocket.accept()
    handle = connectionSocket.recv(1024);
    print "User : [" + handle + "] connected!"
    running = True
    counter = 0;
    while running:
        serverData = connectionSocket.recv(1024);
        if not serverData or serverData == '\\quit':
            print "User : [" + handle + "] disconnected!"
            running = False
        else:
            print handle + "> " + serverData
            counter = counter + 1
            if counter == 5:
                connectionSocket.send('\\quit')
            else:
                connectionSocket.send('server> ' + serverData);