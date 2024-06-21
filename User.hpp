#pragma once

#include <iostream>
#include <string>


typedef struct	User
{
	std::string	username;
	std::string	nickname;
	int 		socket;

	void		setup(const std::string &buff);
}	User;


	// public:
	// 	User();
	// 	User(const User& copy);
	// 	User& operator=(const User& rhs);
	// 	~User();

	// 	std::string	getUsername() const;
	// 	std::string	getNickname() const;
	// 	std::string	getPassword() const;
	// 	int			getSocket() const;
	// 	bool		getisConnected() const;
	// 	int			getCurrentChannel() const;

	// 	void		setUsername(std::string username);
	// 	void		setNickname(std::string nickname);
	// 	void		setPassword(std::string password);
	// 	void		setSocket(int socket);
	// 	void		setisConnected(bool isConnected);
	// 	void		setCurrentChannel(int currentChannel);
