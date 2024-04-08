﻿#include <iostream>
#include <iomanip>
#include <string.h>
//#include <stdio.h>


using namespace std;




struct S{
        string* names;
        float** costs;
    };




void initialize(S& debts, int n) {
    debts.names = new string[n];
    debts.costs = new float*[n];


    cout << "Enter the names of participants " << endl;

    for (int i = 0; i < n; ++i) {
        cin >> debts.names[i];
        debts.costs[i] = new float[n];
        for (int j = 0; j < n; j++) {
            debts.costs[i][j] = 0.00;
        }
    }

}




void show_debts(S& debts, int size){

    cout << setw(20) << left << "";


    for (int i=0; i<size; i++){

        cout << setw(20) << left << "C " + debts.names[i];
    }


    cout << endl;
    

    for (int i=0; i<size; i++){

        cout << setw(20) << left << "D " + debts.names[i];

        for (int j=0; j<size; j++){
            cout << setw(20) << left << fixed << setprecision(2) << debts.costs[i][j];
        }

        cout << endl;
    }

}




S add_expense(S& debts, int n, float amount, string name) {

    int name_index = -1;


    for (int i = 0; i < n; ++i) {
        if (name == debts.names[i]) {
            name_index = i;
            break;
        }
    }

    if (name_index==-1){
        cout << "Participant not found. Names of participants: ";
        for (int i = 0; i < n; ++i) {
            cout << debts.names[i] << " ";
        }
        cout << endl;
        return debts;
    }

    //only if splited equally

    float cost = amount / n;

    for (int i = 0; i < n; ++i) {

        if (i!=name_index){
            debts.costs[i][name_index] += cost;

        }

    }
    return debts;

}





int main(){

    int n;
    cout << "Enter the number of participants: ";
    cin >> n;

    S debts; 
    initialize(debts, n); 



    //ADD EXPENSE
    string name;
    float amount;

    cout << "Who paid? " << endl;
    cin >> name;

    cout << "Amount: " << endl;
    cin >> amount;

    add_expense(debts, n, amount, name);

    



    show_debts(debts, n);



    











    // freeing memory
    for (int i = 0; i < n; ++i) {
        delete[] debts.costs[i];
    }
    delete[] debts.costs;
    delete[] debts.names;

    return 0;

}