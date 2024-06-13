#pragma once

#include <iostream>
#include <string>
#include <vector>

class Channel
{
private:
	std::string	_name;
	std::string	_key;	//key/password might be NULL
	std::string	_topic;
	std::vector<std::string> _users;
	std::vector<std::string> _operators;

public:
	Channel();
	Channel(const Channel& copy);
	Channel& operator=(const Channel& rhs);
	~Channel();

	void	setName(std::string name);
	void	setKey(std::string name);
	void	setTopic(std::string name);

	std::string	addUser(std::string name);
	std::string	removeUser(std::string name);
	std::vector<std::string>	getUsers() const;
	std::vector<std::string>	getOperators() const;
	std::string	getName() const;
	std::string	getTopic() const;
	std::string	getKey() const;

	int isUserInChannel(std::string name) const;
	int isOperator(std::string name) const;
};

std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& vec);
std::ostream& operator<<(std::ostream& out, const Channel& channel);
