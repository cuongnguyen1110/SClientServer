
objects = ServerApp.o ServerSock.o SockConnection.o Server.o 

MServetApp : $(objects)
		cc -o MServetApp  $(objects)  -lstdc++ -lpthread

ServerApp.o : ServerApp.cpp
		cc -c -I./../Commons/ -o ServerApp.o ServerApp.cpp

ServerSock.o : ServerSock.cpp
		cc -c -I./../Commons/ -o ServerSock.o ServerSock.cpp

SockConnection.o : ./../Commons/SockConnection.cpp
		cc -c -I./../Commons/ -o SockConnection.o ./../Commons/SockConnection.cpp

Server.o : Server.cpp
		cc -c -I./../Commons/ -o Server.o Server.cpp

.PHONY : clean
clean :
		rm MServetApp $(objects)