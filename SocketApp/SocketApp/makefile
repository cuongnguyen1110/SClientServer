objects = SocketApp.o ServerSock.o SockConnection.o Server.o \
          ClientSock.o 

ClientServetApp : $(objects)
		cc -o ClientServetApp $(objects)

.PHONY : clean
clean :
		rm edit $(objects)