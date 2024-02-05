#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_PUPILS = 30;

struct Pupil {
    string name;
    int weightFirstDay;
    int weightLastDay;
};

void saveToFile(const Pupil pupils[], const char* filename, int count) {
    ofstream outFile(filename);

    for (int i = 0; i < count; ++i) {
        outFile << pupils[i].name << " " << pupils[i].weightFirstDay << " " << pupils[i].weightLastDay << endl;
    }

    outFile.close();
}

void readFromFile(Pupil pupils[], const char* filename, int& pupilCount) {
    ifstream inFile(filename);

    pupilCount = 0;

    while (inFile >> pupils[pupilCount].name >> pupils[pupilCount].weightFirstDay >> pupils[pupilCount].weightLastDay) {
        pupilCount++;
    }

    inFile.close();
}

int main() {
    Pupil pupils[MAX_PUPILS];
    int pupilCount = 0;  // Track the number of pupils

    readFromFile(pupils, "pupil_records.txt", pupilCount);

    int choice;

    do {
        cout << "\nMenu:\n1. Add student information for the first day\n2. Recall student information for the last day\n3. Display information\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Add student information for the first day
                if (pupilCount < MAX_PUPILS) {
                    for (int i = pupilCount; i < MAX_PUPILS; ++i) {
                        retry:
                        cout << "Enter Name of pupil " << i + 1 << " on the first day of term:" << endl;
                        cin >> pupils[i].name;

                        // Check for repeated names
                        for (int j = 0; j < i; ++j) {
                            if (pupils[i].name == pupils[j].name) {
                                cout << "Error: Name already entered. Please enter a unique name." << endl;
                                goto retry;  // Retry name entry if it's repeated
                            }
                        }

                        // Validate and enter weight
                        do {
                            cout << "Enter Weight of pupil " << i + 1 << " on the first day of term (between 25 and 60):" << endl;
                            cin >> pupils[i].weightFirstDay;

                            if (pupils[i].weightFirstDay < 25 || pupils[i].weightFirstDay > 60) {
                                cout << "Error: Weight should be between 25 and 60. Please enter a valid weight." << endl;
                            }
                        } while (pupils[i].weightFirstDay < 25 || pupils[i].weightFirstDay > 60);

                        pupilCount++;

                        char addAnother;
                        if (pupilCount < MAX_PUPILS) {
                            cout << "Do you want to enter another pupil? (Y/N): ";
                            cin >> addAnother;

                            if (addAnother != 'Y' && addAnother != 'y') {
                                break;  // Exit the loop if the user doesn't want to enter another pupil
                            }
                        }
                    }
                } else {
                    cout << "Class is full. Cannot add more pupils." << endl;
                }

                saveToFile(pupils, "pupil_records.txt", pupilCount);
                break;

            case 2:
                // Recall student information for the last day
                cout << "\nRecall on the last day of term:" << endl;
                for (int i = 0; i < pupilCount; ++i) {
                    cout << "Recall pupil " << pupils[i].name << ":" << endl;
                    cin >> pupils[i].weightLastDay;
                }
                saveToFile(pupils, "pupil_records.txt", pupilCount);
                break;

            case 3:
                // Display fall and rise for each pupil
                cout << "\nStudent Information:" << endl;
                for (int i = 0; i < pupilCount; ++i) {
                    int weightDifference = pupils[i].weightLastDay - pupils[i].weightFirstDay;
                    cout << pupils[i].name << ": ";
                    cout << "|First Day Weight: " << pupils[i].weightFirstDay << " kilograms, ";
                    cout << "|Last Day Weight: " << pupils[i].weightLastDay << " kilograms, ";

                    if (weightDifference > 2.5) {
                        cout << "|Rise of " << weightDifference << " kilograms (significant)" << endl;
                    } else if (weightDifference < -2.5) {
                        cout << "|Fall of " << -weightDifference << " kilograms (significant)" << endl;
                    } else {
                        cout << "|No significant change" << endl;
                    }
                }
                break;

            case 0:
                // Exit the program
                cout << "Exiting the program.\n";
                break;

            default:
                // Invalid choice
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 0);

    return 0;
}

