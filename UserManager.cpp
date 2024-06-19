#include "UserManager.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <iostream>

class Server;

UserManager::UserManager()
{
}

UserManager::UserManager(const UserManager& copy)
{
	*this = copy;
}

UserManager& UserManager::operator=(const UserManager& rhs)
{
	if (&rhs != this)
		this->socketMap = rhs.socketMap;
	return (*this);
}

UserManager::~UserManager()
{
}

// -------------------------------------------------------------------//

std::map<std::string, int>	UserManager::getSocketMap() const
{
	return (socketMap);
}

void UserManager::addUser(User user, int sockfd)
{
	socketMap[user.getNickname()] = sockfd;
}

void UserManager::sendToOne(User user, std::string message, struct pollfd *pfdsArr, int arrSize)
{
	std::cout << "Sending message to " << user.getNickname() << std::endl;
	if (pfdsArr == NULL || arrSize <= 0)
	{
		std::cout << "Invalid arguments" << std::endl;
		return;
	}
	if (socketMap.find(user.getNickname()) != socketMap.end())
	{
		int pfdsIndex = 0;

		if (pfdsIndex < arrSize)
		{
			send(pfdsArr[pfdsIndex].fd, message.c_str(), message.length(), 0);
		}
	}
	std::cout << "Message onetoone sent" << std::endl;
}
