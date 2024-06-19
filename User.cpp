// #include "ft_irc.hpp"
#include "User.hpp"

User::User(std::string nickname) : nickname(nickname), status(0), currentChannel(-1)
{
}

User::User(const User& copy)
{
	*this = copy;
}

User& User::operator=(const User& rhs)
{
	if (this != &rhs)
	{
		this->username = rhs.username;
		this->password = rhs.password;
		this->socket = rhs.socket;
		this->status = rhs.status;
		this->currentChannel = rhs.currentChannel;
	}
	return (*this);
}

User::~User()
{
}

// Getters //
std::string	User::getUsername() const
{
	return (this->username);
}

std::string	User::getNickname() const
{
	return (this->nickname);
}

std::string	User::getPassword() const
{
	return (this->password);
}

int			User::getSocket() const
{
	return (this->socket);
}

int			User::getStatus() const
{
	return (this->status);
}

int			User::getCurrentChannel() const
{
	return (this->currentChannel);
}

// Setters //
void		User::setUsername(std::string username)
{
	this->username = username;
}

void		User::setNickname(std::string nickname)
{
	if (nickname.size() > 9)
	{
		std::cerr << "Nickname should be 9 characters max" << std::endl;
	}
	this->nickname = nickname.substr(0, 9);
}

void		User::setPassword(std::string password)
{
	this->password = password;
}

void		User::setSocket(int socket)
{
	this->socket = socket;
}

void		User::setStatus(int status)
{
	this->status = status;
}

void		User::setCurrentChannel(int currentChannel)
{
	this->currentChannel = currentChannel;
}
