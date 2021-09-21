//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_FWOOSH_HPP
#define SCHOOL21_EXAMS_FWOOSH_HPP

#include "ASpell.hpp"

class Fwoosh : public ASpell
{
public:
	Fwoosh();
	Fwoosh(const Fwoosh & src);
	virtual ~Fwoosh();

	ASpell *clone(void) const;
};


#endif //SCHOOL21_EXAMS_FWOOSH_HPP
