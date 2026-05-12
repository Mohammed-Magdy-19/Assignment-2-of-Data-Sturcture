#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "EmergencyRoomHeap.cpp"
#include "EmergencyRoomPQ.cpp"

using namespace std;

void runSTLComparison(const vector<Patient>& testPatients) {
    
    priority_queue<Patient> stlQueue;

    cout << "\n--- STL priority_queue Comparison ---" << endl;
    for (const auto& p : testPatients) {
        stlQueue.push(p);
    }

    if (!stlQueue.empty()) {
        cout << "Top patient in STL Queue: " << stlQueue.top().name
            << " (Severity: " << stlQueue.top().severity << ")" << endl;
    }
}

int main() {
    
    EmergencyRoomHeap manualHeap;

    
    vector<Patient> patientsData = {
        {"Ahmed", 8, 10}, {"Sara", 5, 12}, {"John", 10, 15}, {"Maria", 3, 18},
        {"Omar", 10, 14}, {"Laila", 7, 20}, {"Ziad", 2, 22}, {"Nour", 9, 25},
        {"Hady", 5, 28}, {"Mona", 8, 30}, {"Fady", 1, 35}, {"Dina", 6, 40},
        {"Tarek", 4, 45}, {"Yassmin", 7, 50}, {"Khaled", 9, 55}, {"Reem", 10, 60},
        {"Samy", 2, 65}, {"Heba", 5, 70}, {"Mostafa", 3, 75}, {"Arwa", 8, 80}
    };

    cout << " 1: Inserting 20 patients into Manual Heap..." << endl;
    for (const auto& p : patientsData) {
        manualHeap.insert(p);
    }

    
    cout << " 2: Displaying All Patients (Level Order):";
    manualHeap.displayAllPatients();

    
    cout << "\n 3: Checking Next Patient for Treatment:";
    manualHeap.viewNext();

    cout << "\n 4: Updating Severity for Patient ID 2 to 10 (Highest Priority)..." << endl;
    manualHeap.updateSeverity(2, 10);
    manualHeap.viewNext();

    
    cout << "\n 5: Treating the next patient in line:";
    manualHeap.treatNext();


    runSTLComparison(patientsData);

    
    return 0;
}