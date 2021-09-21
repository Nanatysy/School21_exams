//
// Created by Debby Willette on 9/21/21.
//

#include "Fwoosh.hpp"

Fwoosh::Fwoosh() : ASpell("Fwoosh", "fwooshed")
{}

Fwoosh::Fwoosh(const Fwoosh &src) : ASpell(src)
{}

Fwoosh::~Fwoosh()
{}

ASpell *Fwoosh::clone(void) const
{
	return new Fwoosh(*this);
}