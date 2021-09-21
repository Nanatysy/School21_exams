//
// Created by Debby Willette on 9/21/21.
//

#include "SpellBook.hpp"

SpellBook::SpellBook() : invent(nullptr)
{}

SpellBook::SpellBook(const SpellBook &src)
{
	*this = src;
}

SpellBook::~SpellBook()
{
	if (invent)
	{
		for (int i = 0; i < this->countInvent(); i++)
			delete invent[i];
		delete invent;
	}
}

SpellBook &SpellBook::operator=(const SpellBook &src)
{
	if (this == &src)
		return (*this);

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

	return *this;
}

void SpellBook::learnSpell(ASpell *spell)
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

void SpellBook::forgetSpell(const std::string & name)
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

ASpell* SpellBook::createSpell(const std::string & name) const
{
	if (!invent)
		return (nullptr);

	for (int i = 0; i < this->countInvent(); i++)
	{
		if (invent[i]->getName() == name)
		{
			return invent[i]->clone();
		}
	}
	return (nullptr);
}

int SpellBook::countInvent(void) const
{
	int i;

	i = 0;
	if (!invent)
		return (0);
	while (this->invent[i])
		i++;
	return (i);
}

