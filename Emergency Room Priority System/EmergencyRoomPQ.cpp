#include "EmergencyRoomPQ.h"
#include <iostream>

using namespace std;

void EmergencyRoomPQ::printPatientData(Patient patient) const
{
    cout << "id: " << patient.id << endl;
    cout << "Name: " << patient.name << endl;
    cout << "Arrival time: " << patient.arrivalTime << endl;
    cout << "severity: " << patient.severity << endl;
    cout << endl;
}

EmergencyRoomPQ::EmergencyRoomPQ()
{
}

void EmergencyRoomPQ::insert(Patient newPatient)
{
    patients.push(newPatient);
}

void EmergencyRoomPQ::treatNext()
{
    if (patients.empty())
    {
        cout << "The Emergency room is empty\n";
        return;
    }

    cout << "\n========================================================\n";
    cout << "=================The patient that treated===============\n";
    printPatientData(patients.top());
    cout << "========================================================\n";

    patients.pop();
}

void EmergencyRoomPQ::viewNext() const
{
    if (patients.empty())
    {
        cout << "The Emergency room is empty\n";
        return;
    }

    cout << "\n========================================================\n";
    cout << "==============The patient that next treated==============\n";
    printPatientData(patients.top());
    cout << "========================================================\n";
}

void EmergencyRoomPQ::updateSeverity(int patientId, int newSeverity)
{
    priority_queue<Patient> temp;

    while(!patients.empty())
    {
        Patient p = patients.top();
        patients.pop();

        if(p.id == patientId)
            p.severity = newSeverity;

        temp.push(p);
    }

    patients = temp;
}

void EmergencyRoomPQ::displayAllPatients() const
{
    if (patients.empty())
    {
        cout << "The Emergency room is empty\n";
        return;
    }

    cout << "\n========================================================\n";
    cout << "========================Patients========================\n";

    priority_queue<Patient> temp = patients;

    while (!temp.empty())
    {
        printPatientData(temp.top());
        temp.pop();
    }

    cout << "========================================================\n";
}

EmergencyRoomPQ::~EmergencyRoomPQ()
{
}
