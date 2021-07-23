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

/**
 * @brief Constructor, initializes to default value
 */
Date::Date() :
    day_(0), month_(0), year_(0)
{
}

/**
 * @brief Constructor overload, initializes to a spefic date with three int numbers
 * @param day Day
 * @param month Month
 * @param year Year
 */
Date::Date(const unsigned int day, const unsigned int month, const unsigned int year)
{
    set(day, month, year);
}

/**
 * @brief Constructor overload, intializes to a specific date with a date string
 * @param date_as_str Date as a string
 */
Date::Date(const std::string& date_as_str)
{
    const auto day = date_as_str.substr(0, 2);
    const auto month = date_as_str.substr(2, 2);
    const auto year = date_as_str.substr(4, 4);
    day_ = str_to_date_int(day);
    month_ = str_to_date_int(month);
    year_ = str_to_date_int(year);
}

/**
 * @brief Default destructor
 */
Date::~Date()
= default;

/**
 * @brief Sets the date of this date object
 * @param day Day
 * @param month Month
 * @param year Year
 */
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

/**
 * @brief Checks if this date is the default date
 * @return True if default, false if not
 */
bool Date::is_default() const
{
    return day_ == 0 && month_ == 0 && year_ == 0;
}

/**
 * @brief Advances this date 
 * @param days Amount of days
 */
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

/**
 * @brief Prints this date
 */
void Date::print() const
{
    std::cout << day_ << ".";
    std::cout << month_ << ".";
    std::cout << year_;
}

/**
 * @brief Overrides the is equal operator
 * @param rhs Date object to compare with
 * @return True if equal, false if not
 */
bool Date::operator==(const Date& rhs) const
{
    return day_ == rhs.day_ && month_ == rhs.month_ && year_ == rhs.year_;
}

/**
 * @brief Overrides the less than operator
 * @param rhs Date object to compare with with
 * @return True if less, false if not
 */
bool Date::operator<(const Date& rhs) const
{
    return (year_ * 10000 + month_ * 100 + day_) <
        (rhs.year_ * 10000 + rhs.month_ * 100 + rhs.day_);
}

/**
 * @brief Checks whether this date is a leap year
 * @return True is so, false if not
 */
bool Date::is_leap_year() const
{
    return (year_ % 4 == 0) && ((year_ % 100 != 0) || (year_ % 400 == 0));
}

/**
 * @brief Converts string date to int
 * @param date_part String date
 * @return Int date
 */
unsigned int Date::str_to_date_int(const std::string& date_part) const
{
    if (date_part.at(0) == '0')
    {
        return std::stoi(date_part.substr(1, 1));
    }
    return std::stoi(date_part);
}

