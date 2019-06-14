#Mary Jacobsen
#Project 2 - file transer system
#client side

import sys
from socket import *

#This function sets up the data socket
#It is mostly from Project 1
def getSocket():
    if sys.argv[3] == "-l": #if command is -l, <SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <DATA_PORT>
        numArguments = 4
    elif sys.argv[3] == "-g": #if command is -g, <SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <FILENAME>, <DATA_PORT>
        numArguments = 5

    #get server port number from command line arg
    serverport = int(sys.argv[numArguments])

    #create socket
    serversocket = socket(AF_INET, SOCK_STREAM) #referenced https://docs.python.org/2/howto/sockets.html

    #bind socket
    serversocket.bind(('', serverport)) #referenced https://docs.python.org/2/howto/sockets.html

    #listen for connections and queue up only 1 connect request
    serversocket.listen(1) #referenced https://docs.python.org/2/howto/sockets.html

    (dataSocket, address) = serversocket.accept() #referenced https://docs.python.org/2/howto/sockets.html

    return dataSocket

#This function sets up the client socket
#Used https://docs.python.org/2/howto/sockets.html
def connectServer():
    #flip1, flip2, or flip3
    servername = sys.argv[1]+".engr.oregonstate.edu"
    #get server port from command line args
    serverport = int(sys.argv[2])
    #get a client connection socket
    clientsocket = socket(AF_INET,SOCK_STREAM)
    #connect using server name and port
    clientsocket.connect((servername, serverport))

    return clientsocket

#This function gets the IP address
#I found how to do this here:
#https://stackoverflow.com/questions/166506/finding-local-ip-addresses-using-pythons-stdlib
def getIP():
    s = socket(AF_INET, SOCK_DGRAM)
    s.connect(("8.8.8.8", 80))
    return s.getsockname()[0]

#This function receives a file specified gy the command line
#I found how to do this here:
#https://www.bogotobogo.com/python/python_network_programming_server_client_file_transfer.php
def receiveFile(datasocket):
    f = open(sys.argv[4], "w") #<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <FILENAME>, <DATA_PORT>
    buffer = datasocket.recv(1024)

    #receive until server sends "finished"
    while "finished" not in buffer:
        f.write(buffer)
        buffer = datasocket.recv(1024)

    print "File transfer complete."

#This function receives and prints all the filenames in the directory from the server
def receiveList(datasocket):
    filename = datasocket.recv(100)

    #receive files until server sends "finished"
    while filename != "finished":
        print filename
        filename = datasocket.recv(100)

#This function sends the info from the command line to the server
#then receives back the data using a seperate data socket that is closed after.
#It also has some error handling
#https://docs.python.org/2/howto/sockets.html
def receiveData(clientsocket):
    if sys.argv[3] == "-g": #<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <FILENAME>, <DATA_PORT>
        print "Reqesting {}".format(sys.argv[4])
        portnumber = sys.argv[5]
        command = "-g"
    elif sys.argv[3] == "-l": #<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <DATA_PORT>
        print "Requesting list of files in this directory"
        portnumber = sys.argv[4]
        command = "-l"

    #send port number
    clientsocket.send(portnumber)

    #receive response
    clientsocket.recv(1024)

    #send command
    clientsocket.send(command)

    #receive response
    clientsocket.recv(1024)

    #send IP address
    clientsocket.send(getIP())

    #receive response
    response = clientsocket.recv(1024)

    if response == "notokay":
        print "The server could not process the command.\n Please use: -l or -g <FILENAME>"
        exit(1)

    if command == "-g":
        #send file name
        clientsocket.send(sys.argv[4])
        #receive response
        response = clientsocket.recv(1024)
        if response != "File found": #if the server does not send back "File found", we are done here."
            print "{}:{} says FILE NOT FOUND".format(sys.argv[1],sys.argv[5])
            return

    #socket for just data
    datasocket = getSocket()

    if command == "-g": #if command is g, call receiveFile
        print "Receiving {} from {}:{}".format(sys.argv[4],sys.argv[1],sys.argv[5])
        receiveFile(datasocket)

    if command == "-l": #if command is l, call receiveList
        print "Receiving directory structure from {}:{}".format(sys.argv[1],sys.argv[4])
        receiveList(datasocket)

    #close datasocket
    datasocket.close()

#All that is left to do in main is to error handle for the command line arguments,
#get the client socket by calling connectServer,
#and call getData
if __name__ == "__main__":

    #check the number of arguments
    if len(sys.argv) < 5 or len(sys.argv) > 6:
        print "Please use: python ftclient.py <SERVER_HOST> <SERVER_PORT> -g <FILENAME> <DATA_PORT>\n or python ftclient.py <SERVER_HOST> <SERVER_PORT> -l <DATA_PORT>"
        exit(1)

    #check if the server name (either flip1, flip2, or flip3)
    elif (sys.argv[1] != "flip1" and sys.argv[1] != "flip2" and sys.argv[1] != "flip3"):
        print "Server name must be flip1, flip2, or flip3."
        exit(1)

    #check the server port
    elif (int(sys.argv[2]) < 1024 or int(sys.argv[2]) > 65535):
        print "Please enter a valid server port number."
        exit(1)

    #check command (either -g or -l)
    elif (sys.argv[3] != "-g" and sys.argv[3] != "-l"):
        print "Please enter either -g or -l for the command."
        exit(1)

    #check data port for command equal to l
    elif (sys.argv[3] == "-l" and (int(sys.argv[4]) < 1024 or int(sys.argv[4]) > 65535)):
        print "Please enter a valid data port number."
        exit(1)

    #check data port for command equal to g
    elif (sys.argv[3] == "-g" and (int(sys.argv[5]) < 1024 or int(sys.argv[5]) > 65535)):
        print "Please enter a valid data port number."
        exit(1)

    #get the client socket for talking with the server
    clientsocket = connectServer()

    #And we're ready to receive the data the user wants from the server
    receiveData(clientsocket)
