#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Channel.hpp"
#include "Server.hpp"

class	User
{
	private:
		std::string	username;
		std::string	nickname;
		std::string password;
		int 		socket;
		int 		status;
		int			currentChannel;

	public:
		User(std::string nickname);
		User(const User& copy);
		User& operator=(const User& rhs);
		~User();

		std::string	getUsername() const;
		std::string	getNickname() const;
		std::string	getPassword() const;
		int			getSocket() const;
		int			getStatus() const;
		int			getCurrentChannel() const;

		void		setUsername(std::string username);
		void		setNickname(std::string nickname);
		void		setPassword(std::string password);
		void		setSocket(int socket);
		void		setStatus(int status);
		void		setCurrentChannel(int currentChannel);
};
