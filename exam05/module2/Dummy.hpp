//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_LITTLEKID_HPP
#define SCHOOL21_EXAMS_LITTLEKID_HPP

#include "ATarget.hpp"

class Dummy : public ATarget
{
public:
	Dummy();
	Dummy(const Dummy & src);
	virtual ~Dummy();

	ATarget *clone(void) const;
};


#endif //SCHOOL21_EXAMS_LITTLEKID_HPP
