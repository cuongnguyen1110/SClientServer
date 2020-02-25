#pragma once
#include "ISocket.h"

class ClientSock :
	public ISocket
{
	void Setup(ISocket::SsocketConfig cf);
	void ClientSetup(); // specific for client

	int Connect();

};

