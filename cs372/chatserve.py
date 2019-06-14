#!/bin/python
# -*- coding: utf-8 -*-
# Mary Jacobsen
# client server chat program
# server side

import sys
from socket import *

#after set up is done, we can chat
def chat(newConnection, clientName, serverName):
    message = "" #to hold chat message

    while 1: #just keep chatting
        receive = newConnection.recv(501)[0:-1] #receive message from client
        if receive == "": #if empty, this connection is over
            print "{} closed the connection".format(clientName)
            print "Waiting for a new connection"
            break

        print "{}> {}".format(clientName, receive) #format specified by assignment
        sending = ""
        while len(sending) > 500 or len(sending) == 0:
            sending = raw_input("{}> ".format(serverName))

        if sending == "\quit": #or closes the connection with the command “\quit”
            print "{} closed the connection".format(serverName)
            print "Waiting for a new connection"
            break
        newConnection.send(sending)

#exchange names
def handshake(connection, serverName):
    clientName = connection.recv(1024)
    connection.send(serverName)
    return clientName

if __name__ == "__main__":
    if len(sys.argv) != 2: #check that the number of args is two
        print "Please run: python chatServer.py [port]"
        exit(1)

    #get port number from command line arg
    portNumber = sys.argv[1]

    #create socket
    serversocket = socket(AF_INET, SOCK_STREAM) #referenced https://docs.python.org/2/howto/sockets.html

    #bind socket
    serversocket.bind(('', int(portNumber))) #referenced https://docs.python.org/2/howto/sockets.html

    #listen for connections and queue up only 1 connect request
    serversocket.listen(1) #referenced https://docs.python.org/2/howto/sockets.html

    serverName = "" #to hold server name
    while len(serverName) > 10 or len(serverName) == 0: #get the server name
        serverName = raw_input("Enter a one-word name that is 10 characters or less for the server. ")

    print "The server is ready to chat."

    while 1: #keep waiting for connections
        connection, address = serversocket.accept() #connect
        print "Connected on address {}".format(address)

        chat(connection, handshake(connection, serverName), serverName) #chat

        connection.close() #close connection
