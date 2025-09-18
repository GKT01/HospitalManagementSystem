#include <iostream>
#include <string>

#include "patient.h"
#include "doctor.h"

#define LIM 100
#define SELECT_DOCTOR 111
#define NO_SELECT -22

using namespace std;

Patient addPatient(int *patientID, Doctor doctors[], int lim);
Doctor addDoctor(int *doctorID);

void showMyPatients(Doctor doctors[], Patient patients[], int lim);

int listDoctor(Doctor doctors[], int lim, int selectDoctor);
int RemoveDoctor(Doctor doctors[], int lim);

int main(int argc, char** argv){
    int index{};
    int index2{};

    int patientID = 0, doctorID = 0;

    Patient patientArray[LIM];
    Doctor doctorArray[LIM];

    Doctor doctor1;
    doctorArray[0] = doctor1;

    while (index != 4){ 

    cout << "Welcome To Hospital, Enter 1 if you are a patient, 2 if you are a doctor,"
    << "3 if you are Admin, 4 to Quit" 
    << endl;
    cin >> index;

    switch (index){
    case 1:
        patientArray[patientID] = addPatient(&patientID, doctorArray, LIM);
        break;
    case 2:
        showMyPatients(doctorArray, patientArray, LIM);
        break;
    case 3:
        while( index2 != 3){
        cout << "To add a doctor enter 1, To remove a doctor enter 2, To list doctors enter 3"
        << ",To exit enter 4" << endl;
        cin >> index2;
        if(index2 == 1){
            doctorArray[doctorID] = addDoctor(&doctorID);
        }
        else if(index == 2){
            int doctor_id_to_remove = RemoveDoctor(doctorArray, LIM);
            doctorArray[doctor_id_to_remove] = Doctor();
        }
        else if(index == 3){
            listDoctor(doctorArray, LIM, NO_SELECT);
        }
        else if (index == 4){
            cout << "Quitting Admin options.." << endl;
            return 0;
        }
        else {
            cout << "Invalid input please try again.." << endl;
        }}

        break;
    case 4:
        cout << "Quitting.."<< endl;
        return 0;
    default:
        cout << "Invalid input please try again.." << endl; 
        break;
    }
    }


    return 0;
}

int RemoveDoctor(Doctor doctors[], int lim){
    int doctorID{-1};

    listDoctor(doctors, LIM, NO_SELECT);

    cout << "Enter DoctorID to remove the Doctor: ";
    cin >> doctorID;

    return doctorID;
}

void showMyPatients(Doctor doctors[], Patient patients[], int lim){
    string doctorName;
    int doctorFound{-1};

    cout << "Hello Mr./Mrs. : ";
    getline(cin >> ws, doctorName);

    for(int i = 0; i < LIM; i++){
        if(doctors[i].doctorName == doctorName){
            doctorFound = doctors[i].doctorID;
            break;
        }
    }
    
    cout << "Here is your Patients: ";
    for(int j = 0; j < LIM; j++){
        if(patients[j].patientResponsibleID == doctorFound)
            cout << "Patient Name: "<<patients[j].patientName
            << ", Illness: " << patients[j].patientIllness
            << endl;
    }
}

int listDoctor(Doctor doctors[], int lim, int selectDoctor){
    int i = -1;
    for(int i = 0; i < LIM; i++){
        if(doctors[i].doctorName != "None")
            cout << "Name: "<<doctors[i].doctorName
            << ",Specialty: " << doctors[i].doctorSpecialty
            << ",Age: " << doctors[i].doctorAge
            << ",Id: " << doctors[i].doctorID
            << endl;
    }

    if (selectDoctor == SELECT_DOCTOR){
        cout << "Please enter the Doctor ID that you want to visit: ";
        cin >> i;

        return i;
    }
    return NO_SELECT;
}

Doctor addDoctor(int *doctorID){
    string name;
    int age;
    string specialty;

    cout << "Enter doctor name: ";
    getline(cin >> ws, name);

    cout << "Enter doctor specialty: ";
    getline(cin >> ws, specialty);

    cout << "Enter doctor age: ";
    cin >> age;

    Doctor doctor(name, specialty, age , ++(*doctorID));
    return doctor;
}

Patient addPatient(int *patientID, Doctor doctors[], int lim){
    string name;
    int age;
    string illness;
    
    int selectedDoctorID = -1;

    cout << "Enter patient name: ";
    getline(cin >> ws, name);

    cout << "Enter patient illness: ";
    getline(cin >> ws, illness);

    cout << "Enter patient age: ";
    cin >> age;

    cout << "Please choose your doctor depending on your illness: " << endl;
    selectedDoctorID = listDoctor(doctors, lim, SELECT_DOCTOR);

    Patient patient(name, illness, age , ++(*patientID), selectedDoctorID);
    return patient;
}