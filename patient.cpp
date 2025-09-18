#include "patient.h"

Patient::Patient(){
    patientName = "Unknown";
    patientIllness = "Lupus"; // Doctor House Joke
    patientAge = 0;
    patientID = -1;
}

Patient::Patient(string name, string illness, int age, int id,int responsibleDoctorID){
    patientName = name;
    patientIllness = illness;
    patientAge = age;
    patientID = id;
    patientResponsibleID = responsibleDoctorID;
}