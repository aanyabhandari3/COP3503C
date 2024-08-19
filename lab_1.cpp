#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    string title;
    string columnHeader1;
    string columnHeader2;
    vector<string>dataStrings;
    vector<int>dataIntegers;
    int count = 0;

    int string_size = dataStrings.size();

    cout << "Enter a title for the data:" << endl;
    getline(cin, title);
    cout << "You entered: " << title << endl;

    cout << "Enter the column 1 header:" << endl;
    getline(cin, columnHeader1);
    cout << "You entered: " << columnHeader1 << endl;

    cout << "Enter the column 2 header:" << endl;
    getline(cin, columnHeader2);
    cout << "You entered: " << columnHeader2 << endl;

    while (true) {
        cout << "Enter a data point (-1 to stop input):" << endl;
        string data;
        getline(cin, data);
        std::size_t pos = data.find(',');
        if (data == "-1") {
            cout << endl;
            break;
        }
        if (data.find(',')== std::string::npos) {
            cout << "Error: No comma in string." << endl;
            continue;
        }
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ',') {
                count++;
            }
        }
        if (data.find(',', pos+1) != std::string::npos) {
            cout << "Error: Too many commas in input." << endl;
            count = 0;
            continue;
        }
        try {
            string dataString = data.substr(0, data.find(','));
            int dataInt = stoi(data.substr(data.find(',') + 1));


            // Add data string and integer to arrays
            dataStrings.push_back(dataString);
            dataIntegers.push_back(dataInt);

            cout << "Data string: " << dataString << endl;
            cout << "Data integer: " << dataInt << endl;

        } catch (const invalid_argument& e) {
            cout << "Error: Comma not followed by an integer." << endl;
            continue;
        }
    }
    cout << right<< setw(33)<<title<<endl;
    cout << left << setw(20) << columnHeader1 << "|" << setw(23) << right << columnHeader2 << endl;
    cout <<"--------------------------------------------"<<endl;

    for (size_t i = 0; i < dataStrings.size(); ++i) {
        cout  << left << setw(20) << dataStrings[i] << "|" << setw(23) << right << dataIntegers[i] << endl;
    }
    cout << endl;
    for (int i = 0; i <= dataStrings.size(); i++) {
        cout << left << setfill(' ') << setw(dataStrings.size());
        cout << setw(20) << right << dataStrings[i] << " " <<string(dataIntegers[i], '*') << endl;
    }

    return 0;
    }