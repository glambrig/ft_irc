#include "UserManager.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <iostream>

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

void	UserManager::sendToOne(User user, std::string message, struct pollfd *pfdsArr, int arrSize)
{
	if (pfdsArr == NULL || arrSize <= 0)
	{
		std::cout << "Invalid arguments" << std::endl;
		return;
	}
	if (socketMap.find(user.getNickname()) != socketMap.end())
	{
		int pfdsIndex = socketMap[user.getNickname()];
		ssize_t byteSent = 0;
		if (pfdsIndex < arrSize)
			ssize_t byteSent = send(pfdsArr[pfdsIndex].fd, message.c_str(), message.length(), 0);
		if (byteSent < 0)
			std::cout << "Error sending message to " << user.getNickname() << std::endl;
	}
	else
	{
		std::cout << "User not found" << std::endl;
	}
}
