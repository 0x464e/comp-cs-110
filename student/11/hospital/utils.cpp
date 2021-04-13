#include "utils.hh"

std::vector<std::string> utils::split(std::string& str, const char delim)
{
    std::vector<std::string> result = { "" };
    auto cont = false;
    for (auto cha : str)
    {
        if (cha == '"')
        {
            cont = !cont;
        }
        else if (cha == delim && !cont)
        {
            result.emplace_back("");
        }
        else
        {
            result.back().push_back(cha);
        }
    }
    if (result.back().empty())
    {
        result.erase(--result.end());
    }
    return result;
}

bool utils::is_numeric(std::string s, const bool zero_allowed)
{
    if (!zero_allowed)
    {
        auto all_zeroes = true;
        for (auto i : s)
        {
            if (i != '0')
            {
                all_zeroes = false;
            }
        }
        if (all_zeroes)
        {
            return false;
        }
    }
    for (auto i : s)
    {
        if (!isdigit(i))
        {
            return false;
        }
    }
    return true;
}
