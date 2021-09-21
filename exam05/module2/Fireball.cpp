//
// Created by Debby Willette on 9/21/21.
//

#include "Fireball.hpp"

Fireball::Fireball() : ASpell("Fireball", "burnt to a crisp")
{}

Fireball::Fireball(const Fireball &src) : ASpell(src)
{}

Fireball::~Fireball()
{}

ASpell *Fireball::clone(void) const
{
	return new Fireball(*this);
}