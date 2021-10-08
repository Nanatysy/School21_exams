//
// Created by Debby Willette on 9/21/21.
//

#include "SpellBook.hpp"

SpellBook::SpellBook()
{}

SpellBook::SpellBook(const SpellBook &src)
{
	*this = src;
}

SpellBook::~SpellBook()
{
	if (!invent.empty())
	{
		std::vector<ASpell *>::iterator it = invent.begin();
		for ( ; it != invent.end(); it++)
			delete *it;
	}
}

SpellBook &SpellBook::operator=(const SpellBook &src)
{
	if (this == &src)
		return (*this);

	invent = src.invent;

	return *this;
}

void SpellBook::learnSpell(ASpell *spell)
{
	invent.push_back(spell->clone());
	delete spell;
}

void SpellBook::forgetSpell(const std::string & name)
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

ASpell* SpellBook::createSpell(const std::string & name) const
{
	if (invent.empty())
		return (nullptr);

	std::vector<ASpell *>::const_iterator it = invent.begin();
	for ( ; it != invent.end(); it++)
	{
		if ((*it)->getName() == name)
		{
			return (*it)->clone();
		}
	}
	return (nullptr);
}
