#include "SockConnection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

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
	mListioningRunning.exchange(true);
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
		bzero((char*) &(buffer[0]),1024);
		int result = read(mSocketFD, buffer, 1024);
		if (result < 0)
		{
			printf("[Client] Fail to read data");
		}
		else if( result == 0)
		{
			printf("-----------Connection has Closed------------\n");
			Close();
			mListioningRunning.exchange(false);
		}
		else
		{
			//printf("successful to read data \n");
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
		printf("ERROR writing to socket");
	}
	else
	{
		//printf("[SockConnection] Success writing to socket: %s \n", data);
	}
		
}


void SockConnection::RegisterRecieveData(void* caller, TCallback callback)
{
	sRecieveDataCallback sCallback(caller, callback);
	mListCallback.push_back(sCallback);
}