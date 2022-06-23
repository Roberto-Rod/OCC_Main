/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    date_and_time.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "time.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

enum {JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
enum {SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};

const char daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//                           J   F   M   A   M   J   J   A   S   O   N   D

// functions

char isLeapYear(int year)
{
    // check if the year is divisible by 4 or is divisible by 400
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

// from Wikipedia http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
// returns 0 = Sunday, 1 = Monday, etc.
char dayOfTheWeek(int year, char month, char date)
{
    const char t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + date) % 7;
}

uint8_t getNumberOfDaysInMonth(int month, int year)
{
    uint8_t daysThisMonth;

    if (month == FEBRUARY)
    {
        if (isLeapYear(year))
        {
            daysThisMonth = 29;
        }
        else
        {
            daysThisMonth = 28;
        }
    }
    else
    {
        daysThisMonth = daysPerMonth[month - 1];
    }

    return (daysThisMonth);
}

uint8_t getNumberOfDaysInThisMonth(RTCCFORM *time)
{
    return (getNumberOfDaysInMonth(time->month, time->year + 2000));
}

// month index is zero-based
void incrementDate(RTCCFORM *time)
{
    uint8_t daysThisMonth;

    daysThisMonth = getNumberOfDaysInThisMonth(time);

    time->date++;

    if (time->date > daysThisMonth)
    {
        time->date = 1;
        time->month++;

        if (time->month > DECEMBER)
        {
            time->month = JANUARY;
            time->year++;
        }
    }
}

// called once per second to update the time
void incrementTime(RTCCFORM *time)
{
    time->tenth_second++;    

    if (time->tenth_second < 10)
    {
        return;
    }

    time->tenth_second = 0;
    time->second++;

    if (time->second < 60)
    {
        return;
    }

    time->second = 0;
    time->minute++;

    if (time->minute < 60)
    {
        return;
    }

    time->minute = 0;
    time->hour++;

    if (time->hour >= 24)
    {
        time->hour = 0;

        incrementDate(time);
    }
}
