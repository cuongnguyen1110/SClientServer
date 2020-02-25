#include "ServerSock.h"

ServerSock::~ServerSock()
{
	mListioningLoopRunning = false;
	if (mListioningThread != nullptr)
	{
		if (mListioningThread->joinable())
		{
			mListioningThread->join();
		}

		delete mListioningThread;
	}

	mMainLoopRunning = false;
	if (mMainThread != nullptr)
	{
		if (mMainThread->joinable())
		{
			mMainThread->join();
		}

		delete mMainThread;
	}
}


ServerSock::ServerSock()
	:mListioningThread(nullptr)
	, mMainThread(nullptr)
	, mListioningLoopRunning(false)
	, mMainLoopRunning(false)
{
	mMainLoopRunning = true;
	mMainThread = new std::thread(&ServerSock::MainLoop, this); // start main thread
}

void ServerSock::StartListen()
{
	mListioningLoopRunning = true;
	mListioningThread = new std::thread(&ServerSock::ListioningLoop, this);
}

void ServerSock::ListioningLoop()
{
	while (mListioningLoopRunning)
	{
 		socklen_t clilen;
		struct sockaddr_in cli_addr;
		clilen = sizeof(cli_addr);
     	int clientSockfd = accept(mServerSockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (clientSockfd < 0)
		{
			printf("ERROR!!! error on accept: %d", cli_addr.sin_addr);
		}
		else
		{
			OnClientConnected(clientSockfd);
		}
	}

	// close server socket
	// notify socket server die
}

void ServerSock::OnClientConnected(int clientSockFD)
{
	mInternalMutex.lock();
	mListConnection.push_back(clientSockFD);
	mInternalMutex.unlock();
}

void ServerSock::MainLoop()
{
	while (mMainLoopRunning)
	{
		// fetch conection events
		std::vector<int> data;
		mInternalMutex.lock();
		if (!mListConnection.empty())
		{
			data.resize(mListConnection.size());
			memcpy(&data[0], &mListConnection[0], mListConnection.size());
			mListConnection.clear();
		}
		mInternalMutex.unlock();

		// send event.
		for (int& connection : data)
		{
			for (const sConnectionCallback& var : mListCallback)
			{
				var.mCallbackFunction(var.mCaller, connection);
			}
		}
	}
}

void ServerSock::RegisterConnectionEvent(void* caller, TCallback funtor)
{
	sConnectionCallback c(caller, funtor);
	mListCallback.push_back(c);
}


void ServerSock::SocketSetup()
{
	mServerSockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (mServerSockfd < 0) 
	{
		printf("ERROR opening socket");
	}

	if (bind(mServerSockfd, (struct sockaddr *) &(mServerAdd),sizeof(mServerAdd)) < 0) 
	{
		printf("ERROR!!!: Fail to bind socket");
	}
    
     listen(mServerSockfd,5);
}



