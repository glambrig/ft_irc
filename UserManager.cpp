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

	const size_t maxMessageSize = 512;

	if (message.length() > maxMessageSize)
	{
		std::cout << "Message too long, cannot send to " << user.getNickname() << std::endl;
		return;
	}

	std::map<std::string, int>::const_iterator it = socketMap.find(user.getNickname());
	if (it != socketMap.end())
	{
		int sockfd = it->second; // Récupère le socket associé à l'utilisateur
		for (int i = 0; i < arrSize; i++)
		{
			if (pfdsArr[i].fd == sockfd)
			{
				ssize_t bytes_sent = send(sockfd, message.c_str(), message.length(), 0);
				if (bytes_sent == -1)
				{
					std::cout << "Fail to send message to " << user.getNickname() << std::endl;
				}
				else
				{
					std::cout << "Message onetoone sent to " << user.getNickname() << std::endl;
				}
				return;
			}
		}
	}
	std::cout << "User not found or invalid socket" << std::endl;
}

Channel* UserManager::findChanByName(std::string name)
{
	for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->getName() == name)
		{
			return &(*it);
		}
	}
	return NULL;
}
