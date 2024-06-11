#pragma once

#include <iostream>
#include <string>
#include "ModeFlags.hpp"

class Channel
{
private:
	std::string	_name;
	std::string	_key;	//key/password might be NULL
	ModeFlags	_modeFlags;
	std::string	_topic;
public:
	Channel();
	Channel(const Channel& copy);
	Channel& operator=(const Channel& rhs);
	~Channel();

	void	setName(std::string name);
	void	setKey(std::string name);
	void	setTopic(std::string name);
	void	changeFlag(const char c, bool toggle);
};
