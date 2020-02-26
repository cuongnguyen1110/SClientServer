#pragma once
#include "ISocket.h"

class Client
{

public:
	Client();
	~Client();

	void SendToServer(char* data, int size);

private:
	ISocket* mSocket;

};

