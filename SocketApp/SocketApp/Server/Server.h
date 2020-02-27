#pragma once

#include "ISocket.h"
#include "SockConnection.h"
#include <vector>
#include <mutex>
#include <atomic>
#include <thread>

class Server
{

	ISocket* mSocket;
	std::vector<SockConnection*> mListConnect;


	void ReceiveData(char* data, size_t size);
	void ReceiveConnection(int connection);

	SockConnection* CreateConnection(int connection);

	std::thread* mMainThread;
	std::mutex mMutext;
	std::atomic<bool> mMainThreadRunning;
	std::vector<std::string> mClientMessages;
	std::vector<std::string> mServerDatabase;

	void SaveDataToDB(std::vector<std::string> data);

	void MainLoop();
public:
	Server();
	~Server();

	static bool OnReceiveConnection(void* caller, int connection);
	static void OnReceiveData(void* caller, char* data, size_t size);

	void DumpDB(); // may be just print all data, need a mutex
	void InitServer();
	// connection
};

