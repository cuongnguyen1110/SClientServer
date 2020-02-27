#include "SockConnection.h"

SockConnection::SockConnection(int sockFD)
	:mSocketFD(sockFD)
	, mListioningThread(nullptr)
	, mListioningRunning(false)
{
	
}

SockConnection::~SockConnection()
{
	Close();
	if (mListioningThread != nullptr)
	{
		mListioningRunning.exchange(false);
		if (mListioningThread->joinable())
		{
			mListioningThread->join();
		}

		delete mListioningThread;
	}
}

// NOTE: this is not a thread-safe function, dont call this function in multithread.
void SockConnection::StartListioning()
{
	if (mListioningThread == nullptr)
	{
		// start listioning
		mListioningThread = new std::thread(&SockConnection::ListioningThreadLoop, this);
	}
}


void SockConnection::ListioningThreadLoop()
{
	while (mListioningRunning)
	{
		char buffer[1024];
		int result = read(mSocketFD, buffer, 1024);
		if (result < 0)
		{
			printf("[Client] Fail to read data");
		}
		else
		{
			printf("[Client] successful to read data");
			OnReceive(buffer, result);
		}
	}
}

void SockConnection::OnReceive(char* data, int size)
{
	for (sRecieveDataCallback& cb : mListCallback)
	{
		cb.mCallbackFunction(cb.mCaller, data, size);
	}
}

void SockConnection::Close()
{
	shutdown(mSocketFD, SHUT_RD);
	close(mSocketFD);
}

int SockConnection::Send(void* data, int size)
{
	int result = write(mSocketFD, data, size);
	if (result < 0)
	{
		printf("[Client] ERROR writing to socket");
	}
	else
	{
		printf("[Client] Success writing to socket: %s", data);
	}
		
}


void SockConnection::RegisterRecieveData(void* caller, TCallback callback)
{
	sRecieveDataCallback sCallback(caller, callback);
	mListCallback.push_back(sCallback);
}