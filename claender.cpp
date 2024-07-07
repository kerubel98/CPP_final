#include "claender.h"
using namespace std;

int getNumberOfDayes(int year, int monthIndex)
{
    return (monthIndex == 2) ? (((year % 100 != 0 && year % 400 == 0) || year % 4 == 0) ? 29 : 28) : ((monthIndex % 2 != 0) ^ (monthIndex < 8)) ? 30
                                                                                                                                                : 31;
}
string ethMonthNames(int month)
{
    string ethiopian_month[13] = {
        "Mes", "Tik", "Hid", "Tah", "Tir", "Yek", "Meg", "Miy", "Gin", "Sen", "Ham", "Neh", "Pau-Mes"};
    return ethiopian_month[month - 1];
}
string eroMonthNames(int month)
{
    string gregorian_month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    return gregorian_month[month - 1];
}

int getDayIndex(int month, int year, int day)
{ // if month is less than 3 reduce year by 1 tomohiko shakamato algorithem
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    if (month < 3)
        year -= 1;

    return ((year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7);
}

int weekDayes(int monthIndex, int year, int weekNo, int dayIndex, int flag)
{
    month current;
    current.monthIndex = monthIndex;
    current.year = year;
    current.startDayIndex = getDayIndex(monthIndex, year, 1);
    current.numberOfDayes = getNumberOfDayes(current.year, current.monthIndex);
    current.lastDayIndex = getDayIndex(monthIndex, year, current.numberOfDayes);
    int wekk = (current.numberOfDayes + current.startDayIndex) / 7 + 1;

    if (dayIndex < current.startDayIndex && weekNo == 1)
    {
        return 0;
    }
    else if (dayIndex > current.lastDayIndex && weekNo >= wekk)
    {
        return 0;
    }
    else
    {
        return (7 * (weekNo - 1)) + dayIndex - (current.startDayIndex - 1);
    }
}

void clanderDisply(int clnFlag, string numStr, int day)
{
    if (clnFlag == 1)
    {
        if (day == 0)
        {

            cout << " |" << numStr << setw(5);
        }
        else
        {

            cout << "|" << numStr << setw(6);
        }
    }
    if (clnFlag == 0)
    {
        if (day == 0)
        {

            cout << " |" << setw(6) << numStr;
        }
        else
        {

            cout << "|" << setw(7) << numStr;
        }
    }
}
void displyWeekNames(int year, int month, int weekNo, int day)
{
    vector<int> x = to_ethiopian(year, month, ((7 * (weekNo - 1)) + day - (getDayIndex(month, year, 1) - 1)));
    int ethy = x[0];
    int ethm = x[2];
    cout << setw(5) << year << "\t" << eroMonthNames(month) << "\t\t" << ethy << "-" << ethy + 1 << "\t\t" << ethMonthNames(ethm) << "  " << ethMonthNames(ethm + 1) << endl;
    cout << endl;
    cout << " |------------------------------------------------------|" << endl;
    cout << " |Sun\t|" << "Mon\t|" << "Tue\t|" << "Wed\t|" << "Thu\t|" << "Fri\t|" << "Sat\t|" << endl;
    cout << " |------------------------------------------------------|" << endl;
}
void printinerdates(int year, int day, int weekNo, int mont, int clnFlag)
{
    stringstream ss, ss1;
    vector<int> x = to_ethiopian(year, mont, ((7 * (weekNo - 1)) + day - (getDayIndex(mont, year, 1) - 1)));
    int eth = x[1];

    if (weekDayes(mont, year, weekNo, day, clnFlag) == 0)
    {
        ss1 << "  ";
        ss << "  ";
    }
    else
    {
        ss1 << eth;
        ss << weekDayes(mont, year, weekNo, day, clnFlag);
    }

    string numStr = ss.str();
    string numStr1 = ss1.str();
    if (numStr.length() == 1)
    {
        numStr = "0" + numStr;
    }
    if (numStr1.length() == 1)
    {
        numStr1 = "0" + numStr1;
    }
    if (clnFlag == 0)
    {
        clanderDisply(clnFlag, numStr, day);
    }
    else if (clnFlag == 1)
    {
        clanderDisply(clnFlag, numStr1, day);
    }
}
void displydayNO(int year, int mont, int weekNo, int dayIndex)
{

    displyWeekNames(year, mont, weekNo, dayIndex);
    for (int j = 1; j < 6; j++)
    {
        for (int i = 0; i < 7; i++)
        {

            printinerdates(year, i, j, mont, 0);
            if (i == 6)
            {
                cout << "|" << endl;
            }
        }

        for (int i = 0; i < 7; i++)
        {

            printinerdates(year, i, j, mont, 1);
            if (i == 6)
            {
                cout << "|" << endl;
            }
        }
        cout << " |------------------------------------------------------|" << endl;
    }
    cout << endl;
}

void runCalender(int year)
{

    for (int i = 1; i < 13; i++)
    {
        displydayNO(year, i, 1, 1);
    };
}