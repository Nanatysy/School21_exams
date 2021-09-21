//
// Created by Debby Willette on 9/21/21.
//

#include "ASpell.hpp"

ASpell::ASpell() : name(nullptr), effects(nullptr)
{}

ASpell::ASpell(const ASpell &src)
{
	*this = src;
}

ASpell::ASpell(const std::string &name, const std::string &effects) : name
(name), effects(effects)
{}

ASpell::~ASpell()
{}

std::string ASpell::getName(void) const
{
	return (this->name);
}

std::string ASpell::getEffects(void) const
{
	return (this->effects);
}

ASpell &ASpell::operator=(const ASpell &src)
{
	if (this == &src)
		return (*this);
	name = src.getName();
	effects = src.getEffects();
	return (*this);
}

void ASpell::launch(const ATarget &src) const
{
	src.getHitBySpell(*this);
}
