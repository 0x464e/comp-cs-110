#pragma once
#include "mammal.hh"

class Giraffe : public Mammal
{
public:
	Giraffe();
	static void make_noise(std::ostream& output);
};

