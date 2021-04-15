/*
 * COMP.CS.110 K2021
 *
 * Program author
 * Name: Otto 
 * Student number: 
 * UserID: 
 * E-Mail: 
 */

#include "careperiod.hh"
#include "utils.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient) :
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date& start, Person* patient) :
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
    patient_ = nullptr;
}

/**
 * @brief Returns the patient of this care period
 * @return Pointer to Person object
 */
Person* CarePeriod::get_patient() const
{
    return patient_;
}

/**
 * @brief Ends this care period by setting today as the end date
 */
void CarePeriod::end_careperiod()
{
    end_ = utils::today;
}

/**
 * @brief Adds a staff member to this care period
 * @param id Id of the staff member to be added
 */
void CarePeriod::add_staff(const std::string& id)
{
    staff_.insert(id);
}

/**
 * @brief Prints this care period, optinally with some pre text
 * @param pre_text String to add in front of the printout
 */
void CarePeriod::print_careperiod_duration(const std::string& pre_text) const
{
    std::cout << pre_text;
    start_.print();
    std::cout << " -";

    if (!end_.is_default())
    {
        std::cout << " ";
        end_.print();
    }
    std::cout << std::endl;
}

/**
 * @brief Prints the staff members assigned to this care period,\n
 * optionally with some pre text
 * @param pre_text String to add in front of the printout
 */
void CarePeriod::print_staff(const std::string& pre_text) const
{
    std::cout << pre_text;
    if (staff_.empty())
    {
        std::cout << " None" << std::endl;
        return;
    }

    for (const auto& staff : staff_)
    {
        std::cout << " " << staff;
    }

    std::cout << std::endl;
}

/**
 * @brief Returns the staff members assigned to this care period
 * @return String set of the staff members' ids
 */
std::set<std::string> CarePeriod::get_staff() const
{
    return staff_;
}
