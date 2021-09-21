//
// Created by Debby Willette on 9/21/21.
//

#include "LittleKid.hpp"

Dummy::Dummy() : ATarget("Target Practice Dummy")
{}

Dummy::Dummy(const Dummy &src) : ATarget(src)
{}

Dummy::~Dummy()
{}

ATarget *Dummy::clone(void) const
{
	return new Dummy(*this);
}
