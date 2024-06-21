#pragma once

#include "User.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"

class UserManager
{
	private:
		std::map<std::string, int> socketMap;
		std::vector<Channel> channels;

	public:
		UserManager();
		UserManager(const UserManager& copy);
		UserManager& operator=(const UserManager& rhs);
		~UserManager();

		std::map<std::string, int>	getSocketMap() const;
		void sendToOne(User user, std::string message, struct pollfd *pfdsArr, int arrSize);

		void	addUser(User user, int socket);
		void	removeUser(User user);
		Channel* findChanByName(std::string name);

};