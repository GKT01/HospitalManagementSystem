#include "doctor.h"

Doctor::Doctor(){
    doctorName = "None";
    doctorSpecialty = "None";
    doctorAge = 0;
    doctorID = -1;
}

Doctor::Doctor(string name, string specialty, int age, int id){
    doctorName = name;
    doctorSpecialty = specialty;
    doctorAge = age;
    doctorID = id;
}