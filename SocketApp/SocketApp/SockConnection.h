#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

class SockConnection
{
	int mSocketFD;
	std::thread* mListioningThread;
	std::mutex mMutex;
	std::atomic<bool> mListioningRunning;

	typedef void(*TCallback) (void* caller, char* data, size_t size);

	struct sRecieveDataCallback
	{
		void* mCaller;
		TCallback mCallbackFunction;
		sRecieveDataCallback(void* caller, TCallback cb)
		{
			mCaller = caller;
			mCallbackFunction = cb;
		}
	};

	std::vector<sRecieveDataCallback> mListCallback;

	void ListioningThreadLoop();

	SockConnection();

public:
	SockConnection(int sockFD);
	~SockConnection();

	void Close();
	int Send(void* data);
	void OnReceive(char* data, int size);

	void RegisterRecieveData(void* caller, TCallback callback);


};

