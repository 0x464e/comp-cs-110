/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Program author
 * Name: Otto 
 * Student number: 
 * UserID: 
 * E-Mail: 
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>
#include <set>

class CarePeriod
{
public:
    //Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    //Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    //Destructor.
    ~CarePeriod();

    //Returns this care period's patient
    Person* get_patient() const;

    //Ends this care period
    void end_careperiod(const Date& end_date);

    //Adds a staff member to this care period
    void add_staff(const std::string& id);

    //Prints this care period's duration
    void print_careperiod_duration(const std::string& pre_text = "") const;

    //Prints staff assigned to this care period
    void print_staff(const std::string& pre_text = "") const;

    //Gets staff assigned to this care period
    std::set<std::string> get_staff() const;

private:
    Person* patient_;
    Date start_;
    Date end_;

    //staff members assigned to this care period
    //set used due to duplicates being unwanted, and alphabetical order
    //is needed in other commands
    std::set<std::string> staff_;
};

#endif // CAREPERIOD_HH
