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
	mMainThread = new std::thread(&ServerSock::MainLoop); // start main thread
}

void ServerSock::StartListen()
{
	mListioningLoopRunning = true;
	mListioningThread = new std::thread(&ServerSock::ListioningLoop);
}

void ServerSock::ListioningLoop()
{
	while (mListioningLoopRunning)
	{
		//int newConnection = accect(sock);
		// if(newConnection < 0) -> connection error
		//send message. [IMPORTANCE TASK]

		int fakeConnection = -1;
		OnClientConnected(fakeConnection);
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



