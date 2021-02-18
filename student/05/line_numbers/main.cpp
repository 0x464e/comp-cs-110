#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	string input_file;
	string output_file;
	cout << "Input file: ";
	getline(cin, input_file);
	cout << "Output file: ";
	getline(cin, output_file);

	ifstream input_file_obj(input_file);

	if (!input_file_obj)
	{
		cout << "Error! The file " << input_file << " cannot be opened." << endl;
		return EXIT_FAILURE;
	}

	ofstream output_file_obj(output_file);

	string line;
	auto i = 0;
	while (getline(input_file_obj, line))
		output_file_obj << to_string(++i) << " " << line << endl;
	input_file_obj.close();
	output_file_obj.close();

	return EXIT_SUCCESS;
}

