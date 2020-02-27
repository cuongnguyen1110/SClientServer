#pragma once
#include "ISocket.h"


class SockConnection;
class Client
{

public:
	Client();
	~Client();

	void SendToServer(char* data, int size);
	static void OnReceiveData(void* caller, char* data, size_t size);

	bool ConnectToServer();
private:
	ISocket* mSocket;

	SockConnection* mConnection;

	void ReceiveData(char* data, int size);

};

