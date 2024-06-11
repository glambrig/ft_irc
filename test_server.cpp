#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

int main()
{
	int server_fd;
	int new_socket;
	int opt = 1;

	struct sockaddr_in address;

	int addrlen = sizeof(address);

	// Création du socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "Socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Liaison du socket à une adresse et un port
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(9999);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Écoute des connexions entrantes
	if (listen(server_fd, 3) < 0)
	{
		std::cerr << "Listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Acceptation des connexions
	while (true)
	{
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
		{
			std::cerr << "Accept failed" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout << "Accepted connection" << std::endl;
		// Gérer la connexion du client ici
		char buffer[1024] = {0};
		read(new_socket, buffer, 1024);
		std::cout << buffer << std::endl;
		// close(new_socket);
	}

	return 0;
}
