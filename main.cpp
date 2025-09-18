#include <iostream>
#include <string>

#include "patient.h"
#include "doctor.h"

using namespace std;

int main(int argc, char** argv){
    int index{};
    int index2{};

    Patient patient1;
    Doctor doctor1;

    while (index != 4){ 

    cout << "Welcome To Hospital, Enter 1 if you are a patient, 2 if you are a doctor,"
    << "3 if you are Admin, 4 to Quit" 
    << endl;
    cin >> index;

    switch (index){
    case 1:
        //AddPatient();
        break;
    case 2:
        //DoctorList();
        break;
    case 3:
        cout << "To add a doctor enter 1, To remove a doctor enter 2, To exit enter 3" << endl;
        cin >> index2;
        while( index != 3){
        if(index2 == 1){
            //AddDoctor();
        }
        else if(index == 2){
           // RemoveDoctor();
        }
        else if (index == 3){
            cout << "Quitting Admin options.." << endl;
            return 0;
        }
        else {
            cout << "Invalid input please try again.." << endl;
        }
        }

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