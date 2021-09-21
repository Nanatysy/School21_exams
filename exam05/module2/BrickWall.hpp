//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_BRICKWALL_HPP
#define SCHOOL21_EXAMS_BRICKWALL_HPP

#include "ATarget.hpp"

class BrickWall : public ATarget
{
public:
	BrickWall();
	BrickWall(const BrickWall & src);
	virtual ~BrickWall();

	ATarget *clone(void) const;
};


#endif //SCHOOL21_EXAMS_BRICKWALL_HPP
