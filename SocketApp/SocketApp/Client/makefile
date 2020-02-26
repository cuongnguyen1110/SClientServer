
objects = Client.o ClientApp.o ClientSock.o SockConnection.o

MClientApp : $(objects)
		cc -o MClientApp  $(objects)  -lstdc++ -lpthread

Client.o : Client.cpp
		cc -c -I./../Commons/ -o Client.o Client.cpp

ClientApp.o : ClientApp.cpp
		cc -c -I./../Commons/ -o ClientApp.o ClientApp.cpp

SockConnection.o : ./../Commons/SockConnection.cpp
		cc -c -I./../Commons/ -o SockConnection.o ./../Commons/SockConnection.cpp

ClientSock.o : ClientSock.cpp
		cc -c -I./../Commons/ -o ClientSock.o ClientSock.cpp

.PHONY : clean
clean :
		rm MClientApp $(objects)