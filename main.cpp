#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;

// Convert string to lowercase
string toLowerCase(const string& str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

// Read file and build map
map<string, int> buildFrequencyMap(const string& filename) {
    map<string, int> freqMap;
    ifstream inFile(filename);
    string item;

    while (getline(inFile, item)) {
        freqMap[toLowerCase(item)]++;
    }

    inFile.close();
    return freqMap;
}

// Print items and counts
void printAllItems(const map<string, int>& freqMap) {
    cout << "\n--- All Items and Frequencies ---\n";
    for (const auto& pair : freqMap) {
        cout << left << setw(15) << pair.first << pair.second << endl;
    }
}

// Print histogram
void printHistogram(const map<string, int>& freqMap) {
    cout << "\n--- Histogram ---\n";
    for (const auto& pair : freqMap) {
        cout << left << setw(15) << pair.first;
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << endl;
    }
}

// Save to file
void writeFrequencyFile(const map<string, int>& freqMap, const string& outputFile) {
    ofstream outFile(outputFile);
    for (const auto& pair : freqMap) {
        outFile << pair.first << " " << pair.second << endl;
    }
    outFile.close();
}

int main() {
    const string inputFile = "CS210_Project_Three_Input_File.txt";
    const string outputFile = "frequency.dat";

    map<string, int> freqMap = buildFrequencyMap(inputFile);
    writeFrequencyFile(freqMap, outputFile);

    int choice;
    string item;

    do {
        cout << "\n==== Corner Grocer Menu ====\n";
        cout << "1. Search for an item\n";
        cout << "2. Display all items and frequencies\n";
        cout << "3. Display histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item name: ";
                cin >> ws;
                getline(cin, item);
                item = toLowerCase(item);
                if (freqMap.count(item)) {
                    cout << item << " appears " << freqMap[item] << " times.\n";
                } else {
                    cout << item << " not found.\n";
                }
                break;

            case 2:
                printAllItems(freqMap);
                break;

            case 3:
                printHistogram(freqMap);
                break;

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}