#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

void displayTable(const vector<string> &header, const vector<vector<string>> &content)
{

    vector<int> maxColWidths(header.size());
    fill(maxColWidths.begin(), maxColWidths.end(), 0);
    for (size_t i = 0; i < header.size(); ++i)
    {
        maxColWidths[i] = max(static_cast<long int>(maxColWidths[i]), static_cast<long int>(header[i].length()));
        for (const vector<string> &row : content)
        {

            if (i < row.size())
            {
                maxColWidths[i] = max(static_cast<long int>(maxColWidths[i]), static_cast<long int>(row[i].length()));
            }
        };
    };
    // Print the header row with separators
    cout << "+";
    for (int width : maxColWidths)
    {
        cout << setfill('-') << setw(width + 3) << "+";
    }
    cout << endl;
    cout << "| ";
    for (size_t i = 0; i < header.size(); ++i)
    {
        cout << right << setfill(' ') << setw(maxColWidths[i]) << header[i] << " | ";
    }
    cout << endl;

    // Print each content row with separators (modified separator line)
    cout << "+";
    for (int width : maxColWidths)
    {
        cout << setfill('-') << setw(width + 3) << "+";
    }
    cout << endl;

    for (const vector<string> &row : content)
    {
        cout << "| ";
        for (size_t i = 0; i < row.size(); ++i)
        {

            if (i < row.size() && row.size() != 0)
            {
                cout << right << setfill(' ') << setw(maxColWidths[i]) << row[i] << " | ";
            }
            else
            {
                cout << right << setw(maxColWidths[i]) << " " << " | "; // Handle empty cells (optional)
            }
        }
        cout << endl;
    }

    cout << "+";
    for (int width : maxColWidths)
    {
        cout << setfill('-') << setw(width + 3) << "+";
    }
    cout << endl;
}