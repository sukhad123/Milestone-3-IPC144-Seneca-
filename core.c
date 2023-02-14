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

#include "core.h"
#include<string.h>
#include <ctype.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
int inputInt(void)
{
    int value;//input character
    char newline;
    int repeat; //flag varaible
    do
    {
        scanf("%d%c", &value, &newline);

        if (newline == '\n')
        {
            repeat = 1;
        }
        else
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
            repeat = 0;
        }

    } while (repeat == 0);
    return value;
}


int inputIntPositive(void)
{
    int value;//input character 
    int repeat = 0; //flag variable
    do
    {
        value = inputInt();//calling above function to get an integer value
        if (value > 0)
        {
            repeat = 1;
        }

        else
        {
            printf("ERROR! Value must be > 0: ");
            repeat = 0;
        }

    } while (repeat == 0);
    return value;
}


int inputIntRange(int min_val, int max_val)
{
    int value;//input 
    int repeat; //flag varaible
    do
    {

        value = inputInt();//getting a value
        if (value <= max_val && value >= min_val)
        {
            repeat = 1;
        }
        else
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", min_val, max_val);
            repeat = 0;
        }
    } while (repeat == 0);
    return value;
}


int inputCharOption(const char charac[])
{

    char singChar;//character input
    int i;//tracks the number of charcters in a string
    int repeat = 0;//flag variable
    int a;
    do
    {
        i = 0;
        scanf("%c", &singChar);
        do
        {
            if (singChar == charac[i])
            {
                repeat = 1;
            }
            i++;
        } while (charac[i] != '\0');
        if (repeat != 1)
        {
            printf("ERROR: Character must be one of [");
            for (a = 0; a < i; a++)
            {
                printf("%c", charac[a]);

            }
            printf("]: ");
        }
        clearInputBuffer();
    } while (repeat == 0);
    return singChar;
}



void inputCString(char* ptr, int minCharac, int maxCharac)
{
    int i;//stores the total characters of the strings
 
    int check = 0;//check for digit or not
    int repeat = 0;//flag variable

    char localStr[500] = { 0 };
    do
    {

        int a = 0; //index element

        scanf(" %[^\n]", localStr);
        i = strlen(localStr);// calculating the length of localStr
        if (i >= minCharac && i <= maxCharac)
        {
            repeat = 1;
        }
        else
        {
            for (a = 0; a < i; a++)
            {

                if (isdigit(localStr[a]) != 0)//checking either the number is digit or not
                {
                    check++;
                }
            }

            if (check != 0)//digit condition
            {
                if (check != 10)
                {
                    printf("Invalid %d-digit number! Number: ", maxCharac);
                }
            }
            else
            {
                if (minCharac == maxCharac)
                {
                    printf("ERROR: String length must be exactly %d chars: ", minCharac);
                }
                else if (i > maxCharac)
                {
                    printf("ERROR: String length must be no more than %d chars: ", maxCharac);
                }
                else
                {
                    printf("ERROR: String length must between %d and %d chars: ", minCharac, maxCharac);
                }
                clearInputBuffer();
            }
        }

    } while (repeat == 0);
 
    strcpy(ptr, localStr);
}

void displayFormattedPhone(const char* ptr)
{
    int noCharacters = 0;//stores the number of elements in arrays
    int check = 0;//check for the conditions
    int a;
    if (ptr == NULL)
    {
        check = 1;
    }
    else
    {
        noCharacters = strlen(ptr);// calculating the length of ptr
        for (a = 0; a < noCharacters; a++)
        {

            if (isdigit(ptr[a]) != 0)//checking either the number is digit or not
            {
                check++;
            }
        }
    }
    if (check == 10 && noCharacters == 10)
    {
        printf("(");
        for (a = 0; a < 3; a++)
        {
            printf("%c", ptr[a]);
        }
        printf(")");
        for (a = 3; a < 6; a++)
        {
            printf("%c", ptr[a]);
        }
        printf("-");
        for (a = 6; a < 10; a++)
        {
            printf("%c", ptr[a]);
        }

    }
    else
    {
        printf("(___)___-____");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////