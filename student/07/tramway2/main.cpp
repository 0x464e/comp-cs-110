#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

const std::string INPUT_FILENAME = "Give a name for input file: ";
const std::string INVALID_FILE = "Error: File could not be read.";
const std::string INVALID_FILE_FORMAT = "Error: Invalid format in file.";
const std::string DUPLICATE_STOP_LINE = "Error: Stop/line already exists.";
const std::string INPUT_PROMPT = "tramway> ";
const std::string INVALID_COMMAND = "Error: Invalid input.";

typedef std::map<std::string, std::map<std::string, double>> tramway;

//Prints a RASSE
void print_rasse()
{
	std::cout <<
		"=====//==================//===\n"
		"  __<<__________________<<__   \n"
		" | ____ ____ ____ ____ ____ |  \n"
		" | |  | |  | |  | |  | |  | |  \n"
		" |_|__|_|__|_|__|_|__|_|__|_|  \n"
		".|                  RASSE   |. \n"
		":|__________________________|: \n"
		"___(o)(o)___(o)(o)___(o)(o)____\n"
		"-------------------------------" << std::endl;
}


//Splits the input string by the specified delimiter.
//Optinally ignores empty parts.
//Returns a vector of the split strings.
std::vector<std::string> split(const std::string& s, const char delimiter,
	const bool ignore_empty = false)
{
	std::vector<std::string> result;
	auto tmp = s;

	while (tmp.find(delimiter) != std::string::npos)
	{
		auto new_part = tmp.substr(0, tmp.find(delimiter));
		tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
		if (!(ignore_empty && new_part.empty()))
		{
			result.push_back(new_part);
		}
	}
	if (!(ignore_empty && tmp.empty()))
	{
		result.push_back(tmp);
	}
	return result;
}


std::tuple<std::string, std::string, double> is_valid_input_file_line(const std::string& file_line,
	const tramway& database)
{
	const auto fields = split(file_line, ';');
	const auto field_count = fields.size();

	//if input file line has fewer than 2 lines, or more than 3 lines,
	//return an empty tuple to indicate an invalid line
	if (field_count < 2 || field_count > 3)
	{
		std::cout << INVALID_FILE_FORMAT << std::endl;
		return std::tuple<std::string, std::string, double>();
	}

	const auto& line = fields.at(0);
	const auto& stop = fields.at(1);
	if (line.empty() || stop.empty())
	{
		std::cout << INVALID_FILE_FORMAT << std::endl;
		return std::tuple<std::string, std::string, double>();
	}

	//if distance field was omitted, it's zero by default
	auto distance = 0.0;
	if (field_count == 3)
	{
		//if distance field is empty, it's zero by default
		//otherwise assume distance field is a valid decimal number
		distance = fields.at(2).empty() ? 0.0 : std::stod(fields.at(2));
	}

	//if the stop already exists in the database and
	//the stop is already specified for this line
	if (database.find(stop) != database.end() &&
		database.at(stop).find(line) != database.at(stop).end())
	{
		std::cout << DUPLICATE_STOP_LINE << std::endl;
		return std::tuple<std::string, std::string, double>();
	}

	//loop through each stop in the database
	for (const auto& db_stop : database)
	{
		//if the current stop is found in the same tramline as the current 
		//input file line's tramline, check if the distance is the same
		//if distance is the same, it's a duplicate tramline
		if (db_stop.second.find(line) != db_stop.second.end() &&
			db_stop.second.at(line) == distance)
		{
			std::cout << DUPLICATE_STOP_LINE << std::endl;
			return std::tuple<std::string, std::string, double>();
		}
	}

	//if code execution got this far, the input line was fine
	return std::tuple<std::string, std::string, double> {line, stop, distance};
}

//Handles the logic to read an input file based off user input
//and attempts to fills the byref specified tramway database object.
//Returns true for success, false for failure.
bool read_input_file(tramway& database)
{
	std::string filename = "";
	std::cout << INPUT_FILENAME;
	std::getline(std::cin, filename);

	std::ifstream file_obj(filename);

	std::string file_line = "";

	if (!file_obj)
	{
		std::cout << INVALID_FILE << std::endl;
		return false;
	}

	//read each line from the input file
	while (std::getline(file_obj, file_line))
	{
		const auto fields = is_valid_input_file_line(file_line, database);
		//if the above check returned an empty tramline, the file line was invalid
		if (std::get<0>(fields).empty())
		{
			return false;
		}

		const auto& line = std::get<0>(fields);
		const auto& stop = std::get<1>(fields);
		const auto& distance = std::get<2>(fields);

		//if the stop doesn't already exist, simply add it in
		if (database.find(stop) == database.end())
		{
			database.insert(
				{
					stop,
					{ { line, distance } }
				});
		}
		//else add a new line and distance for the stop
		else
		{
			database.at(stop).insert({ line, distance });
		}
	}

	return true;
}

//prints each tramline found in the input database in alphabetical order
void print_tramlines(const tramway& database)
{
	//use set to automatically remove duplicates and sort alphabetically
	std::set<std::string> lines;
	std::cout << "All tramlines in alphabetical order:" << std::endl;

	//loop each tramline under each stop
	for (const auto& stop : database)
	{
		for (const auto& line : stop.second)
		{
			lines.insert(line.first);
		}
	}

	for (const auto& line : lines)
	{
		std::cout << line << std::endl;
	}
}

//runs the rasse user interface
//handles all user input commands
void rasse_user_interface(tramway& database)
{
	for (;;)
	{
		std::string user_input = "";
		std::cout << INPUT_PROMPT;
		std::getline(std::cin, user_input);

		//split the user input by space
		const auto split_inputs = split(user_input, ' ', true);
		if (split_inputs.empty())
		{
			continue;
		}

		//the command is the first element in the split inputs
		//arguments are all the following elements
		const auto& command = split_inputs.at(0);
		const std::vector<std::string> arguments(split_inputs.begin() + 1, split_inputs.end());

		if (command == "QUIT")
		{
			break;
		}
		if (command == "LINES")
		{
			print_tramlines(database);
		}
		else if (command == "LINE")
		{
			//requires one argument
			if(arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
		}
		else if (command == "STOPS")
		{

		}
		else if (command == "STOP")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
		}
		else if (command == "DISTANCE")
		{
			//requires three arguments
			if (arguments.size() < 3)
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
		}
		else if (command == "ADDLINE")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
		}
		else if (command == "ADDSTOP")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
		}
		else if (command == "REMOVE")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
		}
	}
}

//entry point
int main()
{
	tramway database;
	print_rasse();
	//attempt to fill the database byref
	if (!read_input_file(database))
	{
		return EXIT_FAILURE;
	}
	rasse_user_interface(database);
	return EXIT_SUCCESS;
}
