//
// Created by Debby Willette on 9/21/21.
//

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{}

TargetGenerator::TargetGenerator(const TargetGenerator &src)
{
	*this = src;
}

TargetGenerator::~TargetGenerator()
{
	if (!invent.empty())
	{
		std::vector<ATarget *>::iterator it = invent.begin();
		for ( ; it != invent.end(); it++)
				delete *it;
	}
}

TargetGenerator &TargetGenerator::operator=(const TargetGenerator &src)
{
	if (this == &src)
		return (*this);

	invent = src.invent;

	return *this;
}

void TargetGenerator::learnTargetType(ATarget *target)
{
	invent.push_back(target->clone());
}

void TargetGenerator::forgetTargetType(const std::string & name)
{
	if (invent.empty())
		return ;

	std::vector<ATarget *>::iterator it = invent.begin();
	for ( ; it != invent.end(); it++)
	{
		if ((*it)->getType() == name)
		{
			delete *it;
			invent.erase(it);
			return ;
		}
	}
}

ATarget *TargetGenerator::createTarget(const std::string &name) const
{
	if (invent.empty())
		return (nullptr);

	std::vector<ATarget *>::const_iterator it = invent.begin();
	for ( ; it != invent.end(); it++)
	{
		if ((*it)->getType() == name)
		{
			return (*it)->clone();
		}
	}
	return (nullptr);
}
