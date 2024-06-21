#pragma once

#include "channel.hpp"
#include "User.hpp"
#include <map>
#include <list>
#include <string>

class ChannelManager
{
	private:
	std::map<std::string, std::list<User> > Operators; // Corrected
	std::map<std::string, std::list<User> > invited; // Corrected
	std::map<std::string, std::string> topics;
	std::map<std::string, std::string> passwords;

		// Indicateurs
		std::map<std::string, bool> pwOn;
		std::map<std::string, bool> invOn;
		std::map<std::string, bool> topicOn;
		std::map<std::string, int> limits;
		std::map<std::string, bool> limitOn;

	public:
		ChannelManager();
		~ChannelManager();

	std::vector<Channel> channels;

	Channel* findChanByName(const std::string& name);

// MODE
		// Gestion des Operators
		void addOperator(const std::string& channel, User& user);
		void removeOperator(const std::string& channel, User& user);
		bool isUserOperator(const std::string& channel, User& user);

		// Gestion des invitations
		void inviteUser(const std::string& channel, User& user);
		void uninviteUser(const std::string& channel, User& user);
		bool isUserInvited(const std::string& channel, User& user);

		// Gestion des sujets
		void setTopicOn(const std::string& channel, const std::string& topic);
		std::string getTopic(const std::string& channel);

		// Gestion des mots de passe
		void setPassword(const std::string& channel, const std::string& password);
		bool checkPassword(const std::string& channel, const std::string& password);

		// Gestion des limites d'utilisateurs
		void setLimit(const std::string& channel, int limit);
		bool isLimitReached(const std::string& channel);

		// Activation/désactivation des fonctionnalités
		void setPwOn(const std::string& channel, bool on);
		void setInvOn(const std::string& channel, bool on);
		void setTopicOnOn(const std::string& channel, bool on);
		void setLimitOn(const std::string& channel, bool on);
};
