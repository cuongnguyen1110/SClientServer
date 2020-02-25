#include "SockConnection.h"

SockConnection::SockConnection(int sockFD)
	:mSocketFD(sockFD)
	, mListioningThread(nullptr)
	, mListioningRunning(false)
{
	// start listioning
	mListioningThread = new std::thread(&SockConnection::ListioningThreadLoop);
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


void SockConnection::ListioningThreadLoop()
{
	while (mListioningRunning)
	{
		// read()
		//OnRecieve()
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

}

int SockConnection::Send(void* data)
{
	return -1;
}


void SockConnection::RegisterRecieveData(void* caller, TCallback callback)
{
	sRecieveDataCallback sCallback(caller, callback);
	mListCallback.push_back(sCallback);
}