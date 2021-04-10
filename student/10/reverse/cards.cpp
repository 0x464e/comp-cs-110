#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards() : top_(nullptr) 
{
}


void Cards::add(int id) 
{
	const auto new_card = std::make_shared<Card_data>(Card_data{ id, top_ });
	top_ = new_card;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Cards::print(std::ostream& s)
{
	auto to_be_printed = top_;
	auto nr = 1;

	while (to_be_printed != nullptr) 
	{
		s << nr << ": " << to_be_printed->data << std::endl;
		to_be_printed = to_be_printed->next;
		++nr;
	}
}

bool Cards::remove(int& id)
{
	if (top_ == nullptr)
		return false;

	id = top_->data;
	auto to_be_deleted = top_;

	top_ = top_->next;
	to_be_deleted = nullptr;

	return true;
}

void Cards::reverse()
{
	recursive_reverse(top_)->next = nullptr;
}

std::shared_ptr<Cards::Card_data> Cards::recursive_reverse(std::shared_ptr<Card_data> ptr)
{
	if(!ptr->next)
		return top_ = ptr;
		
	auto i = recursive_reverse(ptr->next);
	i->next = ptr;
	return ptr;
}

