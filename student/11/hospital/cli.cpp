#include "cli.hh"
#include "utils.hh"
#include <fstream>
#include <sstream>
#include <utility>


Cli::Cli(Hospital* hospital, std::string prompt) :
    hospital_(hospital),
    prompt_(std::move(prompt)),
    can_start_(hospital != nullptr)
{
}

bool Cli::exec()
{
    if (!can_start_)
    {
        std::cout << UNINITIALIZED << std::endl;
        return false;
    }
    std::string cmd;
    std::cout << prompt_;
    std::getline(std::cin, cmd);
    auto input = utils::split(cmd, ' ');
    if (input.empty())
    {
        return true;
    }
    cmd = input.front();
    pop_front(input);
    const auto func = find_command(cmd);

    if (func == nullptr)
    {
        std::cout << UNKNOWN_CMD << std::endl;
        return true;
    }

    // The number of parameters of commands Quit and Help does not matter
    if (func->name == "Quit")
    {
        return false;
    }

    if (func->name == "Help")
    {
        print_help(input);
        return true;
    }

    if (func->params.size() != input.size())
    {
        std::cout << WRONG_PARAMETERS << std::endl;
        return true;
    }

    if (func->name == "Read")
    {
        if (!read_from_file(input.at(0)))
        {
            std::cout << FILE_READING_ERROR << std::endl;
            return false;
        }
        std::cout << FILE_READING_OK << input.at(0) << std::endl;
        return true;
    }

    // Call to member func ptr: (OBJ ->* FUNC_PTR)(PARAMS)
    (hospital_->*(func->func_ptr))(input);
    return true;
}

void Cli::pop_front(std::vector<std::string>& vec)
{
    vec.erase(vec.begin(), ++vec.begin());
}

Cmd* Cli::find_command(const std::string& cmd)
{
    auto upper_cmd = cmd;
    for (unsigned int i = 0; i < cmd.size(); ++i)
    {
        upper_cmd.at(i) = toupper(cmd.at(i));
    }
    for (auto command = cmds_.begin(); command != cmds_.end(); ++command)
    {
        for (const auto& alias : command->aliases)
        {
            if (alias == upper_cmd)
            {
                return &(*command);
            }
        }
    }
    return nullptr;
}

void Cli::print_help(const std::vector<std::string>& params)
{
    if (!params.empty())
    {
        print_cmd_info(find_command(params.at(0)), true);
        return;
    }
    for (auto cmd : cmds_)
    {
        print_cmd_info(&cmd);
    }
}

void Cli::print_cmd_info(Cmd* cmd, const bool longer)
{
    std::cout << cmd->name << " : ";
    for (const auto& alias : cmd->aliases)
    {
        std::cout << alias << " ";
    }
    std::cout << std::endl;
    if (longer)
    {
        std::cout << "Params: " << std::endl;
        if (cmd->params.empty())
        {
            std::cout << "None." << std::endl;
        }
        else
        {
            for (const auto& param : cmd->params)
            {
                std::cout << param << std::endl;
            }
        }
    }
}

bool Cli::read_from_file(const std::string& filename)
{
    std::ifstream inputfile(filename);
    if (!inputfile)
    {
        return false;
    }
    // Redirect the file to cin and save the old cin
    const auto cinbuf = std::cin.rdbuf(inputfile.rdbuf());
    std::ostringstream unwanted_output;
    const auto coutbuf = std::cout.rdbuf(unwanted_output.rdbuf());

    while (exec()) {}

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    inputfile.close();

    return true;
}
