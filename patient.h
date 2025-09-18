#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

using namespace std;

class Patient {
    public:
        Patient();
        Patient(std::string name, string illness, int age, int id);
    protected:
        string patientName;
        string patientIllness;
        int patientAge;
        int patientID;
};

#endif