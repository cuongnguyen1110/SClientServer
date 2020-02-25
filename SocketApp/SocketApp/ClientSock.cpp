#include "ClientSock.h"

#include <netdb.h> 

void ClientSock::SocketSetup()
{
    mClientSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (mClientSockfd < 0) 
	{
		printf("ERROR  mClientSockfd opening socket");
	}

    struct hostent *server;
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
    }

    bcopy((char *)server->h_addr, (char *)&mServerAdd.sin_addr.s_addr,server->h_length);
};

int ClientSock::Connect()
{
    if (connect(mClientSockfd,(struct sockaddr *) &mServerAdd,sizeof(mServerAdd)) < 0) 
    {
        printf("ERROR client connecting");
        return -1;
    }
        
    return mClientSockfd;
}