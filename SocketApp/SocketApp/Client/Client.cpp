#include "Client.h"
#include "ClientSock.h"


Client::Client()
    :mSocket(nullptr)
{
    mSocket = new ClientSock();

    sockaddr_in serverAdd;
    bzero((char*) &(serverAdd),sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = INADDR_ANY;
    serverAdd.sin_port = htons(7777);
    
    mSocket->Setup(serverAdd);
    mSocket->SocketSetup();
    int connection = static_cast<ClientSock*>(mSocket)->Connect();
    if(connection > 0)
    {
        printf("Client connect success \n");
    }
    else
    {
        printf(" client connect fail \n");
    }
    
}


Client::~Client()
{
    delete mSocket;
}

void Client::SendToServer(char* data, int size)
{
    printf("Client try to send data \n");
}

