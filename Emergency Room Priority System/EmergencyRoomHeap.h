#ifndef EMERGENCYROOMHEAP_H
#define EMERGENCYROOMHEAP_H

#include "Patient.h"
#include <vector>

class EmergencyRoomHeap
{
private:
    std::vector<Patient> heap;
    void heapifyUp(int childIndex);
    void heapifyDown(int parentIndex);
    void printPatientData(Patient patient) const;

public:
    EmergencyRoomHeap(/* args */);
    void insert(Patient newPatient);
    void treatNext();
    void viewNext() const;
    void updateSeverity(int patientId, int newSeverity);
    void displayAllPatients() const;
    ~EmergencyRoomHeap();
};


#endif