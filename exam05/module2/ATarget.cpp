//
// Created by Debby Willette on 9/21/21.
//

#include "ATarget.hpp"

ATarget::ATarget() : type(nullptr)
{}

ATarget::ATarget(const ATarget &src)
{
	*this = src;
}

ATarget::ATarget(const std::string &type) : type(type)
{}

ATarget::~ATarget()
{}

const std::string &ATarget::getType(void) const
{
	return (this->type);
}

ATarget &ATarget::operator=(const ATarget &src)
{
	if (this == &src)
		return (*this);
	type = src.getType();
	return (*this);
}

void ATarget::getHitBySpell(const ASpell &src) const
{
	std::cout << getType() << " has been " << src.getEffects() << "!" <<
	std::endl;
}
