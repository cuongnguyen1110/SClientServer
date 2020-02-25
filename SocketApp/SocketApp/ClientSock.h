#pragma once
#include "ISocket.h"

class ClientSock :
	public ISocket
{

public:
	ClientSock();
	virtual ~ClientSock();
	void SocketSetup();

	int Connect();

private:
	int mClientSockfd;

};

