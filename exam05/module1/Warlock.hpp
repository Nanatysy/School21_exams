//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_WARLOCK_HPP
#define SCHOOL21_EXAMS_WARLOCK_HPP

#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

class Warlock
{

private:
	std::string name;
	std::string title;
	ASpell **invent;

	Warlock();
	Warlock(const Warlock & src);
	Warlock & operator=(const Warlock & src);

	int countInvent(void) const;

public:
	Warlock(const std::string & name, const std::string & title);
	~Warlock();

	const std::string & getName(void) const;
	const std::string & getTitle(void) const;

	void setTitle(const std::string & src);
	void introduce() const;

	void learnSpell(ASpell *spell);
	void forgetSpell(std::string name);
	void launchSpell(std::string name, ATarget & target) const;

};


#endif //SCHOOL21_EXAMS_WARLOCK_HPP