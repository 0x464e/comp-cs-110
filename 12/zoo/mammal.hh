#pragma once
#include "animal.hh"

class Mammal : public Animal
{
public:
	Mammal();
	static void suckle(std::ostream& output);
};