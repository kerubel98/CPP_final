#include "manu.h"
#include "eveent.h"

int choise;
string path = "/home/cppProject/projuctfolder/eventData.txt";
int maxEvents = getMaxEvents(path);
Event eventData;
index *eventIndex = readEventsToArray(path, maxEvents);
string lineRead()
{
    char firstChar = cin.peek(); // Peek at the first character

    if (cin.peek() == char_traits<char>::eof())
    {
        cerr << "Empty input." << endl;
        return "";
    }
    string line;
    getline(cin, line).putback(firstChar);
    cin.ignore();
    return line;
}
int mainu()
{

    int id;

    do
    {

        cout << "1 for printing calender" << endl;
        cout << "2 for Adding Events" << endl;
        cout << "3 for Viewing Events" << endl;
        cout << "4 for Searching Event" << endl;
        cout << "5 Deleteing Event" << endl;
        cout << "6 Editing Event" << endl;
        cin >> choise;
        switch (choise)
        {
        case 1:
            cout << "enter calender year" << endl;
            int year;
            cin >> year;
            runCalender(year);
            break;
        case 2:

            cout << "enter event Id" << endl;
            cin >> eventData.ID;
            cin.ignore();
            cout << "Enter eventname: ";
            eventData.name = lineRead();
            cout << "enetr event date: ";
            eventData.date = lineRead();
            cout << "eneter event detaile: ";
            eventData.details = lineRead();
            createEvent(path, eventData);
            break;
        case 3:
            viewEvent(path);
            break;
        case 4:
            cout << "Enter the id of the Event you went to search" << endl;
            int ids;
            cin >> ids;
            searchEvent(eventIndex, path, maxEvents, ids);
            break;
        case 5:
            cout << "Enter the id of the Event you went to delet" << endl;
            int idd;
            cin >> idd;
            deleteEvent(eventIndex, path, maxEvents, idd);
            break;
        case 6:
            cout << "Enter the id of the Event you went to Edit" << endl;
            int ide;
            cin >> ide;
            cout << "enter event Id" << endl;
            cin >> eventData.ID;
            cin.ignore();
            cout << "Enter New eventname: ";
            eventData.name = lineRead();
            cout << "enetr new event date: ";
            eventData.date = lineRead();
            cout << "eneter new event detaile: ";
            eventData.details = lineRead();
            editFileAtPosition(eventIndex, path, maxEvents, eventData, ide);
            break;

        default:
            break;
        }
    } while (choise);

    return 0;
}