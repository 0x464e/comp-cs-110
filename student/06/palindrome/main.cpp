#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
	RECURSIVE_FUNC

	if (s.length() < 1)
		return true;

	if (s.at(s.length() - 1) == s.at(0))
		return palindrome_recursive(s.substr(1, s.length() - 2));	
	return false;
}

#ifndef UNIT_TESTING
int main()
{
	std::cout << "Enter a word: ";
	std::string word;
	std::cin >> word;

	if (palindrome_recursive(word)) {
		std::cout << word << " is a palindrome" << std::endl;
	}
	else {
		std::cout << word << " is not a palindrome" << std::endl;
	}
}
#endif
