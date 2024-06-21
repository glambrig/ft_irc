#pragma once

#include "Channel.hpp"
#include "User.hpp"
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
#include <map>

class Server
{
private:
	std::vector<Channel>	_channels;
	std::vector<User>		_users;
	size_t					_port;
	std::string				sPort;
	std::string				sPassword;
public:
	Server();
	Server(const Server& copy);
	Server(int ac, char **av);
	Server& operator=(const Server& rhs);
	~Server();

	void	parseArgs(int ac, char **av);
	void	whoIsMessageFor(const char *buffer, const int i);
	void	handlePollIn(struct pollfd	**pfdsArr, size_t pfdsArrLen, size_t i, int listenfd);
	void	run();
	void	socketSetup(int &listenfd, struct sockaddr_in &servAddr);
	ssize_t recvData(int sockfd, char* buffer, size_t bufferSize);

	bool	errToggle;	//If an error occurs in parsing, this becomes true and program doesn't run
};
