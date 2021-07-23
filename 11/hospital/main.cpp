/* Hospital
*
* Description:
* This program models a hospital system. The program starts off with an empty
* database for the system, which can then be filled with people and care periods.
* The people can be either hospital staff, or patients. Hospital staff can be 
* assigned to care periods, which belong to patients. In addition to having care
* periods, patients can have medicine prescriptions. A patient must have at least
* one care period. A care period is added to the patient every time they enter
* the hospital. Care periods have start and end dates.
* 
* This program was made to practise modularity in object oriented programming,
* using different classes together, and dynamic memory managment.
*
*
* There are 17 different commands in the program:
* Command                Param(s)                Description
* ------------------------------------------------------------------------------
* RECRUIT                <staff id>              - Adds a staff member   
* ENTER                  <patient id>            - Enters patient to hospital
* LEAVE                  <patient id>            - Removes patient from hospital
* ASSIGN_STAFF           <staff id> <patient id> - Assigns staff to patient
* ADD_MEDICINE           <medicine> <strength>   - Adds prescription to patient
*                        <dosage> <patient id>
* REMOVE_MEDICINE        <medicine> <patient id> - Remove prescription from patient
* PRINT_PATIENT_INFO     <id>                    - Prints info about a patient
* PRINT_CARE_PERIODS     <staff id>              - Prints a staff's care periods
* PRINT_ALL_MEDICINES                            - Prints all prescriptions
* PRINT_ALL_STAFF                                - Prints all staff members
* PRINT_ALL_PATIENTS                             - Prints all patients
* PRINT_CURRENT_PATIENTS                         - Prints all current patients
* SET_DATE               <day> <month> <year>    - Sets what date it is
* ADVANCE_DATE           <amount>                - Advances date
* READ_FROM              <file>                  - Reads commands from a file
* HELP                   <command>               - Prints help
* QUIT                                           - Quits the program
* 
* 
* 
* COMP.CS.110 K2021
*
* Program author
* Name: Otto 
* Student number: 
* UserID: 
* E-Mail: 
* Date: 
*
* Notes about the program and it's implementation:
* Tried to make the data sturcture as non repetetive as possible.
* This results in the design choice of not having e.g. a map where the key would
* be a patient's id, and value would be pointer to their Person object.
* I decided not to waste memory on making an extra data structure like that, 
* because the Person object can get retrieved from a care period, and a patient
* will always have at least one care period.
* */

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
