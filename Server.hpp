#pragma once

#include "Channel.hpp"
#include "User.hpp"

class Server
{
private:
	Channel	*_channels;	//Will be _channels[nb_of_channels]
	User	*_users;
public:
	Server();
	Server(const Server& copy);
	Server& operator=(const Server& rhs);
	~Server();
};