#pragma once

#include "Channel.hpp"
#include "User.hpp"
#include <ctype.h>
#include <unistd.h>
#include <cstdlib>

class Server
{
private:
	Channel				*_channels;	//Will be _channels[nb_of_channels]
	User				*_users;
	size_t				_port;
	std::string	sPort;
	std::string	sPassword;
	bool				_errToggle;	//If an error occurs in parsing, this becomes true and program doesn't run
public:
	Server();
	Server(const Server& copy);
	Server(int ac, char **av);
	Server& operator=(const Server& rhs);
	~Server();

	void	parseArgs(int ac, char **av);
};