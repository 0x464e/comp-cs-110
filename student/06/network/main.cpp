#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using database = map<string, vector<string>>;

const string HELP_TEXT = "S = store id1 i2\nP = print id\n"
"C = count id\nD = depth id\n";

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false) {
	vector<string> result;
	string tmp = s;

	while (tmp.find(delimiter) != string::npos)
	{
		string new_part = tmp.substr(0, tmp.find(delimiter));
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


void add_person(database& db, const string& referrer, const string& person)
{
	if (db.find(referrer) != db.end())
		db.at(referrer).push_back(person);
	else
		db.insert({ referrer, {person} });
}

void print_database(const database& db, const string& start, unsigned depth = 0)
{
	cout << string(depth*2, '.') << start << endl;
	if (db.find(start) == db.end())
		return;

	for(const auto& person : db.at(start))
		print_database(db, person, ++depth), depth--;
}

unsigned get_count(const database& db, const string& start, const bool count_self = false)
{
	auto count = count_self ? 1u : 0u;
	if(db.find(start) != db.end())
		for (const auto& child : db.at(start))
			count += get_count(db, child, true);
	return count;
}

unsigned get_depth(const database& db, const string& start, unsigned depth = 1)
{
	auto d = depth;
	if (db.find(start) != db.end())
		for (const auto& child : db.at(start))
		{
			auto current_depth = get_depth(db, child, depth + 1);
			d = max(current_depth, d);
		}
			
	return d;
}

int main()
{
	database db;

	while (true) {
		string line;
		cout << "> ";
		getline(cin, line);
		auto parts = split(line, ' ', true);

		const auto command = parts.at(0);

		if (command == "S" || command == "s")
		{
			if (parts.size() != 3)
			{
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
				continue;
			}
			const auto id1 = parts.at(1);
			const auto id2 = parts.at(2);

			add_person(db, id1, id2);
		}
		else if (command == "P" || command == "p")
		{
			if (parts.size() != 2)
			{
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
				continue;
			}
			const auto id = parts.at(1);
			print_database(db, id);

		}
		else if (command == "C" || command == "c")
		{
			if (parts.size() != 2)
			{
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
				continue;
			}
			const auto id = parts.at(1);

			cout << get_count(db, id) << endl;

		}
		else if (command == "D" || command == "d")
		{
			if (parts.size() != 2) {
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
				continue;
			}
			const auto id = parts.at(1);

			cout << get_depth(db, id) << endl;
		}
		else if (command == "Q" || command == "q")
			return EXIT_SUCCESS;
		else
			cout << "Erroneous command!" << endl << HELP_TEXT;
	}
}
