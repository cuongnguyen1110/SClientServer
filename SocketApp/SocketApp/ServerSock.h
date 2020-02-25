#pragma once
#include "ISocket.h"

#include <vector>;
#include <thread>;
#include <atomic>
#include <mutex>;

class ServerSock :
	public ISocket
{
public:
	void Setup(ISocket::SsocketConfig cf);
	void ServerSetup(); // specific for client

	void StartListen(); // start a thread to listion to client.

private:

	typedef bool(*TCallback) (void* caller, int connection );

	/*int(*functor(char* param1, float param2)) ;*/
	std::thread* mListioningThread;
	std::thread* mMainThread;
	std::atomic<bool> mListioningLoopRunning;
	std::atomic<bool> mMainLoopRunning;

	void OnClientConnected(int clientSockFD);
	void RegisterConnectionEvent(void* caller, TCallback funtor);
	void ListioningLoop(); /// while(true) { accect }
	void MainLoop();// 

	std::vector<int> mListConnection;
	std::mutex mInternalMutex;

	struct sConnectionCallback
	{
		void* mCaller;
		TCallback mCallbackFunction;
		sConnectionCallback(void* caller, TCallback cf)
		{
			mCaller = caller;
			mCallbackFunction = cf;
		}
	};

	std::vector<sConnectionCallback>  mListCallback;

};

