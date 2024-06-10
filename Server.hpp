#pragma once

#include "Channel.hpp"

class Server
{
private:
	Channel	*_channels;	//Will be _channels[nb_of_channels]
public:
	Server();
	Server(const Server& copy);
	Server& operator=(const Server& rhs);
	~Server();
};