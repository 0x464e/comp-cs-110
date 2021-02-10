#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& line, const char separator, const bool ignore_empty = false)
{
    vector<string> parts;
    string part;
    for(char c : line)
    {
        if(c == separator)
        {
            if(part.size())
                parts.push_back(part);
            else if (!ignore_empty)
                parts.push_back("");
            part = "";
            continue;
        }
        part += c;
    }
    if(part.size())
        parts.push_back(part);
    else if (!ignore_empty)
        parts.push_back("");
    return parts;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector<std::string> parts = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for(auto part : parts)
        std::cout << part << std::endl;

    std::vector<std::string> parts_no_empty = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for(auto part : parts_no_empty)
        std::cout << part << std::endl;
}
