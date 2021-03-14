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
const std::string UNKNOWN_LINE = "Error: Line could not be found.";
const std::string UNKNOWN_STOP = "Error: Stop could not be found.";

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

//Splits the input string by the specified separator.
//Words wrapped in quotes will be returned as one part.
//Optinally includes empty parts.
//Returns a vector of the split strings.
std::vector<std::string> split(const std::string& user_input,
	const char separator, const bool include_empty = false)
{
	if (user_input.empty())
	{
		return std::vector<std::string>();
	}

	//vector to hold the separated parts
	std::vector<std::string> parts = {};
	//temp variable to hold the current part
	std::string part = "";

	//tells whether parsing is currently happening 
	//inside or outside of a quoted substring
	auto inside_quotes = false;

	//loop through each character looking for occurrences of
	//the separator character
	for (auto c : user_input)
	{
		if (c == '"')
		{
			//toggle being inside quoted substring
			inside_quotes = !inside_quotes;
			continue;
		}
		//if inside a quoted substring, ignore the main separator
		if (!inside_quotes && c == separator)
		{
			//include empty parts only if asked for
			if (!part.empty() || include_empty)
			{
				parts.push_back(part);
			}
			part = "";
			continue;
		}
		part += c;
	}

	//also add in whatever was after the last separator
	if (!part.empty() || include_empty)
	{
		parts.push_back(part);
	}
	return parts;
}


std::tuple<std::string, std::string, double> is_valid_input_file_line(const std::string& file_line,
	const tramway& database)
{
	const auto fields = split(file_line, ';', true);
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

//Attempts to print the specified tramline in alphabetical order
//returns false if the specified tramline doesn't exist
bool print_tramline(const tramway& database, const std::string& line)
{
	//vector of stop-distance pairs to store the whole tramline
	std::vector<std::pair<std::string, double>> stops;

	//loop through each stop checking if it's found on the specified line
	for (const auto& stop : database)
	{
		if (stop.second.find(line) != stop.second.end())
		{
			stops.emplace_back(stop.first, stop.second.at(line));
		}
	}

	if (stops.empty())
	{
		return false;
	}

	std::cout << "Line " << line << " goes through these stops "
		<< "in the order they are listed:" << std::endl;

	//sort stops by ascending distance by using a custom comparator lambda
	//the next stop is always guaranteed to be further away from the departure 
	//stop, so this is valid
	std::sort(stops.begin(), stops.end(),
		[](const std::pair<std::string, double>& stop1,
			const std::pair<std::string, double>& stop2)
	{
		return stop1.second < stop2.second;
	});

	//print each stop and distance from the departure stop
	for (const auto& stop : stops)
	{
		//ignore tramlines without any stops (stop is "")
		if(!stop.first.empty())
		{
			std::cout << " - " << stop.first << " : " << stop.second << std::endl;
		}
	}

	return true;
}

void print_stops(const tramway& database)
{
	//use set to automatically remove duplicates and sort alphabetically
	std::set<std::string> stops;
	std::cout << "All stops in alphabetical order:" << std::endl;

	for (const auto& stop : database)
	{
		stops.insert(stop.first);
	}

	for (const auto& stop : stops)
	{
		//ignore tramlines without any stops (stop is "")
		if(!stop.empty())
		{
			std::cout << stop << std::endl;
		}
	}
}

//Attempts to print all the tramlines the specified stop is found in
//returns false if the specified stop doesn't exist
bool print_lines_in_stop(const tramway& database, const std::string& stop)
{
	if (database.find(stop) == database.end())
	{
		return false;
	}

	//use set to automatically remove duplicates and sort alphabetically
	std::set<std::string> lines;
	for (const auto& line : database.at(stop))
	{
		lines.insert(line.first);
	}

	//print each stop and distance from the departure stop
	for (const auto& line : lines)
	{
		std::cout << " - " << line << std::endl;
	}

	return true;
}

//Checks whether or not a tramline exists in the specified database
//returns true if it exists, false if not
bool is_line_in_database(const tramway& database, const std::string& line)
{
	auto exists = false;

	//loop through each stop in the database
	for (const auto& stop : database)
	{
		//if the tramline is found even once, it exists
		if (stop.second.find(line) != stop.second.end())
		{
			exists = true;
			break;
		}
	}
	
	return exists;
}

void print_distance_between_stops(const tramway& database,
	const std::string& line, const std::string& stop1, const std::string& stop2)
{
	if(!is_line_in_database(database, line))
	{
		std::cout << UNKNOWN_LINE << std::endl;
		return;
	}

	//if either of the stops is unknown, or either of the stops 
	//aren't found on to the specified tramline
	if(database.find(stop1) == database.end() || 
		database.at(stop1).find(line) == database.at(stop1).end() ||
		database.find(stop2) == database.end() ||
		database.at(stop1).find(line) == database.at(stop1).end())
	{
		std::cout << UNKNOWN_STOP << std::endl;
		return;
	}

	std::cout << "Distance between " << stop1 << " and " << stop2 << " is "
		<< std::abs(database.at(stop1).at(line) - database.at(stop2).at(line))
		<< std::endl;
}

//Attempts to add a new tramline to the database
void add_tramline(tramway& database, const std::string& line)
{
	if(is_line_in_database(database, line))
	{
		std::cout << DUPLICATE_STOP_LINE << std::endl;
		return;
	}

	//tramlines with no stops are stored under the key ""
	if(database.find("") == database.end())
	{
		database.insert(
			{
				"",
				{ { line, 0.0 } }
			});
	}
	else
	{
		database.at("").insert({ line, 0.0 });
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
		const auto split_inputs = split(user_input, ' ');
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
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			if (!print_tramline(database, arguments.at(0)))
			{
				std::cout << UNKNOWN_LINE << std::endl;
			}
		}
		else if (command == "STOPS")
		{
			print_stops(database);
		}
		else if (command == "STOP")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			if (!print_lines_in_stop(database, arguments.at(0)))
			{
				std::cout << UNKNOWN_STOP << std::endl;
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
			print_distance_between_stops(database, arguments.at(0),
				arguments.at(1), arguments.at(2));
		}
		else if (command == "ADDLINE")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			add_tramline(database, arguments.at(0));
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
		else
		{
			std::cout << INVALID_COMMAND << std::endl;
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
