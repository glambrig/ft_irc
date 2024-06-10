#pragma once

#include <utility>

struct ModeFlags
{
	std::pair<char, bool>	i;
	std::pair<char, bool>	t;
	std::pair<char, bool>	k;
	std::pair<char, bool>	o;
	std::pair<char, bool>	l;
	ModeFlags();
	ModeFlags(const ModeFlags& copy);
	ModeFlags& operator=(const ModeFlags& rhs);
	~ModeFlags();
};