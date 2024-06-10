#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ModeFlags.hpp"
#include "Channel.hpp"
#include "Server.hpp"

struct	UserNames
{
	std::string	nickname;	
	std::string	username;	
	std::string	hostname;	
	std::string	realname;	
};

struct	User
{
	UserNames					userNames;
	std::vector<std::string>	channels;	//List of channels the user is in
	bool						isOperator;
};

