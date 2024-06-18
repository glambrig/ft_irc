#pragma once

#include "Channel.hpp"
// #include "User.hpp"
class User;
#include <vector>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <stdio.h>

class Server
{
private:
	Channel				*_channels;	//Will be _channels[nb_of_channels]
	User				*_users;
	size_t				_port;
	std::string	sPort;
	std::string	sPassword;
public:
	Server();
	Server(const Server& copy);
	Server(int ac, char **av);
	Server& operator=(const Server& rhs);
	~Server();

	void	parseArgs(int ac, char **av);
	void	run();
	void	socketSetup(int &listenfd, struct sockaddr_in &servAddr);
	ssize_t recvData(int sockfd, char* buffer, size_t bufferSize);

	bool	errToggle;	//If an error occurs in parsing, this becomes true and program doesn't run
};
