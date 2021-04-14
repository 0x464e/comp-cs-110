#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
= default;

Hospital::~Hospital()
{
    // Deallocating staff
    for (auto iter = staff_.begin(); iter != staff_.end(); ++iter)
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
}

void Hospital::recruit(Params params)
{
    const auto& specialist_id = params.at(0);
    if (staff_.find(specialist_id) != staff_.end())
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    const auto new_specialist = new Person(specialist_id);
    staff_.insert({ specialist_id, new_specialist });
    std::cout << STAFF_RECRUITED << std::endl;
}

/**
 * @brief Enters a new patient to the hospital system\n
 * and creates creates a careperiod for them
 * @param params String vector containing one element, id of the person to be added
 */
void Hospital::enter(Params params)
{
    const auto& id = params.at(0);

    //if there already is a patient by this id
    if(current_patients_.find(id) != current_patients_.end())
    {
        std::cout << ALREADY_EXISTS << id << std::endl;
        return;
    }

    Person* patient;

    //if this person has never been in the hospital before
    if(patients_careperiods_.find(id) == patients_careperiods_.end())
    {
        patient = new Person(id);
        const auto careperiod = new CarePeriod(Date(utils::today), patient);
        //this person's very first careperiod
        patients_careperiods_.insert({ id, { careperiod } });
    }
    else
    {
        //if a person has been in the hospital before, they're guaranteed to
        //have at least one care period, from which we can get the person object
        patient = patients_careperiods_.at(id).at(0)->get_patient();
        patients_careperiods_.at(id)
            .push_back(new CarePeriod(Date(utils::today), patient));
    }

    current_patients_.insert({ id, patient });
    std::cout << PATIENT_ENTERED << std::endl;
}

/**
 * @brief Removes a patient from the hospital and closes their care period
 * @param params String vector containing one element, id of the patient
 */
void Hospital::leave(Params params)
{
    const auto& id = params.at(0);

    //if a patient by this id doesn't exist
    if (current_patients_.find(id) == current_patients_.end())
    {
        std::cout << CANT_FIND << id << std::endl;
        return;
    }

    //a patient can only have one active careperiod at the same, 
    //and it'll be the latest one
    patients_careperiods_.at(id).back()->end_careperiod();
    current_patients_.erase(id);

    std::cout << PATIENT_LEFT << std::endl;
}

/**
 * @brief Assigns a staff to work with the given patient's current care period
 * @param params String vector containing two elements:
 * - id of the staff member
 * - id of the patient
 */
void Hospital::assign_staff(Params params)
{
    const auto& staff_id = params.at(0);
    const auto& patient_id = params.at(1);

    //if a staff or patient by specified id doesn't exist
    if (staff_.find(staff_id) == staff_.end())
    {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }
    if(current_patients_.find(patient_id) == current_patients_.end())
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    //a patient's latest care period is always the current care period
    patients_careperiods_.at(patient_id).back()->add_staff(staff_id);
}

void Hospital::add_medicine(Params params)
{
    const auto& medicine = params.at(0);
    const auto& strength = params.at(1);
    const auto& dosage = params.at(2);
    const auto& patient = params.at(3);
    if (!utils::is_numeric(strength, true) ||
        !utils::is_numeric(dosage, true))
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
        patient_iter = current_patients_.find(patient);
    if (patient_iter == current_patients_.end())
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    const auto& medicine = params.at(0);
    const auto& patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
        patient_iter = current_patients_.find(patient);
    if (patient_iter == current_patients_.end())
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    
}

void Hospital::print_care_periods_per_staff(Params params)
{

}

void Hospital::print_all_medicines(Params)
{

}

void Hospital::print_all_staff(Params)
{
    if (staff_.empty())
    {
        std::cout << "None" << std::endl;
        return;
    }
    for (std::map<std::string, Person*>::const_iterator iter = staff_.begin();
        iter != staff_.end();
        ++iter)
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{

}

void Hospital::print_current_patients(Params)
{

}

void Hospital::set_date(Params params)
{
    const auto& day = params.at(0);
    const auto& month = params.at(1);
    const auto& year = params.at(2);
    if (!utils::is_numeric(day, false) ||
        !utils::is_numeric(month, false) ||
        !utils::is_numeric(year, false))
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    const auto& amount = params.at(0);
    if (!utils::is_numeric(amount, true))
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(std::stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
