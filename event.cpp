#include "event.h"
#include "display.cpp"

using namespace std;

void createEvent(fstream &file, string path, Event &eventData)
{
    file.open(path, ios::out | ios::app | ios ::binary);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << path << std::endl;
    }

    file.write((char *)&eventData, sizeof(eventData));

    if (file.bad())
    {
        std::cerr << "Error writing to file: " << path << std::endl;
    }
    else
    {
        cout << "event is aded\n";
    }
}
void veiwEvent(fstream &file, string path, Event &eventData)
{
    file.open(path, ios::in);
    if (!file.is_open())
    {
        cerr << "Error opening file" << path << endl;
    };
    while (!file.eof())
    {

        file.read((char *)&eventData, sizeof(eventData));
    }

    file.close();

    if (file.bad())
    {
        std::cerr << "Error writing to file: " << path << std::endl;
        file.close();
    }
}
int searchEvent(fstream &file, string path, Event &eventData)
{
    bool found = false;
    int id;

    file.open(path, ios::in | ios::binary);
    if (!file.is_open())
    {
        cerr << "error opening file tray aben leter" << endl;
        return 0;
    }
    cout << "Enter the id of the event you went to serch";
    cin >> id;
    if (file.bad())
    {
        cerr << "error reading the file" << endl;
        return 0;
    };

    while (!file.eof())
    {
        file.read((char *)&eventData, sizeof(eventData));
        if (eventData.Id == id)
        {
            cout << eventData.Id << endl;
            cout << eventData.name << endl;
            cout << eventData.date << endl;
            cout << eventData.detaile << endl;
            found = true;
        }
    };
    if (found == false)
    {
        cout << "event not found" << endl;
    };
    return 1;
}
void deleteEvent(fstream &file, string path, Event &eventData)
{
    //
    file.open(file)
}
void editEvent(fstream &file)
{
    // edit event besd on the id of the event
    // read the event and implemet a mated to update the event and re- wrightt the edited verstion
}