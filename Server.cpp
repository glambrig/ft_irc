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

#define MAX_CLIENTS 2

void	Server::run()
{
	int					listenfd;	//welcoming socket that all clients will initially connect to before getting their own socket
	int					clientfd[MAX_CLIENTS];	//New socket of accepted connections 
	struct sockaddr_in	servAddr;	//Address the server will listen on

	try
	{
		listenfd = socket(AF_INET, SOCK_STREAM, 0);
		if (listenfd < 0)
			throw ("Server::run::Error creating socket.");
		servAddr.sin_family = AF_INET;	//Expecting an internet address (ip)
		servAddr.sin_port = htons(_port);	//Incoming connections on port _port (specified by user)
		servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//Accept connections from any IP address
		if (bind(listenfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
			throw ("Server::run::Error binding address to socket.");
		if (listen(listenfd, MAX_CLIENTS) < 0)
			throw ("Server::run::Error listening for connections.");
		for (size_t i = 0; true; i++)
		{
			// poll()
			std::cout << "Waiting for connection on port " << _port << std::endl;
			clientfd[i] = accept(listenfd, (struct sockaddr *)NULL, NULL);
			if (clientfd[i] < 0)
				throw ("Server::run::Error accepting connection.");
			std::cout << "GOT CONNECTION!!" << std::endl;
		}
	}
	catch (const char *e)
	{
		// std::cerr << e << std::endl;
		perror(e);	//Not allowed, remove later
	}
}