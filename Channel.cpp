#include "Channel.hpp"
#include <algorithm>

Channel::Channel(std::string &nickname) : _name(nickname)
{
}

Channel::Channel(const Channel& copy)
{
	*this = copy;
}

Channel& Channel::operator=(const Channel& rhs)
{
	if (&rhs != this)
		*this = rhs;
	return (*this);
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_key = rhs._key;
		this->_topic = rhs._topic;
		this->_users = rhs._users;
	}
	return (*this);
}

Channel::~Channel()
{
}

//---------------------- setters --------------------------//

void	Channel::setName(std::string name)
{
	_name = name;
}

void	Channel::setKey(std::string key)
{
	_key = key;
}

void	Channel::setTopic(std::string topic)
{
	_topic = topic;
}


//-------------- add/remove user -----------------//

std::string	Channel::addUser(std::string name)
{
	_users.push_back(name);
	return (name);
}

std::string	Channel::removeUser(std::string name)
{
	std::vector<std::string>::iterator it = std::find(_users.begin(), _users.end(), name);
	if (it == _users.end())
		return ("User not found");
	_users.erase(it);
	return (name);
}

//-------------- getters -----------------//

std::vector<std::string>	Channel::getUsers() const
{
	return (_users);
}

std::vector<std::string>	Channel::getOperators() const
{
	return (_operators);
}

std::vector<std::string>	Channel::getChannels() const
{
	return (_channels);
}


std::string	Channel::getName() const
{
	return (_name);
}

std::string	Channel::getTopic() const
{
	return (_topic);
}

std::string	Channel::getKey() const
{
	return (_key);
}

//-------------- functions -----------------//

int		Channel::isUserInChannel(std::string name) const
{
	int index = 0;
	for (std::vector<std::string>::const_iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (*it == name)
			return (index);
		index++;
	}
	return (-1);
}

int		Channel::isOperator(std::string name) const
{
	int index = 0;
	for (std::vector<std::string>::const_iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if (*it == name)
			return (index);
		index++;
	}
	return (-1);
}

//-------------- operator surcharge -----------------//

// Pour std::vector<std::string>
std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& vec)
{
	for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		out << *it << ' ';
	}
	return out;
}

// Pour Channel
std::ostream& operator<<(std::ostream& out, const Channel& channel)
{
	out << channel.getName() << std::endl;
	out << channel.getKey() << std::endl;
	out << channel.getTopic() << std::endl;
	out << channel.getUsers() << std::endl;
	return out;
}
