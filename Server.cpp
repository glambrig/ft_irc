#include "Server.hpp"

Server::Server()
{

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

#define MAX_CLIENTS 5

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

// void	handlePollIn(int listenfd, struct pollfd **pfdsArr)

// typedef struct usr
// {
// 	struct pollfd	pollfd;
// 	int				id;
// }	usr;

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

	// usr				*usrs = new usr[MAX_CLIENTS];
	struct pollfd	*pfdsArr = new struct pollfd[MAX_CLIENTS];
	struct pollfd	pfd;
	pfd.fd = listenfd;
	pfd.events = POLLIN | POLLOUT;
	pfdsArr[0] = pfd;

	for (size_t i = 1; i < MAX_CLIENTS; i++)
		pfdsArr[i].fd = 0;

	char	buff[512];
	
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
			if (pfdsArr[i].revents & POLLIN) // handlePollIn();
			{
				if (pfdsArr[i].fd == listenfd)
				{
					//Set up incoming connection
					std::cout << "Incoming connection" << std::endl;
					int clientfd = accept(listenfd, NULL, NULL);
					if (clientfd < 0)
						throw ("Error accepting connection.");
					struct pollfd temp;
					temp.fd = clientfd;
					temp.events = POLLIN; // | POLLOUT
					if (pfdsArrLen < MAX_CLIENTS)
					{
						std::cout << pfdsArrLen << std::endl;
						pfdsArr[pfdsArrLen] = temp;	//this causes fd problems because index is wrong
						// usrs[i].pollfd = temp;
						// usrs[i].id = i;
						// std::cout << "ID of newly connected user is " << i << std::endl;
					}
					else
					{
						std::cout << "Too many clients." << std::endl;
						for (int k = 0; k < MAX_CLIENTS; k++)
							close(pfdsArr[k].fd);
						return ;
					}
				}
				else
				{
					int recvRes = recv(pfdsArr[i].fd, &buff, 512, 0);
					if (recvRes <= 0)
					{
						close(pfdsArr[i].fd);
						// reallocArr(pfdsArr, i);
						if (recvRes == 0)
							std::cout << "Client disconnected" << std::endl;
						else if (recvRes < 0)
							throw ("Error receiving from fd");
					}
					else
					{
						std::cout << "Server received message: " << buff 
							<< "Forwarding message to client..." << std::endl;
						send(pfdsArr[pfdsArrLen - i].fd, &buff, strlen(buff), 0);
						std::cout << "sent message!" << std::endl;
					}
				}
			}
			if (pfdsArr[i].revents & POLLOUT)// handlePollOut();
			{
				std::cout << "Something on POLLOUT." << std::endl;
				send(pfdsArr[i].fd, "hi\n", 3, 0);
				continue;
			}
			for (size_t k = 0; k < 512; k++)
				buff[k] = '\0';
		}
	}
}

// typedef struct usrs
// {
// 	struct pollfd 	pfd;
// 	int				id;
// }	usrs;

	// try
	// {
	// 	socketSetup(listenfd, servAddr);

	// 	std::vector<usrs>	fds;
	// 	usrs s_pollfd;

	// 	s_pollfd.id = -1;
	// 	s_pollfd.pfd.fd = listenfd;
	// 	s_pollfd.pfd.events = POLLIN | POLLOUT;
	// 	s_pollfd.pfd.revents = 0;

	// 	fds.push_back(s_pollfd);
	// 	char buff[512];
	// 	std::cout << "Server is running." << std::endl;

	// 	while (true)
	// 	{
	// 		std::cout << "Beginning of infinite loop" << std::endl;
	// 		int pollCount = poll(&fds, fds.size(), -1);
	// 		if (pollCount < 0)
	// 			throw ("Error in poll()");
	// 		for (size_t i = 0; i < fds.size(); i++)
	// 		{
	// 			if (fds[i].pfd.revents & POLLIN)
	// 			{
	// 				if (fds[i].pfd.fd == listenfd)
	// 				{
	// 					//Set up incoming connection
	// 					std::cout << "Setting up incoming connection" << std::endl;
	// 					int clientfd = accept(listenfd, NULL, NULL);
	// 					if (clientfd < 0)
	// 						throw ("Error accepting connection.");
	// 					usrs temp;
	// 					temp.pfd.fd = clientfd;
	// 					temp.pfd.events = POLLIN;
	// 					temp.id = 0;
	// 					fds.push_back(temp);
	// 					std::cout << "End." << std::endl;
	// 				}
	// 				else
	// 				{
	// 					//Existing client
	// 					std::cout << "Existing client. Handling data." << std::endl;
	// 					if (recv(fds[i].pfd.fd, &buff, 1023, 0) <= 0)
	// 					{
	// 						std::cout << "Client disconnected." << std::endl;
	// 						close(fds[i].pfd.fd);
	// 						fds.erase(fds.begin() + i);
	// 					}
	// 					else
	// 					{
	// 						std::cout << buff;

	// 						//find out who the message is for
	// 						//syntax: id message
	// 						if (fds.size() >= 3)
	// 						{
	// 							send(buff[0] - '0', &buff, sizeof(char) * sizeof(buff), 0);
	// 							std::cout << "message sent!" << std::endl;
	// 						}
	// 						else
	// 							std::cout << "not enough clients" << std::endl;
	// 					}
	// 					//Clear buffer
	// 					for (size_t k = 0; k < 512; k++)
	// 							buff[k] = '\0';
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// catch (const char *e)
	// {
	// 	// std::cerr << e << std::endl;
	// 	perror(e);	//Not allowed, remove later
	// }