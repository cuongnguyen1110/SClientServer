#pragma once

#include "ISocket.h"
#include "SockConnection.h"
#include <vector>
#include <mutex>
#include <atomic>

class Server
{

	ISocket* mSocket;
	std::vector<SockConnection*> mListConnect;


	void ReceiveData(char* data, size_t size);
	void ReceiveConnection(int connection);

	SockConnection* CreateConnection(int connection);



public:
	Server();
	~Server();

	static bool OnReceiveConnection(void* caller, int connection);
	static void OnReceiveData(void* caller, char* data, size_t size);

	
	void InitServer();
	// connection
};

