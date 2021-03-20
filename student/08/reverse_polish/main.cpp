#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<std::string> split(const std::string& s, const char delimiter, const bool ignore_empty = false)
{
	std::vector<std::string> result;
	auto tmp = s;

	while (tmp.find(delimiter) != std::string::npos)
	{
		auto new_part = tmp.substr(0, tmp.find(delimiter));
		tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
		if (!(ignore_empty && new_part.empty()))
			result.push_back(new_part);
	}
	if (!(ignore_empty && tmp.empty()))
		result.push_back(tmp);
	return result;
}

int calculate(const int a, const int b, const std::string &operation)
{
	if (operation == "+")
		return a + b;
	if (operation == "-")
		return a - b;
	if (operation == "*")
		return a * b;
	if (operation == "/")
		return a / b;
	return -1;
}

bool isOperation(const std::string& op)
{
	return op == "+" || op == "-" || op == "*" || op == "/";
}

int calculate(std::vector<std::string> &notation) 
{

	std::stack<int> numbers;
	for (const auto& str : notation)
	{
		if (isOperation(str))
		{
			const auto n2 = numbers.top(); 
			numbers.pop();
			const auto n1 = numbers.top(); 
			numbers.pop();

			if (n2 == 0 && str == "/")
				return 69696969;

			numbers.push(calculate(n1, n2, str));
		}
		else
			numbers.push(std::stoi(str));
	}

	return numbers.top();
}

std::vector<std::string> parse(const std::string& input)
{
	std::vector<std::string> vec;

	std::string current;

	for (const auto& c : input)
	{
		if (isdigit(c))
			current += c;
		else if (c)
		{
			if (!current.empty())
			{
				vec.emplace_back(std::move(current));
				current = "";
			}
			if (c != ' ')
				vec.emplace_back(1, c);
		}
	}

	if (!current.empty())
		vec.push_back(std::move(current));

	return vec;
}

int main() 
{
	std::string input;
	cout << "Input an expression in reverse Polish notation (end with #):" << endl << "EXPR> ";
	std::getline(std::cin, input);
	input.pop_back();
	auto str_parts = split(input, ' ', true);

	//I hope no one sees this
	std::vector<char> parts;
	for (const auto& part : str_parts)
		parts.push_back(part[0]);

	if (!isdigit(parts[0]))
	{
		cout << "Error: Expression must start with a number" << endl;
		return EXIT_FAILURE;
	}

	auto prev_operand = 'k';
	vector<char> operators1;
	vector<int> operands1;

	for (const auto& part : parts)
	{
		if (isdigit(part))
			operands1.push_back((prev_operand = part) - '0');
		else if (part == '+' || part == '-' || part == '*')
			operators1.push_back(part);
		else if (part == '/')
		{
			operators1.push_back(part);
			if (prev_operand == '0')
			{
				cout << "Error: Division by zero" << endl;
				return EXIT_FAILURE;
			}
		}
		else
		{
			cout << "Error: Unknown character" << endl;
			return EXIT_FAILURE;
		}
	}

	const auto ratio = operands1.size() - operators1.size();
	if (ratio > 1)
	{
		cout << "Error: Too few operators" << endl;
		return EXIT_FAILURE;
	}

	if (ratio < 1)
	{
		cout << "Error: Too few operands" << endl;
		return EXIT_FAILURE;
	}

	auto notation = parse(input);
	const auto result = calculate(notation);
	if(result == 69696969)
	{
		cout << "Error: Division by zero" << endl;
		return EXIT_SUCCESS;
	}
	std::cout << "Correct: " << result << " is the result" << endl;
	return EXIT_SUCCESS;
}