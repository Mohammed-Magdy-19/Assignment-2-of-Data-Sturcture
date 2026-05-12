#ifndef PATIENT_H
#define PATIENT_H

#include <string>

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

#endif