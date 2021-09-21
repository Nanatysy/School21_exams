//
// Created by Debby Willette on 9/21/21.
//

#include "Warlock.hpp"

Warlock::Warlock() : invent(nullptr)
{}

Warlock::Warlock(const Warlock & src)
{
	*this = src;
}

Warlock::Warlock(const std::string & name, const std::string & title) : name
(name), title(title), invent(nullptr)
{
	std::cout << getName() << ": This looks like another boring day." <<
	std::endl;
}

Warlock::~Warlock()
{
	if (invent)
	{
		for (int i = 0; i < this->countInvent(); i++)
			delete invent[i];
		delete invent;
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

	if (!src.invent)
	{
		invent = nullptr;
	}
	else
	{
		int size = src.countInvent();
		int i;

		invent = new ASpell* [size + 2];
		for (i = 0; i < size; i++)
		{
			if (!src.invent[i])
				invent[i] = nullptr;
			else
				invent[i] = src.invent[i]->clone();
		}
		invent[i] = nullptr;
	}

	return (*this);
}

void Warlock::learnSpell(ASpell *spell)
{
	if (!invent)
	{
		invent = new ASpell* [2];
		invent[0] = spell->clone();
		invent[1] = nullptr;
	}
	else
	{
		ASpell **tmp;
		int size = this->countInvent();
		int i;

		tmp = invent;
		invent = new ASpell* [size + 2];
		for (i = 0; i < size; i++)
		{
			if (!tmp[i])
				invent[i] = nullptr;
			else
				invent[i] = tmp[i]->clone();
		}
		invent[i++] = spell->clone();
		invent[i] = nullptr;
		for (i = 0; i < size; i++)
			delete tmp[i];
		delete tmp;
	}
}

int Warlock::countInvent(void) const
{
	int i;

	i = 0;
	if (!invent)
		return (0);
	while (this->invent[i])
		i++;
	return (i);
}

void Warlock::forgetSpell(const std::string & name)
{
	if (!invent)
		return ;

	for (int i = 0; i < this->countInvent(); i++)
	{
		if (invent[i]->getName() == name)
		{
			delete invent[i];
			invent[i] = nullptr;
			// break??
		}
	}
}

void Warlock::launchSpell(const std::string & name, const ATarget &target) const
{
	int i;
	int size;

	size = this->countInvent();
	for (i = 0; i < size; i++)
	{
		if (invent[i]->getName() == name)
		{
			invent[i]->launch(target);
			break;
		}
	}
}

