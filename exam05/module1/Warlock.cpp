//
// Created by Debby Willette on 9/21/21.
//

#include "Warlock.hpp"

Warlock::Warlock()
{}

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
	if (!invent.empty())
	{
		std::vector<ASpell *>::iterator it = invent.begin();
		for ( ; it != invent.end(); it++)
				delete *it;
	}
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
	invent = src.invent;

	return (*this);
}

void Warlock::learnSpell(ASpell *spell)
{
	invent.push_back(spell->clone());
}

void Warlock::forgetSpell(std::string name)
{
	if (invent.empty())
		return ;

	std::vector<ASpell *>::iterator it = invent.begin();
	for ( ; it != invent.end(); it++)
	{
		if ((*it)->getName() == name)
		{
			delete *it;
			invent.erase(it);
			return ;
		}
	}
}

void Warlock::launchSpell(std::string name, ATarget &target) const
{
	if (invent.empty())
		return ;

	std::vector<ASpell *>::const_iterator it = invent.begin();
	for ( ; it != invent.end(); it++)
	{
		if ((*it)->getName() == name)
		{
			(*it)->launch(target);
		}
	}
}

