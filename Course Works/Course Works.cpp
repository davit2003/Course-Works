#include <iostream>
#include <vector>
#include "EmployeeManager.h"
using namespace std;

int main()
{
    EmployeeManager employeeManger;
    int option;
    bool exit = false;

    cout << "-------------- Hello HR -------------- \n";
    
    while (!exit) {
        cout << "---------- Choose an option ---------- \n";
        cout << "(1) Create Employee \n";
        cout << "(2) Edit Employee \n";
        cout << "(3) Fire Employee \n";
        cout << "(4) Print Employee List \n";
        cout << "(5) Exit \n";
        
        option = 0;
        cin >> option;
        
        cout << "\n--------------------------------------\n";

        std::unique_ptr<RequestResponse<void*>> resp;
        switch (option) {
        case 1: 
            resp = employeeManger.Create();
            if (resp.get()->errorCode == ErrorCode::InvalidRequest)
                cout << resp.get()->errorMessage << endl;
            break;
        case 2: 
            resp = employeeManger.Edit();
            if (resp.get()->errorCode == ErrorCode::InvalidRequest)
                cout << resp.get()->errorMessage << endl;
            break;
        case 3: 
            resp = employeeManger.Remove();
            if (resp.get()->errorCode == ErrorCode::InvalidRequest)
                cout << resp.get()->errorMessage << endl;
            break;
        case 4: 
            employeeManger.PrintList();
            break;
        case 5: exit = true; break;
        default: std::cout << "Invlaid Option\n"; exit = true; break;
        }

        cout << "\n--------------------------------------\n";
    }
}