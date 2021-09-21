//
// Created by Debby Willette on 9/21/21.
//

#include "Warlock.hpp"
#include "Fwoosh.hpp"
#include "LittleKid.hpp"

int main()
{
	Warlock richard("Richard", "the Titled");

	Dummy bob;
	Fwoosh* fwoosh = new Fwoosh();

	richard.learnSpell(fwoosh);

	richard.introduce();
	richard.launchSpell("Fwoosh", bob);

	richard.forgetSpell("Fwoosh");
	richard.launchSpell("Fwoosh", bob);
	return (0);
}
