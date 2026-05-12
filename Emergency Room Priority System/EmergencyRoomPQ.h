#ifndef EMERGENCYROOMPQ_H
#define EMERGENCYROOMPQ_H

#include "Patient.h"
#include <queue>

class EmergencyRoomPQ
{
private:
    std::priority_queue<Patient> patients;
    void printPatientData(Patient patient) const;
public:
    EmergencyRoomPQ(/* args */);
    void insert(Patient newPatient);
    void treatNext();
    void viewNext() const;
    void updateSeverity(int patientId, int newSeverity);
    void displayAllPatients() const;
    ~EmergencyRoomPQ();
};


#endif