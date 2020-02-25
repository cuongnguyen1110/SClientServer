#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

class ISocket
{
public:
	void Setup( sockaddr_in serveAd ) { mServerAdd = serveAd; };
	virtual void SocketSetup();
protected:

	sockaddr_in mServerAdd;
};

