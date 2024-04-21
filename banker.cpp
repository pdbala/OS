#include <iostream>
#include <vector>

using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

int available[MAX_RESOURCES];
int max_alloc[MAX_PROCESSES][MAX_RESOURCES];
int current_alloc[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES];

vector<int> safe_sequence;

bool isSafe(int processes, int resources) {
    // Initialize finish array to false
    for (int i = 0; i < processes; ++i) {
        finish[i] = false;
    }

    // Initialize need matrix
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            need[i][j] = max_alloc[i][j] - current_alloc[i][j];
        }
    }

    int work[MAX_RESOURCES];
    for (int i = 0; i < resources; ++i) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; ++i) {
            if (!finish[i]) {
                bool canBeProcessed = true;
                for (int j = 0; j < resources; ++j) {
                    if (need[i][j] > work[j]) {
                        canBeProcessed = false;
                        break;
                    }
                }

                if (canBeProcessed) {
                    for (int j = 0; j < resources; ++j) {
                        work[j] += current_alloc[i][j];
                    }
                    safe_sequence.push_back(i);
                    finish[i] = true;
                    ++count;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // No safe sequence exists
        }
    }
    return true; // Safe sequence found
}

int main() {
    int processes, resources;

    cout << "Enter the number of processes: ";
    cin >> processes;

    cout << "Enter the number of resources: ";
    cin >> resources;

    cout << "Enter the available instances of each resource:\n";
    for (int i = 0; i < resources; ++i) {
        cin >> available[i];
    }

    cout << "Enter the maximum demand of each process:\n";
    for (int i = 0; i < processes; ++i) {
        cout << "For process " << i << ": ";
        for (int j = 0; j < resources; ++j) {
            cin >> max_alloc[i][j];
        }
    }

    cout << "Enter the current allocation of each process:\n";
    for (int i = 0; i < processes; ++i) {
        cout << "For process " << i << ": ";
        for (int j = 0; j < resources; ++j) {
            cin >> current_alloc[i][j];
        }
    }

    if (isSafe(processes, resources)) {
        cout << "System is in a safe state.\n";
        cout << "Safe sequence is: ";
        for (int i = 0; i < processes; ++i) {
            cout << safe_sequence[i] << " ";
        }
        cout << endl;
    } else {
        cout << "System is in an unsafe state.\n";
    }

    return 0;
}
//0 1 0 2 0 0 3 0 2 2 1 1 0 0 2 7 5 3 3 2 2 9 0 2 4 2 2 5 3 3
