#include <iostream>
#include <vector>
using namespace std;

vector<int> to_ethiopian(int year, int month, int date)
{

    int tahissas;
    int ethiopian_date;
    int ethiopian_month;
    int gregorian_months[] = {0, 31, 28, 31, 30, 31, 30,
                              31, 31, 30, 31, 30, 31};

    int ethiopian_months[] = {0, 30, 30, 30, 30, 30, 30, 30,
                              30, 30, 5, 30, 30, 30, 30};

    // if gregorian leap year, February has 29 days.
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        gregorian_months[2] = 29;
    }

    int ethiopian_year = year - 8;
    int new_year_day = (ethiopian_year / 100) - (ethiopian_year / 400) - 4;

    // if ethiopian leap year pagumain has 6 days
    if (ethiopian_year % 4 == 3)
    {
        ethiopian_months[10] = 6;
    }
    else
    {
        ethiopian_months[10] = 5;
    }

    // calculate number of days up to that date
    int until = 0;
    for (int i = 1; i < month; i++)
    {

        until += gregorian_months[i];
    }
    until += date;

    // update tahissas(december) to match january 1st
    if (ethiopian_year % 4 == 0)

    {
        tahissas = 25;
    }
    else
    {
        tahissas = 24;
    }

    // take into account the  change
    if (year < 1772)
    {
        ethiopian_months[1] = 0;
        ethiopian_months[2] = tahissas;
    }

    else if (until <= 277 &&
             year == 1772)
    {
        ethiopian_months[1] = 0;
        ethiopian_months[2] = tahissas;
    }

    else
    {
        tahissas = new_year_day - 3;
        ethiopian_months[1] = tahissas;
    }

    // calculate month and date incremently
    int m = 0;
    for (m = 1; m < sizeof(ethiopian_months) / sizeof(ethiopian_months[0]); m++)
    {

        if (until <= ethiopian_months[m])
        {

            if (m == 1 || ethiopian_months[m] == 0)
            {

                ethiopian_date = until + (30 - tahissas);
            }
            else
            {

                ethiopian_date = until;
            };
            break;
        }
        else
        {
            until -= ethiopian_months[m];
        }
    }
    // if m > 4, we're already on next Ethiopian year
    if (m > 10)
    {

        ethiopian_year += 1;
    }

    // Ethiopian months ordered according to Gregorian
    int order[] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 2, 3, 4};
    ethiopian_month = order[m];
    return {ethiopian_year, ethiopian_date, ethiopian_month};
    // ethiopian_month, ethiopian_date
}
