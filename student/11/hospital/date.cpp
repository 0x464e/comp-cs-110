/*
 * COMP.CS.110 K2021
 *
 * Program author
 * Name: Otto 
 * Student number: 
 * UserID: 
 * E-Mail: 
 */

#include "date.hh"
#include "utils.hh"
#include <iostream>

// Number of days in months
unsigned int const month_sizes[12] = { 31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31 };

Date::Date() :
    day_(0), month_(0), year_(0)
{
}

Date::Date(const unsigned int day, const unsigned int month, const unsigned int year)
{
    set(day, month, year);
}

Date::Date(const std::string& data_as_str)
{
    const auto day = data_as_str.substr(0, 2);
    const auto month = data_as_str.substr(2, 2);
    const auto year = data_as_str.substr(4, 4);
    day_ = str_to_date_int(day);
    month_ = str_to_date_int(month);
    year_ = str_to_date_int(year);
}

Date::~Date()
= default;

void Date::set(const unsigned int day, const unsigned int month, const unsigned int year)
{
    day_ = day;
    month_ = month;
    year_ = year;

    if (month_ > 12 || month_ < 1)
    {
        month_ = 1;
    }
    if (day_ > month_sizes[month_ - 1]
        || (month_ == 2 && is_leap_year()
            && day > month_sizes[month - 1] + 1))
    {
        day_ = 1;
    }
}

bool Date::is_default() const
{
    return day_ == 0 && month_ == 0 && year_ == 0;
}

void Date::advance(const unsigned int days)
{
    day_ += days;
    while (day_ > month_sizes[month_ - 1])
    {
        if (month_ == 2 && day_ == 29 && is_leap_year())
        {
            return;
        }
        day_ -= month_sizes[month_ - 1];
        if (month_ == 2 && is_leap_year())
        {
            --day_;
        }
        ++month_;

        if (month_ > 12)
        {
            month_ -= 12;
            ++year_;
        }
    }
}

void Date::print() const
{
    std::cout << day_ << ".";
    std::cout << month_ << ".";
    std::cout << year_;
}

bool Date::operator==(const Date& rhs) const
{
    return day_ == rhs.day_ && month_ == rhs.month_ && year_ == rhs.year_;
}

bool Date::operator<(const Date& rhs) const
{
    return (year_ * 10000 + month_ * 100 + day_) <
        (rhs.year_ * 10000 + rhs.month_ * 100 + rhs.day_);
}

bool Date::is_leap_year() const
{
    return (year_ % 4 == 0) && ((year_ % 100 != 0) || (year_ % 400 == 0));
}

unsigned int Date::str_to_date_int(const std::string& date_part) const
{
    if (date_part.at(0) == '0')
    {
        return std::stoi(date_part.substr(1, 1));
    }
    return std::stoi(date_part);
}

