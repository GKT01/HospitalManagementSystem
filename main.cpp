#include <iostream>
#include <string>

#include <fstream>
#include <sstream> // string stream, allows us to get one line

#include "patient.h"
#include "doctor.h"

#define LIM 100
#define SELECT_DOCTOR 111
#define NO_SELECT -22

using namespace std;

Patient addPatient(int *patientID, fstream &patient_file, fstream &doctor_file);
Doctor addDoctor(int *doctorID, fstream &doctor_file);

void showMyPatients(istream &patient_file, istream &doctor_file);

int listDoctor(int selectDoctor, istream &doctor_file);
int RemoveDoctor(Doctor doctors[], int lim, fstream &doctor_file);

int main(int argc, char** argv){
    fstream patient_file("patient.txt", ios::app);
    fstream doctor_file("doctor.txt", ios::app);
    
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
    // add see my doctor cauze im the patient
    cin >> index;

    switch (index){
    case 1:
        // Add if loop that if array of patient array is more than 100 it stopts adding until
        // program restarts (for txt file)
        patientArray[patientID] = addPatient(&patientID, patient_file, doctor_file);
        break;
    case 2:
        showMyPatients(patient_file, doctor_file);
        break;
    case 3:
        while( index2 != 3){
        cout << "To add a doctor enter 1, To remove a doctor enter 2, To list doctors enter 3"
        << ",To exit enter 4" << endl;
        cin >> index2;
        if(index2 == 1){
            // Add if loop that if array of doctor array is more than 100 it stopts adding until
            // program restarts (for txt file)
            doctorArray[doctorID] = addDoctor(&doctorID, doctor_file);
        }
        else if(index == 2){
            int doctor_id_to_remove = RemoveDoctor(doctorArray, LIM, doctor_file);
            doctorArray[doctor_id_to_remove] = Doctor();
        }
        else if(index == 3){
            listDoctor(NO_SELECT, doctor_file);
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

int RemoveDoctor(Doctor doctors[], int lim, fstream &doctor_file){ // change this
    int doctorID{-1};

    listDoctor(NO_SELECT, doctor_file);

    cout << "Please make sure the Doctor has no patient, "
    << "Enter DoctorID to remove the Doctor: ";
    cin >> doctorID;

    return doctorID;
}

void showMyPatients(istream &patient_file, istream &doctor_file){
    string doctorName;
    string doctorNameCheck;

    string firstLineCheck;
    string extractLine;

    int doctorIDCheck;
    int patientResponsibleID;
    
    int doctorFound;

    cout << "Hello Mr./Mrs. : ";
    getline(cin >> ws, doctorName);

    doctor_file.seekg(0, ios::beg); // gets file to beginning to red g = read
    while(getline(doctor_file, firstLineCheck)){ // loops for every line
        if(firstLineCheck.empty())
            cout << "No Doctor Found!" << endl; // any doctor at all
        else{
            stringstream ss(firstLineCheck);
            getline(ss, extractLine, ',');
            doctorNameCheck = extractLine; // we extract doctors name

            while(getline(ss, extractLine, ',')){ // we extracts doctors id, loops for one line because i take only one line
                stringstream(extractLine) >> doctorIDCheck;
                if(doctorName == doctorNameCheck){ 
                    doctorFound = doctorIDCheck;
                    break;
                }
            }
        }
    }
    
    patient_file.seekg(0, ios::beg); // gets file to beginning to read g = read
    cout << "Here is your Patients: " << endl;
    while(getline(patient_file, firstLineCheck)){ // loop for all patients
        stringstream ss(firstLineCheck);
        while(getline(ss, extractLine, ',')){ // we extracts patientsResponsibleDoctor id
        stringstream(extractLine) >> patientResponsibleID;
        if(doctorFound == patientResponsibleID){ // check for doctors id and patientResponsibleID
                cout << firstLineCheck << endl;
            }
        }
    }
}

int listDoctor(int selectDoctor, istream &doctor_file){
    int i = -1;
    string getLineCheck;

    doctor_file.seekg(0, ios::beg); // gets file to beginning
    while(getline(doctor_file, getLineCheck)){
        if(getLineCheck.empty()){
            cout << "Sorry no Doctor Available right now.." << endl;
        }
        else{
            cout << getLineCheck;
        }
    }
    

    if (selectDoctor == SELECT_DOCTOR){
        cout << "Please enter the Doctor ID that you want to visit: ";
        cin >> i;

        return i;
    }
    return NO_SELECT;
}

Doctor addDoctor(int *doctorID, fstream &doctor_file){
    string name;
    int age;
    string specialty;

    cout << "Enter doctor name: ";
    getline(cin >> ws, name);

    cout << "Enter doctor specialty: ";
    getline(cin >> ws, specialty);

    cout << "Enter doctor age: ";
    cin >> age;
    
    doctor_file.seekp(0, ios::end); // gets file to ending for write p = write
    doctor_file << "\n" << name << ", " << specialty << ", " << age << ", " 
    << (++(*doctorID)) << endl;

    Doctor doctor(name, specialty, age , (*doctorID));
    return doctor;
}

Patient addPatient(int *patientID, fstream &patient_file, fstream &doctor_file){
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
    selectedDoctorID = listDoctor(SELECT_DOCTOR, doctor_file);

    patient_file.seekp(0, ios::end); // puts file to the end for writing p = write
    patient_file << "\n" << name << ", " << illness << ", " << age << ", " << (++(*patientID)) << ", "
    << selectedDoctorID << endl;

    Patient patient(name, illness, age , (*patientID), selectedDoctorID);
    return patient;
}