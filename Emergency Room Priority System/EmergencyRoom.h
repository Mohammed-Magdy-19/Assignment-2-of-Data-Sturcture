#ifndef EMERGENCYROOM_H
#define EMERGENCYROOM_H

#include <string>
#include <vector>

struct Patient
{
    int id;
    std::string name;
    int severity;
    int arrivalTime;

    Patient(std::string name, int severity, int arrivalTime)
    {
        this->name = name;
        this->severity = severity;
        this->arrivalTime = arrivalTime;

        static int count = 0;
        this->id = ++count; // increasing count then assign it into this->id 
    }

    bool operator<(const Patient& other) const {
        if(severity == other.severity){
            return arrivalTime > other.arrivalTime;
        }
        return severity < other.severity;
    }

    bool operator>(const Patient& other) const {
        if(severity == other.severity){
            return arrivalTime < other.arrivalTime;
        }
        return severity > other.severity;
    }
};



class EmergencyRoom
{
private:
    std::vector<Patient> heap;
    void heapifyUp(int childIndex);
    void heapifyDown(int parentIndex);
    void printPatientData(Patient patient) const;

public:
    EmergencyRoom(/* args */);
    void insert(Patient newPatient);
    void treatNext();
    void viewNext() const;
    void updateSeverity(int patientId, int newSeverity);
    void displayAllPatients() const;
    ~EmergencyRoom();
};


#endif