#include "giraffe.hh"

Giraffe::Giraffe()
= default;

void Giraffe::make_noise(std::ostream& output)
{
	output << "Ori ori ori!" << std::endl;
}
