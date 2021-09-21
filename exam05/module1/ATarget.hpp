//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_ATARGET_HPP
#define SCHOOL21_EXAMS_ATARGET_HPP

#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget
{

private:
	std::string type;

public:
	ATarget();
	ATarget(const ATarget & src);
	ATarget(const std::string & type);
	virtual ~ATarget();

	const std::string & getType(void) const;

	virtual ATarget *clone(void) const =0;

	void getHitBySpell(const ASpell & src) const;

	ATarget & operator=(const ATarget & src);
};


#endif //SCHOOL21_EXAMS_ATARGET_HPP
