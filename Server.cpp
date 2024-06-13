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
		throw ("sock option error");
	if (listenfd < 0)
		throw ("Server::run::Error creating socket.");
	servAddr.sin_family = AF_INET;	//Expecting an internet address (ip)
	servAddr.sin_port = htons(_port);	//Incoming connections on port _port (specified by user)
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//Accept connections from any IP address
	if (bind(listenfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
		throw ("Server::run::Error binding address to socket.");
	if (listen(listenfd, MAX_CLIENTS) < 0)
		throw ("Server::run::Error listening for connections.");
}

void	Server::run()
{
	int					listenfd;	//welcoming socket that all clients will initially connect to before getting their own socket
	struct sockaddr_in	servAddr;	//Address the server will listen on

	try
	{
		socketSetup(listenfd, servAddr);

		std::vector<pollfd>	fds;
		struct pollfd s_pollfd;

		s_pollfd.fd = listenfd;
		s_pollfd.events = POLLIN;
		s_pollfd.revents = 0;

		fds.push_back(s_pollfd);
		char buff[MAX_CLIENTS][1024];//buffer to test i/o
		for (size_t i = 0; i < MAX_CLIENTS; i++)
		{
			for (size_t k = 0; k < 1024; k++)
				buff[i][k] = '\0';
		}
		std::cout << "Server is running." << std::endl;
		while (true)
		{
			int pollCount = poll(&fds[0], fds.size(), -1);
			if (pollCount < 0)
				throw ("Error in poll()");
			for (size_t i = 0; i < fds.size(); i++)
			{
				if (fds[i].revents & POLLIN)
				{
					if (fds[i].fd == listenfd)
					{
						//We have an incoming connection
						std::cout << "INCOMING" << std::endl;
						int clientfd = accept(listenfd, NULL, NULL);
						if (clientfd < 0)
							throw ("Error accepting connection.");
						struct pollfd temp;
						temp.fd = clientfd;
						temp.events = POLLIN;
						temp.revents = 0;
						fds.push_back(temp);
					}
					else
					{
						//Existing client
						if (read(fds[i].fd, &buff[i], 1023) < 0)
						{
							std::cout << "Error reading from client" << std::endl;
							close(fds[i].fd);
							fds.erase(fds.begin() + i);
						}
						else
							std::cout << buff[i];
					}
				}
			}
		}
	}
	catch (const char *e)
	{
		// std::cerr << e << std::endl;
		perror(e);	//Not allowed, remove later
	}
}