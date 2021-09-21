//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_POLYMORPH_HPP
#define SCHOOL21_EXAMS_POLYMORPH_HPP

#include "ASpell.hpp"

class Polymorph : public ASpell
{
public:
	Polymorph();
	Polymorph(const Polymorph & src);
	virtual ~Polymorph();

	ASpell *clone(void) const;
};


#endif //SCHOOL21_EXAMS_POLYMORPH_HPP
