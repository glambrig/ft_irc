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
		this->_username = rhs.getUsername();
		this->_password = rhs.getPassword();
		this->_socket = rhs.getSocket();
		this->_isConnected = rhs.getisConnected();
		this->_currentChannel = rhs.getCurrentChannel();
	}
	return (*this);
}

User::~User()
{
}

//------------------------- Getters -------------------------//

std::string	User::getUsername() const
{
	return (this->_username);
}

std::string	User::getNickname() const
{
	return (this->_nickname);
}

std::string	User::getPassword() const
{
	return (this->_password);
}

int			User::getSocket() const
{
	return (this->_socket);
}

bool		User::getisConnected() const
{
	return (this->_isConnected);
}

int			User::getCurrentChannel() const
{
	return (this->_currentChannel);
}

//------------------------------ Setters ----------------------------//

void		User::setUsername(std::string username)
{
	this->_username = username;
}

void		User::setNickname(std::string nickname)
{
	std::string temp;

	if (nickname.size() > 9)
	{
		std::cerr << "Nickname should be 9 characters max" << std::endl;
	}
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if (nickname[i + 1] == '\r')
		{
			_nickname = temp;
			return ;
		}
		temp[i] = nickname[i];
	}
}

void		User::setPassword(std::string password)
{
	this->_password = password;
}

void		User::setSocket(int socket)
{
	this->_socket = socket;
}

void		User::setisConnected(bool isConnected)
{
	this->_isConnected = isConnected;
}

void		User::setCurrentChannel(int currentChannel)
{
	this->_currentChannel = currentChannel;
}

bool operator==(const User& lhs, const User& rhs)
{
	return (lhs.getNickname() == rhs.getNickname());
}

// -----------------------------------//

bool User::operator==(const User& rhs) const
{
	return (this->nickname == rhs.nickname);
}
