#include "Server.h"
#include "ServerSock.h"

Server::Server()
    :mSocket(nullptr)
	, mMainThread(nullptr)
{
	mMainThreadRunning = false;
}

Server::~Server()
{
    if(mSocket != nullptr)
    {
        delete mSocket;
    }

	for (SockConnection* c : mListConnect)
	{
		delete c;
	}

	mListConnect.clear();

	mMainThreadRunning.exchange(false);
	if (mMainThread != nullptr)
	{
		if (mMainThread->joinable())
		{
			mMainThread->join();
		}

		delete mMainThread;
	}
}

void Server::InitServer()
{
    mSocket = new ServerSock();

    sockaddr_in serverAdd;

    bzero((char*) &(serverAdd),sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = INADDR_ANY;
    serverAdd.sin_port = htons(7777);
    
    mSocket->Setup(serverAdd);
    mSocket->SocketSetup();
    static_cast<ServerSock*>(mSocket)->RegisterConnectionEvent(this,&Server::OnReceiveConnection);
    
    static_cast<ServerSock*>(mSocket)->StartListen();

	if (mMainThread != nullptr)
	{
		mMainThreadRunning.exchange(true);
		mMainThread = new std::thread(&Server::MainLoop, this);
	}

}

void Server::MainLoop()
{
	while (mMainThreadRunning)
	{
		std::vector<std::string> vecData;
		mMutext.lock();
		int size = mClientMessages.size();
		if (size > 0)
		{
			for (int i = 0; i < size; i++)
			{
				vecData.push_back(mClientMessages[i]);
			}
		}
		mMutext.unlock();

		if (!vecData.empty())
		{
			printf("[Serer] Receive messages from clients: \n");
			for (const std::string& data : vecData)
			{
				printf("-- %s", data.c_str());
			}

			SaveDataToDB(vecData);
		}
	}
}

void Server::SaveDataToDB(std::vector<std::string> data)
{
	for (std::string s : data)
	{
		mServerDatabase.push_back(s);
	}
}

bool Server::OnReceiveConnection(void* caller, int connection)
{
    Server* server = static_cast<Server*>(caller);
    if(connection > 0)
    {
        server->ReceiveConnection(connection);
        return true;
    }
    else
    {
        return false;
    }
    
}

void Server:: ReceiveConnection(int connection)
{
    SockConnection* connectObj = CreateConnection(connection);
    connectObj->RegisterRecieveData(this,&Server::OnReceiveData);
    connectObj->StartListioning();
    mListConnect.push_back(connectObj);
}

void Server::OnReceiveData(void* caller, char* data, size_t size)
{
    Server* server = static_cast<Server*>(caller);
    server->ReceiveData(data, size);
}

void Server::ReceiveData(char* data, size_t size)
{
    char buffer[size];
    memcpy(&buffer[0],&data,size);

    printf("Server::ReceiveData -- %s", buffer);
    // [TODO] handle client data
}

SockConnection* Server::CreateConnection(int connection)
{
	SockConnection* c = new SockConnection(connection);

	return c;
}
