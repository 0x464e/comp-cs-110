/*
 * COMP.CS.110 K2021
 *
 * Program author
 * Name: Otto 
 * Student number: 
 * UserID: 
 * E-Mail: 
 */

#include "person.hh"
#include <iostream>
#include <map>
#include <utility>

/**
 * @brief Default constructor
 */
Person::Person()
= default;

/**
 * @brief Constructor overload, initalizes id with move semantics and date of
 * birth with the default date
 * @param id String id for the person
 */
Person::Person(std::string id) :
    id_(std::move(id))
{
    date_of_birth_ = Date();
}

/**
 * @brief Constructor overload, initalizes id with move semantics and date of
 * birth with the specified date
 * @param id String id for the person
 * @param date_of_birth String date of birth
 */
Person::Person(std::string id, const std::string& date_of_birth) :
    id_(std::move(id)), date_of_birth_(date_of_birth)
{
}

/**
 * @brief Default destructor
 */
Person::~Person()
= default;

/**
 * @brief Gets this person's id
 * @return String id
 */
std::string Person::get_id() const
{
    return id_;
}

/**
 * @brief Gets this person's medicines
 * @return String vector containing the medicines
 */
std::vector<std::string> Person::get_medicines() const
{
    std::vector<std::string> result;
    for (auto iter = medicines_.begin(); iter != medicines_.end(); ++iter)
    {
        result.push_back(iter->first);
    }
    return result;
}

/**
 * @brief Adds a medicine prescription for this person
 * @param name Name of medicine
 * @param strength Strength of medicine
 * @param dosage Dosage for medicine
 */
void Person::add_medicine(const std::string& name,
    const unsigned int strength,
    const unsigned int dosage)
{
    Prescription pre{};
    pre.strength = strength;
    pre.dosage = dosage;
    if (medicines_.find(name) != medicines_.end())
    {
        medicines_.at(name) = pre;
    }
    else
    {
        medicines_.insert({ name, pre });
    }
}

/**
 * @brief Removes a prescription for this person
 * @param name String name of medicine
 */
void Person::remove_medicine(const std::string& name)
{
    medicines_.erase(name);
}

/**
 * @brief Prints this person's id
 */
void Person::print_id() const
{
    std::cout << id_;
    //date_of_birth_.print();
    //std::cout << std::endl;
}

/**
 * @brief Prints this person's medicines
 * @param pre_text Text in front of printouts
 */
void Person::print_medicines(const std::string& pre_text) const
{
    if (medicines_.empty())
    {
        std::cout << " None" << std::endl;
        return;
    }
    std::cout << std::endl;
    for (auto iter = medicines_.begin(); iter != medicines_.end(); ++iter)
    {
        std::cout << pre_text
            << iter->first << " "
            << iter->second.strength << " mg x "
            << iter->second.dosage << std::endl;
    }
}

/**
 * @brief Overrides the less than operator
 * @param rhs Person to compare with
 * @return true if less, false if not
 */
bool Person::operator<(const Person& rhs) const
{
    return id_ < rhs.id_;
}
