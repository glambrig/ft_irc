#include "ModeFlags.hpp"

ModeFlags::ModeFlags()
{
	i.first = 'i';
	t.first = 't';
	k.first = 'k';
	o.first = 'o';
	l.first = 'l';

	i.second = false;
	t.second = false;
	k.second = false;
	o.second = false;
	l.second = false;
}

ModeFlags::ModeFlags(const ModeFlags& copy)
{
	i.first = copy.i.first;
	t.first = copy.t.first;
	k.first = copy.k.first;
	o.first = copy.o.first;
	l.first = copy.l.first;

	i.second = copy.i.second;
	t.second = copy.t.second;
	k.second = copy.k.second;
	o.second = copy.o.second;
	l.second = copy.l.second;
}

ModeFlags& ModeFlags::operator=(const ModeFlags& rhs)
{
	if (this != &rhs)
	{
		ModeFlags(rhs);
	}
	return (*this);
}

ModeFlags::~ModeFlags()
{
}
