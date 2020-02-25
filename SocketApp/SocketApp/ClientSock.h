#pragma once
#include "ISocket.h"

class ClientSock :
	public ISocket
{

public:

	void SocketSetup();

	int Connect();

private:
	int mClientSockfd;

};

