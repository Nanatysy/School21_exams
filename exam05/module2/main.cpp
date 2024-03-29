//
// Created by Debby Willette on 9/21/21.
//

#include "Warlock.hpp"
#include "Fwoosh.hpp"
#include "Dummy.hpp"
#include "Polymorph.hpp"
#include "BrickWall.hpp"
#include "Fireball.hpp"
#include "SpellBook.hpp"
#include "TargetGenerator.hpp"

int main()
{
	Warlock richard("Richard", "foo");
	richard.setTitle("Hello, I'm Richard the Warlock!");
	BrickWall model1;

	Polymorph* polymorph = new Polymorph();
	TargetGenerator tarGen;

	tarGen.learnTargetType(&model1);
	richard.learnSpell(polymorph);

	Fireball* fireball = new Fireball();

	richard.learnSpell(fireball);
	richard.learnSpell(fireball);
	richard.learnSpell(fireball);

	ATarget* wall = tarGen.createTarget("Inconspicuous Red-brick Wall");

	richard.introduce();
	richard.launchSpell("Polymorph", *wall);
	richard.launchSpell("Fireball", *wall);
	richard.forgetSpell("Fireball");
	richard.launchSpell("Fireball", *wall);

//	ATarget* wall2 = tarGen.createTarget("Inconspicuous Red-brick Wall");

	delete wall; // subject main leak

	wall = tarGen.createTarget("Inconspicuourick Wall");
	richard.launchSpell("Polymorph", *wall); // so dumb

	delete wall;
}
