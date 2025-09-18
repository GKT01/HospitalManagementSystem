#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

using namespace std;

class Patient {
    public:
        Patient();
        Patient(string name, string illness, int age, int id,int responsibleDoctorID);
    //protected:
        int patientResponsibleID;
        string patientName;
        string patientIllness;
        int patientAge;
        int patientID;
};

#endif