#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ModeFlags.hpp"
#include "Channel.hpp"
#include "Server.hpp"

class	User
{
	private :
		std::string	username;
		std::string password;
		int 		socket;
		int 		status;
		int			currentChannel;

	public:
		User();
		User(const User& copy);
		User& operator=(const User& rhs);
		~User();

		std::string	getUsername() const;
		std::string	getPassword() const;
		int			getSocket() const;
		int			getStatus() const;
		int			getCurrentChannel() const;

		void		setUsername(std::string username);
		void		setPassword(std::string password);
		void		setSocket(int socket);
		void		setStatus(int status);
		void		setCurrentChannel(int currentChannel);
};
