//
// Created by Debby Willette on 9/21/21.
//

#include "BrickWall.hpp"

BrickWall::BrickWall() : ATarget("Inconspicuous Red-brick Wall")
{}

BrickWall::BrickWall(const BrickWall &src) : ATarget(src)
{}

BrickWall::~BrickWall()
{}

ATarget *BrickWall::clone(void) const
{
	return new BrickWall(*this);
}
