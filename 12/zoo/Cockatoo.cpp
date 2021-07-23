#include "cockatoo.hh"

Cockatoo::Cockatoo() = default;

void Cockatoo::sing(std::ostream& output)
{
	output << "Kee-ow kee-ow!" << std::endl;
}
