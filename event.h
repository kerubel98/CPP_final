#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

struct Event
{
    int Id;
    char name[30];
    char date[15];
    char detaile[100];

    void getName()
    {
        int i = 0;

        cin.ignore();
        while (i < 29 || cin.peek() != '\n')
        {
            cin.get(name[i]);

            if (name[i] == '\n')
            {
                name[i] = '\0';
                break;
            }
            i++;
        }

        if (i == 29 && cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Warning: Name input exceeded maximum length. Truncated." << endl;
        }
    }
    void getdetaile()
    {
        int i = 0;
        cin.ignore();
        while (i < 99 || cin.peek() != '\n')
        {
            cin.get(detaile[i]);

            if (detaile[i] == '\n')
            {
                detaile[i] = '\0';
                break;
            }
            i++;
        };
        if (i == 99 && cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Warning: Name input exceeded maximum length. Truncated." << endl;
        }
    }
};

void createEvent(fstream &file, string path, Event &eventdetaill);
void veiwEvent(fstream &file, string path, Event &eventdetaill);
int searchEvent(fstream &file, string path, Event &eventdetaill);
void deleteEvent(fstream &file);
void editEvent(fstream &file);

#endif