#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Channel.hpp"

class	User
{
	private:
		std::string	_username;
		std::string	_nickname;
		std::string _password;
		int 		_socket;
		bool 		_isConnected;
		int			_currentChannel;

	public:
		User();
		User(const User& copy);
		User& operator=(const User& rhs);
		~User();

		std::string	getUsername() const;
		std::string	getNickname() const;
		std::string	getPassword() const;
		int			getSocket() const;
		bool		getisConnected() const;
		int			getCurrentChannel() const;

		void		setUsername(std::string username);
		void		setNickname(std::string nickname);
		void		setPassword(std::string password);
		void		setSocket(int socket);
		void		setisConnected(bool isConnected);
		void		setCurrentChannel(int currentChannel);

		void		setup(const std::string &buff);
};
