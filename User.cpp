#include "User.hpp"

// User::User()
// {
// }

// User::User(const User& copy)
// {
// 	*this = copy;
// }

// User& User::operator=(const User& rhs)
// {
// 	if (this != &rhs)
// 	{
// 		this->_username = rhs.getUsername();
// 		this->_password = rhs.getPassword();
// 		this->_socket = rhs.getSocket();
// 		this->_isConnected = rhs.getisConnected();
// 		this->_currentChannel = rhs.getCurrentChannel();
// 	}
// 	return (*this);
// }

// User::~User()
// {
// }

// // Getters //
// std::string	User::getUsername() const
// {
// 	return (this->_username);
// }

// std::string	User::getNickname() const
// {
// 	return (this->_nickname);
// }

// std::string	User::getPassword() const
// {
// 	return (this->_password);
// }

// int			User::getSocket() const
// {
// 	return (this->_socket);
// }

// bool		User::getisConnected() const
// {
// 	return (this->_isConnected);
// }

// int			User::getCurrentChannel() const
// {
// 	return (this->_currentChannel);
// }

// // Setters //
// void		User::setUsername(std::string username)
// {
// 	this->_username = username;
// }

// void		User::setNickname(std::string nickname)
// {
// 	this->_nickname = nickname;
// }

// void		User::setPassword(std::string password)
// {
// 	this->_password = password;
// }

// void		User::setSocket(int socket)
// {
// 	this->_socket = socket;
// }

// void		User::setisConnected(bool isConnected)
// {
// 	this->_isConnected = isConnected;
// }

// void		User::setCurrentChannel(int currentChannel)
// {
// 	this->_currentChannel = currentChannel;
// }

void		User::setup(const std::string &buff)
{
	if (buff.empty() || buff.find('\0') != std::string::npos)
	{
		std::cout << "SOMETHING REALLY BAD HAPPENED" << std::endl;
		return ;
	}
	if (buff.compare(0, 4, "NICK") == 0)
	{
		std::string nick;
		size_t pos = buff.find("\r\n");
		if (pos != std::string::npos)
		{
			nick = buff.substr(pos, buff.length() - pos);
			if (nick.length() > 9)
			this->nickname = nick;
		}
		else
			std::cout << "invalid NICK command" << std::endl;
	}
	// if (buff.compare(0, 4, "USER") == 0)
	// {

	// }
}