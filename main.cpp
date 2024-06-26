﻿#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>


using namespace std;


const int MIN_PARTICIPANTS = 2;
const int MAX_PARTICIPANTS = 5;




struct S{
        int n; //number of participants
        string* names; // names of participants
        float** costs; // costs matrix
    };




void groupInitialize(S& debts) {

    while (true) {
        cout << "Enter the number of participants (number from 2 to 5): ";
        
        if (!(cin >> debts.n)) {
            cout << "Invalid number of participants. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else if (debts.n > MAX_PARTICIPANTS) {
            cout << "Number of participants exceeds the maximum allowed limit." << endl;
        }else if (debts.n < MIN_PARTICIPANTS) {
            cout << "Number of participants must be at least 2." << endl;
        }else {
            break; 
        }
    }

    debts.names = new string[debts.n];
    debts.costs = new float*[debts.n];

    cout << "Enter the names of participants " << endl;

    for (int i = 0; i < debts.n; i++) {
        cin >> debts.names[i];
        debts.costs[i] = new float[debts.n];

        for (int j = 0; j < debts.n; j++) {
            debts.costs[i][j] = 0.00;
        }
    }
}




void showDebtsTable(S& debts){

    cout <<  endl << "TABLE OF DEBTS (C=Creditor D=Debtor)" << endl;
    cout << setw(20) << left << "";

    for (int i=0; i<debts.n; i++){
        cout << setw(20) << left << "C " + debts.names[i];
    }

    cout << endl;

    for (int i=0; i<debts.n; i++){

        cout << setw(20) << left << "D " + debts.names[i];

        for (int j=0; j<debts.n; j++){
            cout << setw(20) << left << fixed << setprecision(2) << debts.costs[i][j];
        }

        cout << endl;
    }

}




void showBalance(S& debts){

    int counter = 0;
    bool is_debt = false;

    cout <<  endl << "BALANCE: " << endl;

    for (int i=0; i<debts.n; i++){

        for (int j=i+1; j<debts.n; j++){

            if (debts.costs[i][j] == debts.costs[j][i]){
                continue;
            } else if (debts.costs[i][j] > debts.costs[j][i]){
                is_debt = true;
                cout << debts.names[i] << " owes " << debts.names[j] << " " << setprecision(2) << abs (debts.costs[i][j] - debts.costs[j][i]) << " $" << endl;
            } else if (debts.costs[i][j] < debts.costs[j][i]){
                is_debt = true; 
                cout << debts.names[j] << " owes " << debts.names[i] << " " << setprecision(2) << abs (debts.costs[i][j] - debts.costs[j][i])  << " $" << endl;
            }
                
        }

    }

    if (is_debt == false){
        cout << "No debts among the participants." << endl;
    }
}




S addExpense(S& debts){

    string name;
    float amount;
    char answer;
    int name_index = -1;

    while(true){

        cout << "DO YOU WANT TO ADD AN EXPENSE? (Y/N) ";
        cin >> answer;
        
        if (tolower(answer) ==  'n' ){
            break;
        } else if(tolower(answer) == 'y' ){

            int name_index = -1;

            cout << "ADDING NEW EXPENSE " << endl;
            cout << "Who paid? " << endl;
            cin >> name;

            for (int i = 0; i < debts.n; i++) {

                if (name == debts.names[i]) {
                    name_index = i;
                    break;
                }
            }

            if (name_index==-1){
                cout << "EXPENSE NOT ADDED. Participant not found. Names of participants: ";
        
                for (int i = 0; i < debts.n; i++) {
                    cout << debts.names[i] << " ";
                }

                cout << endl << "Try again." << endl;
            }else{
                cout << "Amount: " << endl;

                if (!(cin >> amount)) {
                    cout << "EXPENSE NOT ADDED Invalid amount. Amount should be a digit. Try again." << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                }

                float cost = amount / debts.n;

                for (int i = 0; i < debts.n; i++) {

                    if (i!=name_index){
                        debts.costs[i][name_index] += cost;
                    }   
                }
            }
        }else{
            cout << "INVALID INPUT. Please enter 'Y' or 'N'." << endl;
            continue;
        }
    }

    return debts;
}




int main(){


    S new_group; 

    groupInitialize(new_group); 

    addExpense(new_group);

    showDebtsTable(new_group);

    showBalance(new_group);


    // memory
    delete[] new_group.costs;
    delete[] new_group.names;


    return 0;
}