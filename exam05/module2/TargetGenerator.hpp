//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_TARGETGENERATOR_HPP
#define SCHOOL21_EXAMS_TARGETGENERATOR_HPP

#include "ATarget.hpp"
#include <vector>

class TargetGenerator
{
private:
	std::vector<ATarget *> invent;

	TargetGenerator(const TargetGenerator & src);
	TargetGenerator & operator=(const TargetGenerator & src);

public:
	TargetGenerator();
	virtual ~TargetGenerator();

	void learnTargetType(ATarget* target);
	void forgetTargetType(std::string const &name);
	ATarget* createTarget(const std::string & name) const;

};


#endif //SCHOOL21_EXAMS_TARGETGENERATOR_HPP
