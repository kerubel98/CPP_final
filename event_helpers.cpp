#include "eveent.h"

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
    {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}
int searchIndex(index *eventIndex, int &maxEvents, int id)
{
    int index = 0;
    bool found = false;
    for (int i = 0; i < maxEvents; i++)
    {
        if (eventIndex[i].ID == id && eventIndex[i].isDeleted == false)
        {
            index = i;
            found = true;
            break;
        }
        // else if (eventIndex[i].isDeleted == false)
        // {
        //     throw runtime_error("Event is delited ");
        // }
    }
    if (!found)
    {
        throw runtime_error("Event you Loking is not found");
    }
    return index;
}

fstream OpenFile(const string &path, bool binaryFlag)
{

    ios_base::openmode mode = ios::in | ios::out | ios::app;
    if (binaryFlag)
    {
        mode |= ios::binary;
    }

    fstream file(path, mode);
    if (!file.is_open())
    {
        throw runtime_error("Failed to open event file.");
    }

    return file;
}
string formatedContent(Event &eventData)
{
    stringstream formattedData;
    formattedData << "{" << endl;
    formattedData << "ID: " << eventData.ID << "," << endl;
    formattedData << "Name: " << eventData.name << "," << endl;
    formattedData << "Date: " << eventData.date << "," << endl;
    formattedData << "Details: " << eventData.details << "," << endl;
    formattedData << "}" << endl;
    return formattedData.str();
}
int getMaxEvents(const string &path)
{
    fstream file = OpenFile(path, false);
    int numLines = 0;
    string line;
    while (getline(file, line, '}'))
    {
        if (!line.empty())
        {
            numLines++;
        }
    }
    file.close();
    numLines -= 1;
    return numLines;
}
int parseEventLine(const string &line)
{
    int ID;
    istringstream iss(line);
    stringstream ss;
    string label, value;

    while (getline(iss, label, ':'))
    {
        // getline(iss, label, ':');
        if (label == "{\nID")
        {
            getline(iss, value, ',');
            ID = stoi(trim(value));
            break;
        }
    }

    return ID;
}

index *readEventsToArray(const string &path, int maxEvents)
{
    index *eventIndex = new index[maxEvents];
    fstream file = OpenFile(path, false);
    if (!file)
    {
        delete[] eventIndex;
        return nullptr;
    }
    string line;
    int i = 0;
    char ch;
    if (maxEvents > 0)
    {
        while (getline(file, line, '}') && i < maxEvents)
        {
            if (line.empty())
            {
                continue;
            }
            int index = parseEventLine(line);
            if (index != 0)
            {
                int end = file.tellg();
                eventIndex[i].ID = index;
                eventIndex[i].end = end + 1;
                eventIndex[i].big = eventIndex[i].end - (line.length() + 2);
                file.get(ch);
                i++;
                continue;
            };
        }
    }
    else
    {
        cerr << "No Event" << path << endl;
        return nullptr;
    }
    file.close();
    return eventIndex;
}
vector<vector<string>> lineToVactor(fstream &file, index *eventIndex, int index)
{
    string line;
    vector<string> ID;
    vector<string> Name;
    vector<string> Date;
    vector<string> Details;
    vector<vector<string>> content;

    while ((file.tellg() < eventIndex[index].end) && getline(file, line))
    {

        if (line.empty() || line.front() == '{' || line.back() == '}')
        {
            continue;
        }

        stringstream ss(line);
        string key, value;
        vector<string> row;
        // Extract key-value pairs using getline with delimiters
        while (getline(ss, key, ':') && getline(ss, value, ','))
        {
            if (key == "ID")
            {
                ID.push_back(value);
            }
            else if (key == "Name")
            {
                Name.push_back(value);
            }
            else if (key == "Date")
            {
                Date.push_back(value);
            }
            else if (key == "Details")
            {
                Details.push_back(value);
            }
            else
            {
                continue;
            }
        };

        // content.push_back(row);
    }
    for (int i = 0; i < ID.size(); i++)
    {
        vector<string> row = {ID[i], Name[i], Date[i], Details[i]};

        content.push_back(row);
    }
    return content;
}
void freeEventArray(Event *events)
{
    if (events != nullptr)
    {
        delete[] events;
    }
}

vector<vector<string>> lineToVactor(fstream &file)
{
    string line;
    vector<string> ID;
    vector<string> Name;
    vector<string> Date;
    vector<string> Details;
    vector<vector<string>> content;

    while (getline(file, line))
    {

        if (line.empty() || line.front() == '{' || line.back() == '}')
        {
            continue;
        }

        stringstream ss(line);
        string key, value;
        vector<string> row;
        // Extract key-value pairs using getline with delimiters
        while (getline(ss, key, ':') && getline(ss, value, ','))
        {
            if (key == "ID")
            {
                ID.push_back(value);
            }
            else if (key == "Name")
            {
                Name.push_back(value);
            }
            else if (key == "Date")
            {
                Date.push_back(value);
            }
            else if (key == "Details")
            {
                Details.push_back(value);
            }
            else
            {
                continue;
            }
        };

        // content.push_back(row);
    }
    for (int i = 0; i < ID.size(); i++)
    {
        vector<string> row = {ID[i], Name[i], Date[i], Details[i]};

        content.push_back(row);
    }
    return content;
}