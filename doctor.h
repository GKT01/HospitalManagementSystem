#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>

using namespace std;

class Doctor
{
    public:
        Doctor();
        Doctor(string name, string specialty, int age, int id);
        
    protected:
        string doctorName;
        string doctorSpecialty;
        int doctorAge;
        int doctorID;
};



#endif