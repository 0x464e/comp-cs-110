#pragma once
#include "bird.hh"

class Cockatoo : public Bird
{
public:
	Cockatoo();
	static void sing(std::ostream& output);
};

