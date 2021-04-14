#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";

int main()
{
    const auto hospital = new Hospital();

    Cli cli(hospital, PROMPT);
    while (cli.exec()) {}

    delete hospital;
    return EXIT_SUCCESS;
}
