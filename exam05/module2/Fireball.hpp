//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_FIREBALL_HPP
#define SCHOOL21_EXAMS_FIREBALL_HPP

#include "ASpell.hpp"

class Fireball : public ASpell
{
public:
	Fireball();
	Fireball(const Fireball & src);
	virtual ~Fireball();

	ASpell *clone(void) const;
};


#endif //SCHOOL21_EXAMS_FIREBALL_HPP
