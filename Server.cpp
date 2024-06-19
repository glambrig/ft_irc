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

#define MAX_CLIENTS 10

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


ssize_t Server::recvData(int sockfd, char* buffer, size_t bufferSize) {
	ssize_t bytesRead = recv(sockfd, buffer, bufferSize, 0);
	if (bytesRead > 0) {
		std::cout << "Reçu " << bytesRead << " bytes" << std::endl;
		buffer[bytesRead] = '\0'; // terminé par un caract nul
	} else if (bytesRead == 0) {
		std::cout << "La connexion a été fermée par le client" << std::endl;
	} else {
		std::cerr << "Erreur lors de la réception des données" << std::endl;
	}
	return bytesRead;
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
	}

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
					int clientfd = accept(listenfd, NULL, NULL);
					if (clientfd < 0)
						throw ("Error accepting connection.");
					struct pollfd temp;
					temp.fd = clientfd;
					temp.events = POLLIN; // | POLLOUT
					if (pfdsArrLen < MAX_CLIENTS)
					{
						std::cout << pfdsArrLen << std::endl;
						pfdsArr[pfdsArrLen] = temp; // ajouter le clientfd au tableau de pollfd
						pfdsArrLen++; // incrementer la taille du tableau
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
						std::cout << "Server received message: " << buff;
						std::cout << "Forwarding message to client..." << std::endl;
					}
				}
			}
			if (pfdsArr[i].revents & POLLOUT)// handlePollOut();
			{
				send(pfdsArr[i].fd, "hi\n", 3, 0);
				continue;
			}
		}
	}
}
