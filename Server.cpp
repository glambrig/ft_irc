#include "Server.hpp"

#define MAX_CLIENTS 5

Server::Server()
{
	// pfdsArr = new struct pollfd[MAX_CLIENTS];	//can be alloc'd and freed in constructor/destructor
}

Server::Server(const Server& copy)
{
	*this = copy;
}

Server::Server(int ac, char **av)
{
	try
	{
		parseArgs(ac, av);
	}
	catch (const char *e)
	{
		std::cout << e << std::endl;
		errToggle = true;
	}
}

Server& Server::operator=(const Server& rhs)
{
	if (&rhs != this)
		*this = rhs;
	return (*this);
}

Server::~Server()
{
	// delete[] pfdsArr;
}

void	Server::parseArgs(int ac, char **av)
{
	if (ac != 3)
		throw ("Server::parseArgs::Error: Invalid number of arguments");
	sPort = av[1];
	for (size_t i = 0; i < sPort.length(); i++)
	{
		if (isdigit(sPort[i]) == 0)
			throw ("Server::parseArgs::Error: Port is not a number");
	}
	_port = atoi(sPort.c_str());
	if (sPort[0] == '-')
		throw ("Server::parseArgs::Error: Negative port is invalid.");
	if (_port < 1023)
		throw ("Server::parseArgs::Error: Port is \"well known\". (Use 1024-65534)");
	if (_port > 65534)
		throw ("Server::parseArgs::Error: Port > 65534.");
	this->sPassword = av[2];
}


void	Server::socketSetup(int &listenfd, struct sockaddr_in &servAddr)
{
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	int one = 1;

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) < 0)
		throw ("Server::socketSetup::Sock option error");
	if (listenfd < 0)
		throw ("Server::socketSetup::Error creating socket.");
	servAddr.sin_family = AF_INET;	//Expecting an internet address (ip)
	servAddr.sin_port = htons(_port);	//Incoming connections on port _port (specified by user)
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//Accept connections from any IP address
	if (bind(listenfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
		throw ("Server::socketSetup::Error binding address to socket.");
	if (listen(listenfd, MAX_CLIENTS) < 0)
		throw ("Server::socketSetup::Error listening for connections.");
}

void Server::whoIsMessageFor(const char *buffer, const int i)
{
	std::string buff = buffer;

	if (buff.compare(0, 4, "USER") == 0 || buff.compare(0, 4, "NICK") == 0)
	{
		_users[i].setup(buff);
		return ;
	}
	//	Send to everyone
	for (size_t k = 0; k < _users.size(); k++)
	{
		if (_users[k].getSocket() != i)
			send(_users[k].getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
	}
}

void	Server::handlePollIn(struct pollfd	**pfdsArr, size_t pfdsArrLen, size_t i, int listenfd)
{
	char	buff[512];

	if ((*pfdsArr)[i].fd == listenfd)
	{
		//Set up incoming connection
		std::cout << "Incoming connection" << std::endl;
		int clientfd = accept(listenfd, NULL, NULL);
		if (clientfd < 0)
			throw ("Error accepting connection.");

		struct pollfd temp;
		temp.fd = clientfd;
		temp.events = POLLIN;

		if (pfdsArrLen < MAX_CLIENTS)
		{
			std::cout << pfdsArrLen << std::endl;
			(*pfdsArr)[pfdsArrLen] = temp;
			User	newUsr;
			newUsr.setSocket(temp.fd);
			_users.push_back(newUsr);
		}
		else
		{
			std::cout << "Too many clients." << std::endl;
			for (int k = 0; k < MAX_CLIENTS; k++)
				close((*pfdsArr)[k].fd);
			return ;
		}
	}
	else
	{
		int recvRes = recv((*pfdsArr)[i].fd, &buff, 512, 0);
		if (recvRes <= 0)
		{
			close((*pfdsArr)[i].fd);
			// reallocArr(pfdsArr, i);	//need to write this. frees the space taken up by the disconnected client, and realloc's the array
			if (recvRes == 0)
			{
				_users[i].setisConnected(false);
				std::cout << "Client disconnected" << std::endl;
			}
			else if (recvRes < 0)
				throw ("Error receiving from fd");
		}
		else
		{
			std::cout << "Server received message: " << buff 
				<< "Forwarding message to client..." << std::endl;
			whoIsMessageFor(buff, i);
			std::cout << "sent message!" << std::endl;
		}
	}
	for (size_t k = 0; k < 512; k++)
		buff[k] = '\0';
}

void	Server::run()
{
	int					listenfd;	//Server accepts connections on this socket
	struct sockaddr_in	servAddr;

	try
	{
		socketSetup(listenfd, servAddr);
	}
	catch (const char *e)
	{
		std::cout << e << std::endl;
		return ;
	}

	struct pollfd	*pfdsArr = new struct pollfd[MAX_CLIENTS];	//can be alloc'd and freed in constructor/destructor
	struct pollfd	pfd;
	pfd.fd = listenfd;
	pfd.events = POLLIN | POLLOUT;
	pfdsArr[0] = pfd;

	for (size_t i = 1; i < MAX_CLIENTS; i++)
		pfdsArr[i].fd = 0;

	std::cout << "Server is running." << std::endl;
	while (1)
	{
		size_t pfdsArrLen = 0;
		for (size_t i = 0; i < MAX_CLIENTS; i++)
		{
			if (pfdsArr[i].fd == 0)
				break ;
			pfdsArrLen++;
		}
		int pollreturn = poll(pfdsArr, pfdsArrLen, -1);
		if (pollreturn < 0)
			throw ("Poll returned negative value");

		for (size_t i = 0; i < pfdsArrLen; i++)
		{
			if (pfdsArr[i].revents & POLLIN)
				handlePollIn(&pfdsArr, pfdsArrLen, i, listenfd);
			if (pfdsArr[i].revents & POLLOUT)// handlePollOut();
			{
				std::cout << "Something on POLLOUT." << std::endl;
				send(pfdsArr[i].fd, "hi\n", 3, 0);
				continue;
			}
		}
	}
}
