#ifndef CALENDER_H
#define CALENDER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "ethiopianCalendnder.h"
using namespace std;

struct month
{
    int monthIndex;
    int startDayIndex;
    int lastDayIndex;
    int numberOfDayes;
    int year;
};
int getNumberOfDayes(int, int);
string ethMonthNames(int);
string eroMonthNames(int);
int getDayIndex(int, int, int);
int weekDayes(int, int, int, int, int);
void clanderDisply(int, string, int);
void displyWeekNames(int, int, int, int);
void printinerdates(int, int, int, int, int);
void displydayNO(int, int, int, int);
void runCalender(int);

#endif