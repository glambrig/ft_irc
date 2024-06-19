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

void addUser(User user, int sockfd)
{
	socketpair[user.getNickname()] = sockfd;
}

void UserManager::sendToOne(User user, std::string message, struct pollfd *pfdsArr, int arrSize)
{
	if (pfdsArr == NULL || arrSize <= 0)
	{
		std::cout << "Invalid arguments" << std::endl;
		return;
	}
	if (socketMap.find(user.getNickname()) != socketMap.end())
	{
		int pfdsIndex = 0; // Assuming you want to start from the first index, adjust as necessary
		// Ensure pfdsIndex is within bounds and find the correct index based on your logic
		// This is a placeholder logic. You need to implement how you find the correct pfdsIndex based on your application's logic
		if (pfdsIndex < arrSize)
		{
			ssize_t byteSent = send(pfdsArr[pfdsIndex].fd, message.c_str(), message.length(), 0);
			// Use byteSent or suppress unused variable warning
			(void)byteSent; // Suppress unused variable warning if byteSent is not used elsewhere
		}
	}
}
