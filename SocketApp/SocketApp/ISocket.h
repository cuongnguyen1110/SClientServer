#pragma once
#include <sys/socket.h>

class ISocket
{
public:
	struct SsocketConfig
	{
		int port, sockFD;
		struct sockaddr_in serverAddr;
	};

	virtual void Setup(SsocketConfig cf);
};

