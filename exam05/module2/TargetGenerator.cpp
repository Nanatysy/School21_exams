//
// Created by Debby Willette on 9/21/21.
//

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() : invent(nullptr)
{}

TargetGenerator::TargetGenerator(const TargetGenerator &src)
{
	*this = src;
}

TargetGenerator::~TargetGenerator()
{
	if (invent)
	{
		for (int i = 0; i < this->countInvent(); i++)
			delete invent[i];
		delete invent;
	}
}

TargetGenerator &TargetGenerator::operator=(const TargetGenerator &src)
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

		invent = new ATarget* [size + 2];
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

void TargetGenerator::learnTargetType(ATarget *target)
{
	if (!invent)
	{
		invent = new ATarget* [2];
		invent[0] = target->clone();
		invent[1] = nullptr;
	}
	else
	{
		ATarget **tmp;
		int size = this->countInvent();
		int i;

		tmp = invent;
		invent = new ATarget* [size + 2];
		for (i = 0; i < size; i++)
		{
			if (!tmp[i])
				invent[i] = nullptr;
			else
				invent[i] = tmp[i]->clone();
		}
		invent[i++] = target->clone();
		invent[i] = nullptr;
		for (i = 0; i < size; i++)
			delete tmp[i];
		delete tmp;
	}
}

void TargetGenerator::forgetTargetType(const std::string & name)
{
	if (!invent)
		return ;

	for (int i = 0; i < this->countInvent(); i++)
	{
		if (invent[i]->getType() == name)
		{
			delete invent[i];
			invent[i] = nullptr;
			// break??
		}
	}
}

ATarget *TargetGenerator::createTarget(const std::string &name) const
{
	if (!invent)
		return (nullptr);

	for (int i = 0; i < this->countInvent(); i++)
	{
		if (invent[i]->getType() == name)
		{
			return invent[i]->clone();
		}
	}
	return (nullptr);
}

int TargetGenerator::countInvent(void) const
{
	int i;

	i = 0;
	if (!invent)
		return (0);
	while (this->invent[i])
		i++;
	return (i);
}
