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
 * @brief Ends this careperiod by setting today as the end date
 */
void CarePeriod::end_careperiod()
{
    end_ = utils::today;
}
