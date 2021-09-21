//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_ASPELL_HPP
#define SCHOOL21_EXAMS_ASPELL_HPP

#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell
{

private:
	std::string name;
	std::string effects;

public:
	ASpell();
	ASpell(const ASpell & src);
	ASpell(const std::string & name, const std::string & effects);
	virtual ~ASpell();

	std::string getName(void) const;
	std::string getEffects(void) const;

	virtual ASpell *clone(void) const = 0;

	void launch(const ATarget & src) const;

	ASpell & operator=(const ASpell & src);
};


#endif //SCHOOL21_EXAMS_ASPELL_HPP
