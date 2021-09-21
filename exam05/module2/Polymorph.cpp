//
// Created by Debby Willette on 9/21/21.
//

#include "Polymorph.hpp"

Polymorph::Polymorph() : ASpell("Polymorph", "turned into critter")
{}

Polymorph::Polymorph(const Polymorph &src) : ASpell(src)
{}

Polymorph::~Polymorph()
{}

ASpell *Polymorph::clone(void) const
{
	return new Polymorph(*this);
}