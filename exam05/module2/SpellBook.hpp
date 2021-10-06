//
// Created by Debby Willette on 9/21/21.
//

#ifndef SCHOOL21_EXAMS_SPELLBOOK_HPP
#define SCHOOL21_EXAMS_SPELLBOOK_HPP

#include "ASpell.hpp"
#include <vector>


class SpellBook
{
private:
	std::vector<ASpell *> invent;

	SpellBook(const SpellBook & src);
	SpellBook & operator=(const SpellBook & src);

public:
	SpellBook();
	virtual ~SpellBook();

	void learnSpell(ASpell *spell);
	void forgetSpell(const std::string & name);
	ASpell *createSpell(const std::string & name) const;
};


#endif //SCHOOL21_EXAMS_SPELLBOOK_HPP
