/*
Name and surname:

INSTRUCTIONS:
(1)  Implement functions so that they fulfill the description at their declarations.
(2)  The entire implementation must be in this one file.
(3)  Submit only this source file (with completed solutions).
(4)  The program must be compilable.
(5)  Global and static variables are forbidden.
(6)  Under no circumstances change the declarations of functions that you are supposed to program
     (do not change names, return values, nor type and number of parameters in given functions).
     Do not change implementations of given data types, nor implementations of finished helper functions
     (unless stated otherwise in the task assignment).
(7)  If needed, you can add additional helper functions or data types to the code.
(8)  Test your solution (in the 'main' function and using added helper functions or data types).
     Test code will not be graded.
(9)  The 'main' function must be last in the source code.
*/

#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATA TYPES
//-------------------------------------------------------------------------------------------------

// Position in a plane
struct Position
{
    int x; // x-coordinate
    int y; // y-coordinate
};

// Date
struct Date
{
    int year;  // year
    int month; // month
    int day;   // day
};

// Function execution success
enum class Result
{
    SUCCESS, // function executed successfully
    FAILURE  // error during function execution
};

//-------------------------------------------------------------------------------------------------
// TASK 1 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function prints the data in the structure to standard output.
    The implementation must use 'std::cout'.
    Print format must be according to the following examples. Without newline. Without quotes. Maintain spacing.

    EXAMPLES:
        "x: 10, y: 20"
        "x: -12345, y: 2"

    PARAMETER:
        [in] position - position to be printed
*/
void print(const Position *position)
{
    std::cout << "x: " << position->x << ", y: " << position->y;
}

//-------------------------------------------------------------------------------------------------
// TASK 2 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    Implement the same functionality as in the first example. The difference is only the parameter type.
*/
void print(const Position &position)
{
    std::cout << "x: " << position.x << ", y: " << position.y;
}

//-------------------------------------------------------------------------------------------------
// TASK 3 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function reads two numbers sequentially from standard input. Stores them as x and y components of position 'position'.
    The implementation must use 'std::cin' and formatted input.

    PARAMETER:
        - [out] position - position whose values will be set according to data from standard input.

    INPUT CONDITIONS:
        Text entered on standard input contains two integers that can be represented by type 'int'.
        You don't need to handle the possibility of incorrect data on standard input.
 */
void readFromStandardInput(Position *position)
{
    std::cin >> position->x >> position->y;
}

//-------------------------------------------------------------------------------------------------
// TASK 4 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function returns the largest value of array 'data' elements and sets 'result' according to search success.

    If the array contains elements, it returns their maximum and sets 'result' to 'SUCCESS'.
    If the array doesn't contain any elements (its length is zero),
    it returns the minimum value that can be represented by data type 'int' and sets result to 'FAILURE'.

    PARAMETERS:
        [in] data    - address of array start
        [in] length  - number of array elements (array length)
        [out] result - indicates success of finding maximum

    RETURN VALUE:
        If array contains elements, returns the value of the largest element of array 'data'.
        If array doesn't contain elements, returns minimum value representable by data type 'int'.

    EXAMPLES:
        input: (1, 2, 5, 0, 1) => return value: 5,  result: 'Result::SUCCESS'
        input: (-5, -2, -10)   => return value: -2, result: 'Result::SUCCESS'
        input: () => return value: minimum value representable by data type 'int', result: 'Result::FAILURE'
*/
int maximum(const int *data, std::size_t length, Result *result)
{

    if (!length)
    {
        *result = Result::FAILURE;
        return INT_MIN;
    }

    int max = data[0];

    cout << "max: " << max << endl;

    for (std::size_t i = 1; i < length; i++)
    {
        if (max < data[i])
        {
            max = data[i];
        }
    }

    *result = Result::SUCCESS;
    return max;
}

//-------------------------------------------------------------------------------------------------
// TASK 5 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function returns the number of characters needed to write number 'value' (in decimal number system).

    PARAMETER:
        - [in] value - analyzed value

    RETURN VALUE:
        Number of characters needed for text representation of value 'value'

    EXAMPLES:
        - input: 18002 => output: 5
        - input: 2     => output: 1
        - input: 0     => output: 1
        - input: -500  => output: 4
*/
int numDigits(int value)
{
    return std::to_string(value).length();
}

//-------------------------------------------------------------------------------------------------
// TASK 6 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function prints a date to standard output according to the given format.

    The printed text will contain a copy of text in 'format', but
    character 'D' replaces with day,
    character 'M' replaces with month,
    character 'Y' replaces with year in the date.

    PARAMETERS:
        - [in] date - date
        - [in] format - date printing format

    EXAMPLES:
        Let the date be April 10, 2020
        - format: "D. M. Y" => "10. 4. 2020"
        - format: "D. M."   => "10. 4."
        - format: "Exam will be D. M. Y, in room BC 300" => "Exam will be 10. 4. 2020, in room BC 300"
        - format: "M/D/Y"   => "4/10/2020"
        - format: "Y-M-D"   => "2020-4-10"

    NOTE:
        Notice the function overloading. This source file contains 3 functions named 'print'.
*/
void print(const Date *date, const char *format)
{
    for (std::size_t i = 0; i < std::strlen(format); i++)
    {
        if (format[i] == 'D')
        {
            std::cout << date->day;
        }
        else if (format[i] == 'M')
        {
            std::cout << date->month;
        }
        else if (format[i] == 'Y')
        {
            std::cout << date->year;
        }
        else
        {
            std::cout << format[i];
        }
    }
}

//-------------------------------------------------------------------------------------------------
// TASK 7 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function creates a new date according to parameters and returns its address.
    Use operator 'new' for dynamic memory allocation.

    PARAMETERS:
        [in] day   - day in date
        [in] month - month in date
        [in] year  - year in date

    RETURN VALUE:
        Address of dynamically allocated date whose content is given by parameters
*/
Date *create(int day, int month, int year)
{
    return new Date{year, month, day}; // This matches the struct order
}
//-------------------------------------------------------------------------------------------------
// TASK 8 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function deallocates date. Sets the pointer to date to 'nullptr'.
    Use operator 'delete' for memory deallocation.

    PARAMETER:
        [in, out] date - address of pointer to date

    OUTPUT CONDITIONS:
        Date at address (*date) is deallocated.
        (*date) has value 'nullptr'.
*/
void destroy(Date **date)
{
    delete *date;
    *date = nullptr;
}

//-------------------------------------------------------------------------------------------------
// TASK 9 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function determines if the year in the date is a leap year.

    PARAMETER:
        [in] date - date

    RETURN VALUE:
        'true'  - if year is a leap year
        'false' - if year is not a leap year

    INPUT CONDITION:
        Year in date is a positive number

    DETERMINING LEAP YEAR:
        A year divisible by 4 is a leap year except when it's divisible by 100, but not divisible by 400.
        Examples:
            - leap years: 2000, 2004, 2008
            - non-leap years: 2001, 2002, 2003, 2005, 2006, 2007, 2009, 2010
            - leap years: 1600, 2000, 2400
            - non-leap years: 1500, 1700, 1800, 1900, 2100, 2200, 2300, 2500
*/
bool isInLeapYear(const Date *date)
{
    if (date->year % 4 == 0)
    {
        if (date->year % 100 == 0 && date->year % 400 != 0)
        {
            return false;
        }

        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------
// TASK 10 (0.4 points)
//-------------------------------------------------------------------------------------------------
/*
    The function determines if the date is valid.

    Need to verify if the date can exist. For example
    in January the day can be from 1 to 31,
    in February from 1 to 28 or 29, depending on whether the year is a leap year.
    A year has months 1 to 12.

    PARAMETER:
        [in] date - date

    RETURN VALUE:
        'true'  - if date is valid
        'false' - if date is not valid

    INPUT CONDITION:
        Year in date is a positive number
*/
bool isValid(const Date *date)
{
    if (date->day < 1)
    {
        return false;
    }

    switch (date->month)
    {
    case 1: // January
        return date->day <= 31;
    case 2: // February
        return isInLeapYear(date) ? date->day <= 29 : date->day <= 28;
    case 3: // March
        return date->day <= 31;
    case 4: // April
        return date->day <= 30;
    case 5: // May
        return date->day <= 31;
    case 6: // June
        return date->day <= 30;
    case 7: // July
        return date->day <= 31;
    case 8: // August
        return date->day <= 31;
    case 9: // September
        return date->day <= 30;
    case 10: // October
        return date->day <= 31;
    case 11: // November
        return date->day <= 30;
    case 12: // December
        return date->day <= 31;
    default:
        return false;
    }
}

//-------------------------------------------------------------------------------------------------
// TESTING
//-------------------------------------------------------------------------------------------------

// you can add helper testing functions and structures here

int main()
{
    cout << "=== TESTING TASK 1 & 2: print() ===" << endl;
    Position pos1 = {10, 20};
    cout << "Test 1 (reference): ";
    print(pos1);

    Position *pos2 = new Position{-12345, 2};
    cout << "Test 2 (pointer): ";
    print(pos2);

    // Clean up
    delete pos2;

    Position pos3 = {0, 0};
    cout << "Test 3 (zero values): ";
    print(&pos3);
    cout << endl;

    cout << "=== TESTING TASK 3: readFromStandardInput() ===" << endl;
    cout << "Enter two integers (e.g., 5 -10): ";
    Position inputPos;
    readFromStandardInput(&inputPos);
    cout << "You entered: ";
    print(&inputPos);
    cout << endl;

    cout << "=== TESTING TASK 4: maximum() ===" << endl;
    Result result;

    int arr1[] = {1, 2, 5, 0, 1};
    int max1 = maximum(arr1, 5, &result);
    cout << "Test 1: {1, 2, 5, 0, 1} => max: " << max1
         << ", result: " << (result == Result::SUCCESS ? "SUCCESS" : "FAILURE") << endl;

    int arr2[] = {-5, -2, -10};
    int max2 = maximum(arr2, 3, &result);
    cout << "Test 2: {-5, -2, -10} => max: " << max2
         << ", result: " << (result == Result::SUCCESS ? "SUCCESS" : "FAILURE") << endl;

    int max3 = maximum(nullptr, 0, &result);
    cout << "Test 3: empty array => max: " << max3
         << ", result: " << (result == Result::SUCCESS ? "SUCCESS" : "FAILURE") << endl;

    int arr4[] = {100};
    int max4 = maximum(arr4, 1, &result);
    cout << "Test 4: {100} => max: " << max4
         << ", result: " << (result == Result::SUCCESS ? "SUCCESS" : "FAILURE") << endl;
    cout << endl;

    cout << "=== TESTING TASK 5: numDigits() ===" << endl;
    cout << "Test 1: 18002 => " << numDigits(18002) << " digits (expected: 5)" << endl;
    cout << "Test 2: 2 => " << numDigits(2) << " digits (expected: 1)" << endl;
    cout << "Test 3: 0 => " << numDigits(0) << " digits (expected: 1)" << endl;
    cout << "Test 4: -500 => " << numDigits(-500) << " digits (expected: 4)" << endl;
    cout << "Test 5: -1 => " << numDigits(-1) << " digits (expected: 2)" << endl;
    cout << "Test 6: 999999 => " << numDigits(999999) << " digits (expected: 6)" << endl;
    cout << endl;

    cout << "=== TESTING TASK 6: print(Date, format) ===" << endl;
    Date date1 = {2020, 4, 10}; // April 10, 2020
    cout << "Date: April 10, 2020" << endl;
    cout << "Format 'D. M. Y': ";
    print(&date1, "D. M. Y");
    cout << endl;

    cout << "Format 'D. M.': ";
    print(&date1, "D. M.");
    cout << endl;

    cout << "Format 'Exam will be D. M. Y, in room BC 300': ";
    print(&date1, "Exam will be D. M. Y, in room BC 300");
    cout << endl;

    cout << "Format 'M/D/Y': ";
    print(&date1, "M/D/Y");
    cout << endl;

    cout << "Format 'Y-M-D': ";
    print(&date1, "Y-M-D");
    cout << endl;
    cout << endl;

    cout << "=== TESTING TASK 7 & 8: create() and destroy() ===" << endl;
    Date *dynamicDate = create(15, 7, 2023);
    cout << "Created date (15. 7. 2023): ";
    print(dynamicDate, "D. M. Y");
    cout << endl;

    cout << "Date pointer before destroy: " << dynamicDate << endl;
    destroy(&dynamicDate);
    cout << "Date pointer after destroy: " << dynamicDate << " (should be 0 or nullptr)" << endl;
    cout << endl;

    cout << "=== TESTING TASK 9: isInLeapYear() ===" << endl;
    Date leapTest1 = {2000, 1, 1};
    Date leapTest2 = {2004, 1, 1};
    Date leapTest3 = {2001, 1, 1};
    Date leapTest4 = {1900, 1, 1};
    Date leapTest5 = {2024, 1, 1};

    cout << "Year 2000: " << (isInLeapYear(&leapTest1) ? "LEAP" : "NOT LEAP") << " (expected: LEAP)" << endl;
    cout << "Year 2004: " << (isInLeapYear(&leapTest2) ? "LEAP" : "NOT LEAP") << " (expected: LEAP)" << endl;
    cout << "Year 2001: " << (isInLeapYear(&leapTest3) ? "LEAP" : "NOT LEAP") << " (expected: NOT LEAP)" << endl;
    cout << "Year 1900: " << (isInLeapYear(&leapTest4) ? "LEAP" : "NOT LEAP") << " (expected: NOT LEAP)" << endl;
    cout << "Year 2024: " << (isInLeapYear(&leapTest5) ? "LEAP" : "NOT LEAP") << " (expected: LEAP)" << endl;
    cout << endl;

    cout << "=== TESTING TASK 10: isValid() ===" << endl;
    Date valid1 = {2020, 1, 31};   // Valid: January 31
    Date valid2 = {2020, 2, 29};   // Valid: February 29 (leap year)
    Date invalid1 = {2019, 2, 29}; // Invalid: February 29 (not leap year)
    Date invalid2 = {2020, 4, 31}; // Invalid: April has only 30 days
    Date invalid3 = {2020, 13, 1}; // Invalid: month 13
    Date invalid4 = {2020, 0, 15}; // Invalid: month 0
    Date invalid5 = {2020, 6, 0};  // Invalid: day 0
    Date valid3 = {2020, 12, 31};  // Valid: December 31

    cout << "Date 31.1.2020: " << (isValid(&valid1) ? "VALID" : "INVALID") << " (expected: VALID)" << endl;
    cout << "Date 29.2.2020: " << (isValid(&valid2) ? "VALID" : "INVALID") << " (expected: VALID)" << endl;
    cout << "Date 29.2.2019: " << (isValid(&invalid1) ? "VALID" : "INVALID") << " (expected: INVALID)" << endl;
    cout << "Date 31.4.2020: " << (isValid(&invalid2) ? "VALID" : "INVALID") << " (expected: INVALID)" << endl;
    cout << "Date 1.13.2020: " << (isValid(&invalid3) ? "VALID" : "INVALID") << " (expected: INVALID)" << endl;
    cout << "Date 15.0.2020: " << (isValid(&invalid4) ? "VALID" : "INVALID") << " (expected: INVALID)" << endl;
    cout << "Date 0.6.2020: " << (isValid(&invalid5) ? "VALID" : "INVALID") << " (expected: INVALID)" << endl;
    cout << "Date 31.12.2020: " << (isValid(&valid3) ? "VALID" : "INVALID") << " (expected: VALID)" << endl;

    cout << "\n=== ALL TESTS COMPLETED ===" << endl;

    return 0;
}