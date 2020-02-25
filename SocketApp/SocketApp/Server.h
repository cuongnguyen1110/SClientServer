#pragma once
#include "ISocket.h"
class Server
{

	ISocket* mSocket;

public:
	Server();
	~Server();
	static bool OnReciveConnection(Server* caller, int connection);
	void ReciveConnection(int connection);
	// connection
};

