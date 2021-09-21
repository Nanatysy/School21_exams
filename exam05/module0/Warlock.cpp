//
// Created by Debby Willette on 9/21/21.
//

#include <Warlock.hpp>

#include "Warlock.hpp"

Warlock::Warlock() {}

Warlock::Warlock(const Warlock & src)
{
	*this = src;
}

Warlock::Warlock(const std::string & name, const std::string & title) : name
(name), title(title)
{
	std::cout << getName() << ": This looks like another boring day." <<
	std::endl;
}

Warlock::~Warlock()
{
	std::cout << getName() << ": My job here is done!" << std::endl;
}

const std::string & Warlock::getName(void) const
{
	return (this->name);
}

const std::string & Warlock::getTitle(void) const
{
	return (this->title);
}

void Warlock::setTitle(const std::string & src)
{
	this->title = src;
}

void Warlock::introduce() const
{
	std::cout << getName() << ": I am " << getName() << ", " << getTitle() <<
	"!" << std::endl;
}

Warlock & Warlock::operator=(const Warlock & src)
{
	if (this == &src)
		return *this;

	name = src.getName();
	title = src.getTitle();
	return (*this);
}
