/*
* Tramway
*
* Description:
* This program models a tramway system of different lines and stops. Each line
* is associated with different stops and each stop is associated with a distance
* from the departure stop. The program starts off by reading a specified input
* file, which contains information about the tramway system in csv format:
* line;stop[;distance]
* the distance value being optional and defaulting to zero, indicating it being
* the departure stop. A line can't have duplicate stops, this is checked by both
* stop name & distance. After the input file has been parsed and the database
* has been populated, the command line user interface opens. The program
* contains nine commands:
* QUIT								 - quit the program
* LINES								 - print all lines
* LINE		<line>					 - print specific line
* STOPS								 - print all stops
* STOP		<stop>					 - print specific stop
* DISTANCE	<line> <stop1> <stop2>	 - distance between two stops on the line
* ADDLINE	<line>					 - adds a new line to the database
* ADDSTOP	<line> <stop> <distance> - adds a new stop to the database
* REMOVE	<stop>					 - removes a stop from the database
*
*
* COMP.CS.110 K2021
*
* Program author
* Name: Otto 
* Student number: 
* UserID: 
* E-Mail: 
* Date: 15.03.2021
*
* Notes about the program and it's implementation:
* If using the tramway stops as the outer map's keys in the database is somehow
* more desirable, I have a working version for that as well in a previous commit.
* Switching to using lines as the outer map's keys in the database was an
* afterthought. After I made the switch to that, I really couldn't say why I
* didn't do it that way right away. This seems so much better and cleaner.
*/

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

//a struct to pass around certain tramway stop's information more conveniently
struct tramway_stop
{
	std::string line;
	std::string name;
	double distance{};
};

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
//Substrings wrapped in quotes will be returned as one part.
//Optionally includes empty parts.
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

//Attempts to create a tramway stop from the input vector of strings.
//Returns an empty tramway_stop struct if the input was invalid.
tramway_stop create_tramway_stop(const std::vector<std::string>& fields,
	const tramway& database)
{
	const auto field_count = fields.size();

	//if input file line has fewer than 2 lines, or more than 3 lines,
	//return an empty tramway struct to indicate invalid input
	if (field_count < 2 || field_count > 3)
	{
		std::cout << INVALID_FILE_FORMAT << std::endl;
		return tramway_stop();
	}

	const auto& line = fields.at(0);
	const auto& stop = fields.at(1);
	if (line.empty() || stop.empty())
	{
		std::cout << INVALID_FILE_FORMAT << std::endl;
		return tramway_stop();
	}

	//if distance field was omitted, it's zero by default
	auto distance = 0.0;
	if (field_count == 3)
	{
		//if distance field is empty, it's zero by default
		//otherwise assume distance field is a valid decimal number
		distance = fields.at(2).empty() ? 0.0 : std::stod(fields.at(2));
	}

	//if line exists in the database and the stop
	//is already specified for this line
	if (database.find(line) != database.end() &&
		database.at(line).find(stop) != database.at(line).end())
	{
		std::cout << DUPLICATE_STOP_LINE << std::endl;
		return tramway_stop();
	}

	//if the line exists in the database
	if (database.find(line) != database.end())
	{
		//loop through each stop in the database under the specified line
		for (const auto& db_stop : database.at(line))
		{
			//if a stop in the database already has the specified distance,
			//the input stop is invalid
			if (db_stop.second == distance)
			{
				std::cout << DUPLICATE_STOP_LINE << std::endl;
				return tramway_stop();
			}
		}
	}

	tramway_stop stop_struct;
	stop_struct.line = line;
	stop_struct.name = stop;
	stop_struct.distance = distance;

	//if code execution got this far, the input line was fine
	return stop_struct;
}

//Adds the specified stop to the database
//The stop is to be validated with is_valid_stop() before passed into here
void add_stop(tramway& database, const tramway_stop& stop)
{
	//if the line doesn't already exist, simply add it in
	//along with the stop and distance
	if (database.find(stop.line) == database.end())
	{
		database.insert(
			{
				stop.line,
				{ { stop.name, stop.distance } }
			});
	}
	//else add a new stop and distance for the stop
	else
	{
		database.at(stop.line).insert({ stop.name, stop.distance });
	}
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
		const auto fields = split(file_line, ';', true);
		const auto stop = create_tramway_stop(fields, database);

		//if the above check returned an empty tramline, the file line was invalid
		if (stop.line.empty())
		{
			return false;
		}

		add_stop(database, stop);
	}
	return true;
}

//prints each tramline found in the input database in alphabetical order
void print_tramlines(const tramway& database)
{
	std::cout << "All tramlines in alphabetical order:" << std::endl;

	//keys in map are sorted alphabetically automatically
	for (const auto& line : database)
	{
		std::cout << line.first << std::endl;
	}
}

//Attempts to print the specified tramline in alphabetical order
void print_tramline(const tramway& database, const std::string& line)
{
	//vector of stop-distance pairs to store the whole tramline
	std::vector<std::pair<std::string, double>> stops;

	if (database.find(line) == database.end())
	{
		std::cout << UNKNOWN_LINE << std::endl;
		return;
	}

	for (const auto& stop : database.at(line))
	{
		stops.emplace_back(stop.first, stop.second);
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
		//ignore empty tramline
		if (!stop.first.empty())
		{
			std::cout << " - " << stop.first << " : " << stop.second << std::endl;
		}
	}
}

void print_stops(const tramway& database)
{
	//use set to automatically remove duplicates and sort alphabetically
	std::set<std::string> stops;
	std::cout << "All stops in alphabetical order:" << std::endl;

	//loop through each stop under each line
	for (const auto& line : database)
	{
		for (const auto& stop : line.second)
		{
			stops.insert(stop.first);
		}
	}

	for (const auto& stop : stops)
	{
		std::cout << stop << std::endl;
	}
}

//Checks whether a stop exists in the specified database
//returns true if it exists, false if not
bool is_stop_in_database(const tramway& database, const std::string& stop)
{
	//loop through each stop in the database
	for (const auto& line : database)
	{
		//if the stop is found even once, it exists
		if (line.second.find(stop) != line.second.end())
		{
			return true;
		}
	}

	return false;
}

//Attempts to print all the tramlines the specified stop is found in
void print_lines_in_stop(const tramway& database, const std::string& stop)
{
	if (!is_stop_in_database(database, stop))
	{
		std::cout << UNKNOWN_STOP << std::endl;
		return;
	}

	std::cout << "Stop " << stop << " can be found on the following lines:" << std::endl;

	//use set to automatically remove duplicates and sort alphabetically
	std::set<std::string> lines;
	for (const auto& line : database)
	{
		if (line.second.find(stop) != line.second.end())
		{
			lines.insert(line.first);
		}
	}

	//print each line
	for (const auto& line : lines)
	{
		std::cout << " - " << line << std::endl;
	}
}

void print_distance_between_stops(const tramway& database,
	const std::string& line, const std::string& stop1, const std::string& stop2)
{
	if (database.find(line) == database.end())
	{
		std::cout << UNKNOWN_LINE << std::endl;
		return;
	}

	const auto& db_line = database.at(line);

	//if either of the stops isn't found under the specified tramline
	if (db_line.find(stop1) == db_line.end() ||
		db_line.find(stop2) == db_line.end())
	{
		std::cout << UNKNOWN_STOP << std::endl;
		return;
	}

	std::cout << "Distance between " << stop1 << " and " << stop2 << " is "
		<< std::abs(db_line.at(stop1) - db_line.at(stop2))
		<< std::endl;
}

//Attempts to add a new tramline to the database
void add_tramline(tramway& database, const std::string& line)
{
	//if duplicate tramline
	if (database.find(line) != database.end())
	{
		std::cout << DUPLICATE_STOP_LINE << std::endl;
		return;
	}

	database.insert(
		{
			line,
			{ {  } }
		});

	std::cout << "Line was added." << std::endl;
}

//Adds more printouts to the process of adding a stop.
//Used when adding stops via the user interface.
void add_stop_with_printouts(tramway& database, const std::string& line,
	const std::string& stop_name, const std::string& distance)
{
	//if unknown line
	if (database.find(line) == database.end())
	{
		std::cout << UNKNOWN_LINE << std::endl;
		return;
	}

	//attempt to create a tramway stop
	const auto stop = create_tramway_stop({ line, stop_name, distance }, database);

	//the stop is invalid if it doesn't have a line
	if (stop.line.empty())
	{
		return;
	}

	add_stop(database, stop);
	std::cout << "Stop was added." << std::endl;
}

//Removes the specified stop from all lines in the specified database
void remove_stop(tramway& database, const std::string& stop)
{
	if (!is_stop_in_database(database, stop))
	{
		std::cout << UNKNOWN_STOP << std::endl;
		return;
	}

	for (auto& line : database)
	{
		//erase from each line it occurs in
		if (line.second.find(stop) != line.second.end())
		{
			line.second.erase(stop);
		}
	}

	std::cout << "Stop was removed from all lines." << std::endl;
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
		auto command = split_inputs.at(0);

		//transform command to lowercase
		std::transform(command.begin(), command.end(), command.begin(), tolower);

		//arguments are all the elements after the first one
		const std::vector<std::string> arguments(split_inputs.begin() + 1,
			split_inputs.end());

		if (command == "quit")
		{
			break;
		}
		if (command == "lines")
		{
			print_tramlines(database);
		}
		else if (command == "line")
		{
			//requires one argument
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			print_tramline(database, arguments.at(0));
		}
		else if (command == "stops")
		{
			print_stops(database);
		}
		else if (command == "stop")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			print_lines_in_stop(database, arguments.at(0));
		}
		else if (command == "distance")
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
		else if (command == "addline")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			add_tramline(database, arguments.at(0));
		}
		else if (command == "addstop")
		{
			if (arguments.size() < 3)
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			add_stop_with_printouts(database, arguments.at(0), arguments.at(1),
				arguments.at(2));
		}
		else if (command == "remove")
		{
			if (arguments.empty())
			{
				std::cout << INVALID_COMMAND << std::endl;
				continue;
			}
			remove_stop(database, arguments.at(0));
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
	//main database, holds all the info
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
