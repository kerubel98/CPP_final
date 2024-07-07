#ifndef EVEENT_H
#define EVEENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;
struct Event
{
    int ID;
    string name;
    string date;
    string details;
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
            cin.get(details[i]);

            if (details[i] == '\n')
            {
                details[i] = '\0';
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

struct index
{
    int ID;
    int big;
    int end;
    bool isDeleted = false;
};

string trim(const string &str);
int searchIndex(index *eventIndex, int &maxEvents, int id);
fstream OpenFile(const string &path, bool binaryFlag);
string formatedContent(Event &eventData);
void createEvent(string path, Event &eventData);
int getMaxEvents(const string &path);
int parseEventLine(const string &line);
index *readEventsToArray(const string &path, int maxEvents);
void searchEvent(index *eventIndex, string path, int maxEvents, int id);
void deleteEvent(index *eventIndex, string path, int maxEvents, int id);
void editFileAtPosition(index *eventIndex, string path, int &maxEvents, Event &newData, int id);
void viewEvent(string path);
void freeEventArray(Event *events);
void displayTable(const vector<string> &header, const vector<vector<string>> &content);

#endif
