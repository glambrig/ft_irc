#include "ChannelManager.hpp"
#include <iostream>
#include "Channel.hpp"
#include "User.hpp"

ChannelManager::ChannelManager()
{
}

ChannelManager::~ChannelManager()
{
}

// MODE

// Gestion des Operators
void ChannelManager::addOperator(const std::string& channel, User& user)
{
	Operators[channel].push_back(user);
}

void ChannelManager::removeOperator(const std::string& channel, User& user)
{
	Operators[channel].remove(user);
}

bool ChannelManager::isUserOperator(const std::string& channel, User& user)
{
	if (int(Operators[channel].size() + invited[channel].size()) >= limits[channel])
	{
		return true;
	}

	for (std::list<User>::iterator it = Operators[channel].begin(); it != Operators[channel].end(); ++it)
	{
		if (*it == user)
		{
			return true;
		}
	}
	return false;
}

// Gestion des invitations

void ChannelManager::inviteUser(const std::string& channel, User& user)
{
	invited[channel].push_back(user);
}

void ChannelManager::uninviteUser(const std::string& channel, User& user)
{
	invited[channel].remove(user);
}

bool ChannelManager::isUserInvited(const std::string& channel, User& user)
{
	std::list<User>::iterator it;
	for (it = invited[channel].begin(); it != invited[channel].end(); ++it)
	{
		if (*it == user)
			return true;
	}
	return false;
}

// Gestion des sujets

void ChannelManager::setTopicOn(const std::string& channel, const std::string& topic)
{
	topics[channel] = topic;
}

std::string ChannelManager::getTopic(const std::string& channel)
{
	return topics[channel];
}

// Gestion des mots de passe

void ChannelManager::setPassword(const std::string& channel, const std::string& password)
{
	passwords[channel] = password;
}

bool ChannelManager::checkPassword(const std::string& channel, const std::string& password)
{
	if (passwords[channel] == password)
		return true;
	return false;
}

// Gestion des limites d'utilisateurs

void ChannelManager::setLimit(const std::string& channel, int limit)
{
	limits[channel] = limit;
}

bool ChannelManager::isLimitReached(const std::string& channel)
{
	if (limits[channel] <= 0)
		return false;
	if (int(Operators[channel].size() + invited[channel].size()) >= limits[channel])
		return true;
	return false;
}

// Activation/désactivation des fonctionnalités

void ChannelManager::setPwOn(const std::string& channel, bool on)
{
	pwOn[channel] = on;
}

void ChannelManager::setInvOn(const std::string& channel, bool on)
{
	invOn[channel] = on;
}

// void ChannelManager::setTopicOnOn(const std::string& channel, bool on)
// {
// 	setTopicOnOn[channel] = on;
// }

void ChannelManager::setLimitOn(const std::string& channel, bool on)
{
	limitOn[channel] = on;
}

// ------------------------------------ //

Channel* ChannelManager::findChanByName(const std::string& name)
{
	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (channels[i].getName() == name)
		{
			return &channels[i];
		}
	}
	return NULL;
}
