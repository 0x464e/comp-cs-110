#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;


bool comparator(const string& first, const string& second)
{
	return first > second;
}


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

	map<string, int> scores;

	string line;
	size_t i;

	while (getline(input_file_obj, line))
	{
		auto key = line.substr(0, i = line.find(':'));
		auto value = stoi(line.substr(i + 1));
		if (scores.find(key) == scores.end())
			scores.insert({ key, value });
		else
			scores.at(key) += value;
	}
	input_file_obj.close();
	cout << "Final scores:" << endl;
	

	for (auto score : scores)
		cout << score.first << ": " << score.second << endl;

	return EXIT_SUCCESS;
}
