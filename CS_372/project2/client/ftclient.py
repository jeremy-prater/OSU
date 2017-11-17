#!/usr/bin/env python

import sys
import argparse
from ftClientConnection import ftClientConnection

parser = argparse.ArgumentParser(description='ftclient')
parser.add_argument('host', help='ftserver host to connect to')
parser.add_argument('port', type=int, help='ftserver port to connect to')
parser.add_argument('-l', action='store_true', help='get directory listing')
parser.add_argument('-g', help='download file')
parser.add_argument('clientPort', type=int, help='ftclient port to connect to')
args = parser.parse_args();

if (args.port < 0) or (args.port > 65535):
    print("Invalid host port: {}".format(args.port))
    sys.exit(-1)

if (args.clientPort < 0) or (args.clientPort > 65535):
    print("Invalid client port: {}".format(args.clientPort))
    sys.exit(-2)

command = -1
file = ""
if args.l:
    command = 0
elif args.g != None:
    command = 1
    file = args.g
else:
    print("No command specified!")
    sys.exit(-3)

with ftClientConnection(args.host, args.port, args.clientPort, command, file) as connection:
    connection.ftConnect()