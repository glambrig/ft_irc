#include "Channel.hpp"

Channel::Channel()
{

}

Channel::Channel(const Channel& copy)
{

}

Channel& Channel::operator=(const Channel& rhs)
{

}

Channel::~Channel()
{
}

void	Channel::setName(std::string name)
{
	_name = name;
}

void	Channel::setKey(std::string key)
{
	_name = key;
}

void	Channel::setTopic(std::string topic)
{
	_name = topic;
}

void	Channel::changeFlag(const char c, bool toggle)
{
	if (c != 'i' && c != 't' && c != 'k' && c != 'o' && c != 'l')
	{
		std::cerr << "Channel::changeFlag: Invalid flag provided" << std::endl;
		return ;
	}
	switch (c)
	{
		case 'i':
			_modeFlags.i.second = toggle;
			break ;
		case 't':
			_modeFlags.t.second = toggle;
			break ;
		case 'k':
			_modeFlags.k.second = toggle;
			break ;
		case 'o':
			_modeFlags.o.second = toggle;
			break ;
		case 'l':
			_modeFlags.l.second = toggle;
			break ;
		default :
			throw ("Channel::changeFlag: Unable to change flag");
			break ;
	}
}
