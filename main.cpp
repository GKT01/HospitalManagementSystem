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

Patient addPatient(int *patientID, fstream &patient_file, fstream &doctor_file); // Adds Patient
Doctor addDoctor(int *doctorID, fstream &doctor_file); // Adds Doctor

void showMyPatients(istream &patient_file, istream &doctor_file); // Shows Patients of a Doctor
void showMyDoctor(istream &patient_file, istream &doctor_file); // Show Doctor of a Patient

void fixIndexNumbers(istream &patient_file, istream &doctor_file, int* patientID, int* doctorID);
// Aligns the Index Numbers

int listDoctor(int selectDoctor, istream &doctor_file); // Lists All the Doctors

int main(int argc, char** argv){
    fstream patient_file("patient.txt", ios::in | ios::out | ios::app);
    fstream doctor_file("doctor.txt", ios::in | ios::out | ios::app);

    int index{};
    int index2{};

    int patientArrayIndex_obj{};
    int doctorArrayIndex_obj{};

    int patientID{};
    int doctorID{};

    Patient patientArray[LIM];
    Doctor doctorArray[LIM];

    Doctor doctor1;
    doctorArray[0] = doctor1;

    fixIndexNumbers(patient_file,doctor_file, &patientID, &doctorID);

    while (index != 5){ 

    cout << "Welcome To Hospital, Enter 1 if you want to register as patient, 2 if you are a doctor\n"
    << "3 if you are Admin, 4 if you are a already a patient, 5 to Quit" 
    << endl;
    // add see my doctor cauze im the patient
    cin >> index;

    switch (index){
    case 1:
        if(patientArrayIndex_obj < LIM){
            patientArray[patientArrayIndex_obj] = addPatient(&patientID, patient_file, doctor_file);
            patientArrayIndex_obj++;
            // Adds Patient
        }
        else{
            cout << "You are out of adding limit. Please restart the program." << endl;
        }
        break;

    case 2:
        showMyPatients(patient_file, doctor_file);
        //Shows Patient
        break;
    case 3:
        //Admin Commands
        while( index2 != 3){
        cout << "To add a doctor enter 1, To list doctors enter 2"
        << ",To exit enter 3" << endl;
        cin >> index2;
        if(index2 == 1){
               if(doctorArrayIndex_obj < LIM){
                    doctorArray[doctorArrayIndex_obj] = addDoctor(&doctorID, doctor_file);
                    doctorArrayIndex_obj++;
                    // Adds Doctor
                }
                else{
                    cout << "You are out of adding limit. Please restart the program." << endl;
                }
        }
        else if(index2 == 2){
            // Lists Doctors
            listDoctor(NO_SELECT, doctor_file);
        }
        else if (index2 == 3){
            cout << "Quitting Admin options.." << endl;
            break;
        }
        else {
            cout << "Invalid input please try again.." << endl;
        }}

        break;
    case 4:
        // Show Patients Doctor
        showMyDoctor(patient_file, doctor_file);
        break;
    case 5:
        cout << "Quitting.."<< endl;
        return 0;
    default:
        cout << "Invalid input please try again.." << endl; 
        break;
    }
    }

    patient_file.close(); // Closes file
    doctor_file.close(); // Closes file

    return 0;
}

void fixIndexNumbers(istream &patient_file, istream &doctor_file, int* patientID, int* doctorID){
    string check;

    patient_file.clear();
    patient_file.seekg(0, ios::beg);
    while(getline(patient_file, check)){ // for patient
        if (!check.empty())
            (*patientID)++;
    }

    doctor_file.clear();
    doctor_file.seekg(0, ios::beg);
    while(getline(doctor_file, check)){ // for doctor
        if (!check.empty())
            (*doctorID)++;
    }
}

void showMyDoctor(istream &patient_file, istream &doctor_file){
    string name;
    string lineCheck;

    string getPatientName;

    string getID1;
    string getID2;

    int responsibleDoctorID_int = -1;
    int myDoctorsID_int = -1;

    
    cout << "Enter your name: ";
    getline(cin >> ws, name);

    patient_file.clear();
    doctor_file.clear();

    patient_file.seekg(0, ios::beg);
    doctor_file.seekg(0, ios::beg);

    while(getline(patient_file, lineCheck)){ 
        stringstream getLines(lineCheck);
        getline(getLines, getPatientName, ','); // Gets Patients Name
        if(name == getPatientName){
            while(getline(getLines, getID1, ',')){
                stringstream ss(getID1); // we have doctors id from patient now
                int temp;
                if(ss >> temp)
                    responsibleDoctorID_int = temp;
            }
            break;
        }
    }

    while(getline(doctor_file, lineCheck)){
        stringstream getLines(lineCheck);
        while(getline(getLines, getID2, ',')){
            stringstream ss(getID2);
            int temp;
            if(ss >> temp)
                myDoctorsID_int = temp; // Get Doctor ID
            }
        if(myDoctorsID_int == responsibleDoctorID_int){ // doctor id and patients responsible id equals now
            cout << "Here is information about your doctor(s): " << endl;
            cout << lineCheck << endl;
            break;
        }
    }
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

    
    patient_file.clear();
    doctor_file.clear();

    doctor_file.seekg(0, ios::beg); // gets file to beginning to red g = read
    while(getline(doctor_file, firstLineCheck)){ // loops for every line
        if(firstLineCheck.empty())
            cout << "No Doctor Found!" << endl; // any doctor at all
        else{
            stringstream ss(firstLineCheck);
            getline(ss, extractLine, ',');
            doctorNameCheck = extractLine; // we extract doctors name

            while(getline(ss, extractLine, ',')){ // we extracts doctors id, loops for one line because i take only one line
                stringstream ss(extractLine);
                int temp;   // string to int
                if(ss >> temp)
                    doctorIDCheck = temp; // Get Doctor ID
            }
            if(doctorName == doctorNameCheck){ 
                    doctorFound = doctorIDCheck;
                    break;
                }
        }
    }
    
    patient_file.seekg(0, ios::beg); // gets file to beginning to read g = read
    cout << "Here is your Patients: " << endl;
    while(getline(patient_file, firstLineCheck)){ // loop for all patients
        stringstream ss(firstLineCheck);
        while(getline(ss, extractLine, ',')){ // we extracts patientsResponsibleDoctor id
            stringstream ss(extractLine);
            int temp;
            if(ss >> temp)
                patientResponsibleID = temp; // Get Patient ID
            }
        if(doctorFound == patientResponsibleID){ // check for doctors id and patientResponsibleID
            cout << firstLineCheck << endl;
        }
    }
}

int listDoctor(int selectDoctor, istream &doctor_file){
    int i = -1;
    string getLineCheck;

    doctor_file.clear();
    doctor_file.seekg(0, ios::beg); // gets file to beginning
    while(getline(doctor_file, getLineCheck)){
        if(getLineCheck.empty()){
            cout << "Sorry no Doctor Available right now.." << endl;
        }
        else{
            cout << getLineCheck << endl;
        }
    }
    

    if (selectDoctor == SELECT_DOCTOR){ // Checks for Adding Doctor's ID to a Patient's Information
        cout << "Please enter the Doctor ID that you want to visit: " << endl;
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
    
    doctor_file.clear();
    doctor_file.seekp(0, ios::end); // gets file to ending for write p = write
    doctor_file << "\n"<< name << ", " << specialty << ", " << age << "," 
    << (++(*doctorID));

    Doctor doctor(name, specialty, age , (*doctorID));
    return doctor; // Returns Doctor Object to Doctor Array
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

    patient_file.clear();
    patient_file.seekp(0, ios::end); // puts file to the end for writing p = write

    patient_file << "\n" <<name << ", " << illness << ", " << age << ", " << (++(*patientID)) << ","
    << selectedDoctorID;

    Patient patient(name, illness, age , (*patientID), selectedDoctorID);
    return patient; // Returns Patient Object to Patient Array
}