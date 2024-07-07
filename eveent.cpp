#include "eveent.h"
#include "event_helpers.cpp"
#include "display.cpp"

void createEvent(string path, Event &eventData)
{
    fstream file = OpenFile(path, false);

    string format = formatedContent(eventData);

    file.write(format.data(), format.size());
    if (file.bad())
    {
        cerr << "Error writing to file: " << path << endl;
    }
    else
    {
        cout << "event is aded\n";
    }
    file.close();
}
// Function to determine the maximum number of events to read

void searchEvent(index *eventIndex, string path, int maxEvents, int id)
{
    if (eventIndex == nullptr)
    {
        cerr << "Error: Event index array is not available." << endl;
        return;
    }
    if (id < 1 || id > eventIndex[maxEvents - 1].ID)
    {
        cerr << "Error: Invalid event ID." << endl;
        return;
    }
    int index = searchIndex(eventIndex, maxEvents, id);
    if (!index)
    {
        cerr << "sometin wrong in the arry" << endl;
    }
    fstream file = OpenFile(path, false);

    if (!file.seekg(eventIndex[index].big, ios::beg))
    {
        cerr << "Error seeking to start position in file." << endl;
        file.close();
        return;
    }

    vector<vector<string>> content;

    content = lineToVactor(file, eventIndex, index);

    // vector<vector<string>>
    vector<string> header = {"ID", "Name", "Date", "Details"};

    displayTable(header, content);

    file.close();
}

void deleteEvent(index *eventIndex, string path, int maxEvents, int id)
{
    if (eventIndex == nullptr)
    {
        cerr << "Error: Event index array is not available." << endl;
        return;
    }
    if (id < 1 || id > eventIndex[maxEvents - 1].ID)
    {
        cerr << "Error: Invalid event ID." << endl;
        return;
    }

    int index = searchIndex(eventIndex, maxEvents, id);
    fstream file = OpenFile(path, false);

    int startPos = eventIndex[index].big + 1;
    int endPos = eventIndex[index].end + 1;
    file.seekg(0, ios::end);
    long int fileSize = file.tellg();
    file.seekg(0, ios::beg);
    if (startPos >= fileSize || endPos > fileSize)
    {
        cerr << "Error: Positions are outside file bounds." << endl;
        file.close();
        return;
    }

    char bufferBefore[startPos];
    char bufferAfter[fileSize - endPos];

    long int bytesRead = 0;
    while (bytesRead < startPos)
    {
        int readSize = min(static_cast<long int>(sizeof(bufferBefore)), startPos - bytesRead);
        file.read(bufferBefore, readSize);
        bytesRead += file.gcount();
    }
    file.seekg(endPos, ios::beg);
    bytesRead = 0;
    while (bytesRead < fileSize - endPos)
    {
        int readSize = min(static_cast<long int>(sizeof(bufferAfter)), fileSize - endPos - bytesRead);
        file.read(bufferAfter, readSize);
        bytesRead += file.gcount();
    }

    file.close();
    file.open(path, ios::binary | ios::out | ios::trunc);
    if (!file.is_open())
    {
        cerr << "Error opening file for writing: " << path << endl;
        return;
    }
    file.write(bufferBefore, startPos);
    file.write(bufferAfter, fileSize - endPos);
    file.close();

    cout << "Content erased successfully from " << startPos << " to " << endPos << endl;
}

void editFileAtPosition(index *eventIndex, string path, int &maxEvents, Event &newData, int id)
{
    string newContent = formatedContent(newData);
    int index = searchIndex(eventIndex, maxEvents, id);

    long int editPos = eventIndex[index].big;
    long int endtPos = eventIndex[index].end;
    // show the data to be edited
    searchEvent(eventIndex, path, maxEvents, id);

    if (editPos < 0 || newContent.empty())
    {
        cerr << "Error: Invalid edit position or empty data." << endl;
        return;
    }

    // Open the file in read-write binary mode
    fstream filename = OpenFile(path, true);

    // Get the file size
    filename.seekg(0, ios::end);
    long int fileSize = filename.tellg();
    filename.seekg(0, ios::beg);

    // Check if edit position is within file bounds
    if (editPos >= fileSize)
    {
        cerr << "Error: Edit position is outside file bounds." << endl;
        filename.close();
        return;
    }

    // Create temporary buffers (adjust buffer size based on your needs)
    char bufferBefore[editPos];
    char bufferAfter[fileSize - endtPos + 1];

    // Read content before the edit position
    long int bytesRead = 0;
    while (bytesRead < editPos)
    {
        long int tempSize = min(static_cast<long int>(sizeof(bufferBefore)), editPos - bytesRead);
        int readSize = tempSize;
        filename.read(bufferBefore, readSize);
        bytesRead += filename.gcount();
    }

    bytesRead = 0;
    if (editPos + newContent.size() < fileSize)
    {
        while (bytesRead < fileSize - endtPos - newContent.size())
        {
            long int tempSize = min(static_cast<long int>(sizeof(bufferAfter)), static_cast<long int>(fileSize - endtPos + 1 - newContent.size() - bytesRead));
            int readSize = tempSize;
            filename.read(bufferAfter, readSize);
            bytesRead += filename.gcount();
        }
    }
    // Seek to the edit position (overwrite existing data)
    filename.seekp(editPos, ios::beg);
    filename.write(newContent.data(), newContent.size());
    filename.seekg(editPos + newContent.size(), ios::beg);
    bytesRead = 0;
    while (bytesRead < fileSize - endtPos - newContent.size())
    {
        long int tempSize = min(static_cast<long int>(sizeof(bufferAfter)), static_cast<long int>(fileSize - endtPos + 1 - newContent.size() - bytesRead));
        int readSize = tempSize;
        filename.write(bufferAfter, readSize);
        bytesRead += filename.gcount();
    }

    // Close the file
    filename.close();

    cout << "File edited successfully at position " << editPos << endl;
}
void viewEvent(string path)
{
    fstream file = OpenFile(path, true);
    vector<vector<string>> content = lineToVactor(file);
    vector<string> header = {"ID", "Name", "Date", "Details"};
    displayTable(header, content);
    file.close();
}

/// Desplay functions to desplay
