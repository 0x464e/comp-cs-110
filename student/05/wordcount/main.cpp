#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>

using namespace std;

int main()
{
	string input_file;
	cout << "Input file: ";
	getline(cin, input_file);

	ifstream input_file_obj(input_file);

	if (!input_file_obj)
	{
		cout << "Error! The file " << input_file << " cannot be opened." << endl;
		return EXIT_FAILURE;
	}

	string line;
	unsigned line_number = 0;
	map<string, pair<int, set<unsigned>>> word_counts;

	while (getline(input_file_obj, line))
	{
		line_number++;
		string word;
		const auto l = line.length();
		for(auto i = 0u; i < l; i++)
		{
			const auto c = line.at(i);
			if(c == ' ' || i == l-1)
			{
				if(i == l - 1)
					word += c;
				if (word_counts.find(word) != word_counts.end())
					word_counts.at(word).first++, 
					word_counts.at(word).second.insert(line_number);
				else
					word_counts.insert({ word, {1, {line_number}} });
				word = "";
			}
			else
				word += c;
		}
	}
	input_file_obj.close();

	auto iter = word_counts.begin();
	while (iter != word_counts.end())
	{
		string line_numbers;
		for (const auto& i : iter->second.second)
			line_numbers += to_string(i) + ", ";

		cout << iter->first << " " << iter->second.first
			 << ": " << line_numbers.substr(0, line_numbers.length() - 2) << endl;
		++iter;
	}

	return EXIT_SUCCESS;
}
