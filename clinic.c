/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Sukhad Adhikari
Student ID#: 15651219
Email      : sadhikari28@myseneca.ca
Section    : ZBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do
    {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{

    int i;//index
    int records = 0; //tracks the records 
    displayPatientTableHeader();
    for (i = 0; i < max; i++)//iterating till the maximum patients
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);

        }
        else
        {
            records++;//adding 1 for each uneligible records
        }
    }
    printf("\n");
    if (records == max)//checking if there is nothing to display
    {
        printf("\"*** No records found ***\"\n");
    }
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selectOption;//integer that stores either to check by patient number or by phone number
    int flag = 0;//flag variable
    do
    {
        printf("Search Options\n"
            "==========================\n");
        printf("1) By patient number\n"
            "2) By phone number\n");
        printf("..........................\n"
            "0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &selectOption);
        printf("\n");
        if (selectOption == 1)
        {
            searchPatientByPatientNumber(patient, max);//calling to search for patients by patientNumber
        }
        else if (selectOption == 2)
        {
            searchPatientByPhoneNumber(patient, max);//calling the function to search patient by patient number
        }
        else if (selectOption == 0)//condition to go back from this submenu
        {
            flag = 1;
            clearInputBuffer();//clearing the buffer
        }

    } while (flag == 0);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i;//index
    int emptySpace = 0;//variable that holds the number of free space
    int a;//element that holds the place where new value is going to be stored

    for (i = 0; i < max; i++)
    {
        if (emptySpace == 0)//to add only one value at one time
        {
            if (patient[i].patientNumber == 0)//checking if their any empty space to store a new one or not
            {
                emptySpace++;
                a = i;//assigning the index value to store details of new patient
            }
        }
    }

    if (emptySpace == 0)//checking if there is any empty spaces or not
    {
        puts("ERROR: Patient listing is FULL!\n");
    }
    else
    {
        patient[a].patientNumber = nextPatientNumber(patient, max);//calling next patient number and assigning to that
        inputPatient(&patient[a]);//calling input patient
        puts("*** New patient record added ***\n");//displaying after adding new one
    }

}


// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int inpNum;//variable that stores the patient number that will be prompted
    int check = 0;//variable that determines either that record exists or not
    printf("Enter the patient number: ");//asking for patient number to user
    scanf("%d", &inpNum);
    printf("\n");
    check = findPatientIndexByPatientNum(inpNum, patient, max);//calling function to check either that number exists or not
    if (check == -1)
    {
        puts("\nERROR: Patient record not found!");
         
    }
    else//is in that array
    {
        menuPatientEdit(&patient[check]);//calling menupatient edit that will edit the patient details
    }

}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int inpNum;//variable that stores the patient number that will be prompted
    char opt;//index that holds the decision
    char newline;
    int check = 0;//variable that determines either that record exists or not
    printf("Enter the patient number: ");//asking for patient number to user
    scanf("%d", &inpNum);
    check = findPatientIndexByPatientNum(inpNum, patient, max);//checking where does it actually exits
    if (check != -1)
    {
        printf("\nName  : %s\n"//displaying the information according to the output
            "Number: %05d\n"
            "Phone : ", patient[check].name, patient[check].patientNumber);
        displayFormattedPhone(patient[check].phone.number);
        printf(" (%s)\n", patient[check].phone.description);

        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        do
        {
            scanf(" %c%c", &opt,&newline); 
            if (newline != '\n')
            {
                {
                    clearInputBuffer();
                    printf("ERROR: Character must be one of [yn]: ");                     
                }
            }
            else
            {
                if (opt == 'y')
                {
                    patient[check].patientNumber = 0;
                    puts("Patient record has been removed!\n");
                   
                }

                else if (opt == 'n')
                {
                    puts("Operation aborted.\n");
                    clearInputBuffer();//clearing the buffer
                }
                else//if user type other than y or y process is stopped
                {
                    printf("ERROR: Character must be one of [yn]: ");
                    clearInputBuffer();//clearing the buffer
                }
            }
        } while (newline != '\n');

    }
    else
    {
        puts("\nERROR: Patient record not found!\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//sorting function


void sort(struct Appointment* appoint, int max)
{
    int i, j;//index element
    struct Appointment temp;//temporary variable(temp) to store the appointment type

    // Storing all the date and time values in minutes for comparison
    for (i = 0; i < max; i++)
    {
        appoint[i].time.min = (appoint[i].date.year * 12 * 30 * 24 * 60) + (appoint[i].date.month * 30 * 24 * 60) + (appoint[i].date.day * 24 * 60) + (appoint[i].time.hour * 60) + appoint[i].time.min;//converting minutes for each appointments
    }

    // Using bubble sort to compare minutes and then swap the structs
    for (i = 0; i< max; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (appoint[j].time.min > appoint[j + 1].time.min)
            {
                temp = appoint[j];//storing to temp variable
                appoint[j] = appoint[j + 1];
                appoint[j + 1] = temp;
            }
        }
    }

    //converting to minutes
    for (i = 0; i < max; i++)
    {
        appoint[i].time.min = appoint[i].time.min - (appoint[i].date.year * 12 * 30 * 24 * 60) - (appoint[i].date.month * 30 * 24 * 60) - (appoint[i].date.day * 24 * 60) - (appoint[i].time.hour * 60);
    }

}

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int i, z;//index element
    displayScheduleTableHeader(&data->appointments->date, 5);//calling header function

    sort(data->appointments, data->maxAppointments);//sorting

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (z = 0; z < data->maxPatient; z++)//looking for same patient number from patientdata txt and appointmentData.txt
        {
            if (data->appointments[i].patientNumber == data->patients[z].patientNumber)//check for the patientNumber in patients and appointments
            {
                displayScheduleData(&data->patients[z], &data->appointments[i], 8);//Display fuction
            }
        }

    }
    puts("");

}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int tempYear;//variable stores the year
    int tempMonth;//stores the month
    int tempDay;//stores the day
    int i, a;//index
    int header = 0;//variable for header

    printf("Year        : ");
    tempYear = inputInt();//calling 
    printf("Month (1-12): ");
    
    tempMonth = inputIntRange(1, 12);//calling inputIntrange to validate the months
    
    if (tempYear == 2024 && tempMonth == 2)
    {
        printf("Day (1-29)  : ");
        tempDay = inputIntRange(1, 29);//calling inputIntrange to validate the day:: to overcome the exception
    }
    else
    {
        printf("Day (1-28)  : ");
        tempDay = inputIntRange(1, 28);//calling inputIntrange to validate the days
    }
    sort(data->appointments, data->maxAppointments);//Sorting all the values


    for (i = 0; i < data->maxAppointments; i++)//iterating till maxappointments
    {
        if (tempYear == data->appointments[i].date.year && tempMonth == data->appointments[i].date.month && tempDay == data->appointments[i].date.day)//check for year
        {
            for (a = 0; a < data->maxPatient; a++)//looking for same patient number from patientdata txt and appointmentData.txt
            {
                if (data->appointments[i].patientNumber == data->patients[a].patientNumber)//checking for the same patient number in appointmentData.txt and patientData.txt
                {
                    if (header == 0)
                    {
                        printf("\n");
                        displayScheduleTableHeader(&data->appointments[i].date, 0);
                    }
                    displayScheduleData(&data->patients[a], &data->appointments[i], 0);//Display function
                    header++;
                }
            }
        }
    }
    puts("");
}

// Add an appointment record to the appointment array
// Todo:

void addAppointment(struct Appointment* appoint, int maxAppointments, struct Patient* patient, int maxPatient)
{

    int i;//index
    int tmpPatientnum;//temp variable stores the patient number
    int tempYear;//temporary variable stores year
    int tempMonth;//temp variable stores month
    int tempDay;//temp variable stores day
    int tempHour;//temp variable stores hour
    int tempMin;//temp variable stores minute
    int flag;//flag varible


    int emptySpace = 0;//variable that holds the number of free space
    int a = 0;//element that holds the place where new value is going to be stored

    for (i = 0; i < maxAppointments; i++)
    {
        if (appoint[i].patientNumber < 1)//checking if their any empty space to store a new one or not
        {
            emptySpace++;
            a = i;//assigning the index value to store details of new patient
        }
        if (emptySpace == 1)//mannuually making condition false to get only one space to record for new data
        {
            i = maxAppointments;
        }
    }



    if (emptySpace == 0)//checking if there is any empty spaces or not
    {
        puts("ERROR: Patient listing is FULL!\n");
    }
    else
    {
        printf("Patient Number: ");
        tmpPatientnum = inputIntPositive();

        do
        {
            flag = 0;
            int subMenuflag;
            printf("Year        : ");

            tempYear = inputIntPositive();
            printf("Month (1-12): ");
            tempMonth = inputIntRange(1, 12);
            printf("Day (1-31)  : ");
            tempDay = inputIntRange(1, 31);
            do
            {
                subMenuflag = 0;
                printf("Hour (0-23)  : ");
                tempHour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                tempMin = inputIntRange(0, 59);

                if (tempHour == END_HOUR)//not more than end hour
                {
                    if (tempMin == 0)
                    {
                        subMenuflag++;
                    }
                }
                if (tempHour >= START_HOUR && tempHour <= END_HOUR - 1)//filtering times according to the macros time available
                {
                    
                    if (tempMin % MINUTE_INTERVAL == 0)//chcking for minute
                    {
                        subMenuflag++;
                    }
                }
                if (subMenuflag == 0)
                {
                    printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
                }
            } while (subMenuflag == 0);


            
            flag = slotcheck(appoint, maxAppointments, tempYear, tempMonth, tempDay, tempHour, tempMin);
            if (flag != 0)
            {
                puts("\nERROR: Appointment timeslot is not available!\n");
            }
            else//storing the values
            {
                appoint[a].date.year = tempYear;
                appoint[a].date.month = tempMonth;
                appoint[a].date.day = tempDay;
                appoint[a].time.hour = tempHour;
                appoint[a].time.min = tempMin;
                appoint[a].patientNumber = tmpPatientnum;
            }
        } while (flag != 0);




        puts("\n*** Appointment scheduled! ***\n");
    }


}
//check either the appointment records is in the appointment list or not
int slotcheck(struct Appointment* appoint, int max, int tempyear, int tempMonth, int tempDay, int tempHour, int tempMin)
{
    int i;
    int flag = 0;
    for (i = 0; i < max; i++)//checking for the same record from the booked slot
    {
        if ((appoint[i].date.year == tempyear) && (appoint[i].date.month == tempMonth) && (appoint[i].date.day == tempDay) && (appoint[i].time.hour == tempHour) && (appoint[i].time.min == tempMin))
        {
            flag++;
        }
    }
    return flag;
}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appoint, int maxAppointments, struct Patient* patient, int maxPatient)
{
    char decision;
    int check = 0;//index that tracks the match of record 
    int patNum;//variable that store the patient num
    int year = 0;
    int month = 0;
    int day = 0;
    int z;//index
    int pat;//store the patient index
    int val;//stores the appointment index
    int valid = 0;
    printf("Patient Number: ");
    patNum = inputIntPositive();
 
    check = appointmentCheck(appoint, maxAppointments, patNum);
    if (check == -1)
    {
        puts("ERROR: Patient record not found!\n");
    }
    else
    {
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (1-12): ");
        month = inputIntRange(1, 12);
        printf("Day (1-29)  : ");
        day = inputIntRange(1, 29);
        //checking for the records by patient number
      
   
        //for patients
        for (z = 0; z < maxPatient; z++)
        {
            if (patNum == patient[z].patientNumber)
            {
                pat = z; //getting patient index from patient data.txt
            }
        }
      
        printf("\nName  : %s\n"//displaying the information according to the output
            "Number: %05d\n"
            "Phone : ", patient[pat].name, patient[pat].patientNumber);
        displayFormattedPhone(patient[pat].phone.number);
        printf(" (%s)\n", patient[pat].phone.description);
        
        printf("Are you sure you want to remove this appointment (y,n): ");
        scanf(" %c", &decision);
        if (decision == 'y')
        {
            while (valid == 0 && z < maxAppointments)//checking 
            {
                if ((appoint[z].patientNumber == patNum) && (appoint[z].date.day == day) && (appoint[z].date.month == month) && (appoint[z].date.year == year))//checking for the patient number,day, month 
                {
                    valid = 1;
                }
                if (valid == 1)
                {
                    val = z;//index of the removing appointment;
                }
                z++;
            }

            appoint[val].patientNumber = 0;//assigning to safe empty state              
            puts("\nAppointment record has been removed!\n");
            clearInputBuffer();

        }
        else
        {
            puts("Cancelled\n");
        }

    }
}
//check either the patNum is in the appointment list or not
int appointmentCheck(struct Appointment* appoint, int max, int patNum)///check the patient Number exists or not
{
    int i;
    int check = 0;
    for (i = 0; i < max; i++)
    {
        if (appoint[i].patientNumber == patNum)//check for patient number 
        {
            check = i;
        }
    }
    if (check == 0)
    {
        check = -1;
    }
    return check;
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int input;//integer that holds the patient number that is going to be searched
    int check;//variable that goona check either there is that patient number or not
    printf("Search by patient number: ");
    scanf("%d", &input);
    check = findPatientIndexByPatientNum(input, patient, max);
    printf("\n");
    if (check != -1)
    {
        printf("Name  : %s\n"//displaying the patient details
            "Number: %05d\n"
            "Phone : ", patient[check].name, patient[check].patientNumber);
        displayFormattedPhone(patient[check].phone.number);
        printf(" (%s)\n", patient[check].phone.description);
        printf("\n");
        clearInputBuffer();
    }
    else
    {
        printf("*** No records found ***\n\n");
    }

    suspend();
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNum[PHONE_LEN + 1] = { 0 };//array the stores input phone number from user 
    int record;//tracks the no of matches
    int i = 0;//index
    int matchIndex = 0;//stores the number of matches; assigning to zero

    printf("Search by phone number: ");

    inputCString(phoneNum, 10, 10);


    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        record = strcmp(patient[i].phone.number, phoneNum);
        if (record == 0)//checking for the matching phonenumbers 
        {
            printf("%05d %-15s ", patient[i].patientNumber,
                patient[i].name);
            displayFormattedPhone(patient[i].phone.number);//calling function to display the phone number
            printf(" (%s)\n", patient[i].phone.description);
            matchIndex++;
        }
    }
    printf("\n");
    if (matchIndex == 0)//checking if there is zero matches?
    {
        printf("*** No records found ***\n\n");
    }
    clearInputBuffer();
    suspend();
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int highestNum = 0;//highest patient number of the array
    int i;//index
    for (i = 0; i < max; i++)
    {
        if (highestNum < patient[i].patientNumber)
        {
            highestNum = patient[i].patientNumber;//assigning the heighest number to the heighest patient number of the array
        }
    }
    highestNum = highestNum + 1;//adding one to the heighest num
    return highestNum;
}


// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i;//index
    int check = -1; //for checking either it is in or not
    int finalValue;//returning value from the function
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)//checking for matching numbers
        {
            check = i;
        }
    }
    if (check != -1)//no matching numbers
    {
        finalValue = check;
    }
    else
    {
        finalValue = check;//if matching assigning to index value
        clearInputBuffer();//clearing the buffer
    }
    return finalValue;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n------------------\nNumber: %05d\nName  : ",
        patient->patientNumber);
    inputCString(patient->name, 1, NAME_LEN);//calling the function to get a patient name
    putchar('\n');
    inputPhoneData(&patient->phone);//calling this unction to get phone details
    clearInputBuffer();
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int inpSelect;//input selection

    puts("Phone Information\n"
        "-----------------");

    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n2. Home\n3. Work\n4. TBD\n");
    printf("Selection: ");



    scanf(" %d", &inpSelect);

    if (inpSelect >= 1 && inpSelect <= 3)
    {
        if (inpSelect == 1)
        {
            strcpy(phone->description, "CELL");//copying to the phone description
            printf("\nContact: %s\n", phone->description);
        }
        else if (inpSelect == 2)
        {
            strcpy(phone->description, "HOME");
            printf("\nContact: %s\n", phone->description);
        }
        else if (inpSelect == 3)
        {
            strcpy(phone->description, "WORK");
            printf("\nContact: %s\n", phone->description);
        }

        printf("Number : ");
        inputCString(phone->number, 10, 10);//getting and storing phone number


    }
    else if (inpSelect == 4)
    {
        strcpy(phone->description, "TBD");
        *phone->number = 0;

    }
    else
    {
        printf("ERROR!");//if any selection displaying error
    }
    printf("\n");
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;// variable that stores the total number of records 
    FILE* fp = NULL;
    fp = fopen(datafile, "r");//opening the file for reading
    if (fp != NULL)
    {
        while (i < max && fscanf(fp, " %d|%[^|]|%[^|]|%[^\n]\n", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
        {
            i++;
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file\n");
    }

    return i;//returning the total number of records
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;// variable that stores the total number of records 
    FILE* fp = NULL;

    fp = fopen(datafile, "r");//opening the file for reading

    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF)//checking the record in a line
        {
            i++;//increasing for each record
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file\n");
    }

    return i;//returning the total number of records
}