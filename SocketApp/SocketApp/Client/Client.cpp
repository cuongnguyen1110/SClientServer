#include "Client.h"
#include "ClientSock.h"
#include "../Commons/SockConnection.h"

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
   
    
}


Client::~Client()
{
    delete mSocket;
	delete mConnection;
}

bool Client::ConnectToServer()
{
	int connection = static_cast<ClientSock*>(mSocket)->Connect();
	if (connection > 0)
	{

		printf("Client connect success \n");
		if (mConnection == nullptr)
		{
			mConnection = new SockConnection(connection);
			mConnection->RegisterRecieveData(this, &Client::OnReceiveData);
			mConnection->StartListioning();
		}
		return true;
	}
	else
	{
		printf(" client connect fail \n");
		return false;
	}
}

void Client::SendToServer(char* data, int size)
{
	if (mConnection)
	{
		mConnection->Send(data, size);
	}
    printf("Client try to send data \n");
}

void Client::OnReceiveData(void* caller, char* data, size_t size)
{
	Client* client = static_cast<Client*>(caller);
	client->ReceiveData(data, size);
}

void Client::ReceiveData(char* data, int size)
{
	printf("[Client] Receive data from server %s", data);

}
