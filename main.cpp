#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
//#include <stdio.h>


using namespace std;

const int MAX_PARTICIPANTS = 5;
const int MIN_PARTICIPANTS = 5;




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




void showDebtsTable(S& debts, int size){

    cout <<  endl << "TABLE OF DEBTS (C=Creditor D=Debtor)" << endl;

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




void showBalance(S& debts, int size){

    int counter = 0;
    bool is_debt = false;

    cout <<  endl << "BALANCE: " << endl;

    for (int i=0; i<size; i++){

        for (int j=i+1; j<size; j++){

            if (debts.costs[i][j] == debts.costs[j][i]){
                continue;
            }

            else if (debts.costs[i][j] > debts.costs[j][i]){
                is_debt = true;
                cout << debts.names[i] << " owes " << debts.names[j] << " " << setprecision(2) << abs (debts.costs[i][j] - debts.costs[j][i]) << " $" << endl;
            }

            else if (debts.costs[i][j] < debts.costs[j][i]){
                is_debt = true; 
                cout << debts.names[j] << " owes " << debts.names[i] << " " << setprecision(2) << abs (debts.costs[i][j] - debts.costs[j][i])  << " $" << endl;
            }
                
        }

    }

    if (is_debt == false){
        cout << "No debts among the participants." << endl;
    }
}




S addExpense(S& debts, int n, float amount, string name) {

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

    // works only if splited equally

    float cost = amount / n;

    for (int i = 0; i < n; ++i) {

        if (i!=name_index){
            debts.costs[i][name_index] += cost;
        }

    }
    return debts;

}




void newExpense(S& debts, int n){

    string name;
    float amount;
    char answer;
    int name_index = -1;

    while(true){

        cout << "Do you want to add an expense? y/n ";
        cin >> answer;
        
        if (tolower(answer) ==  'n' ){
            break;
        }
        else if(tolower(answer) == 'y' ){
            cout << "Who paid? " << endl;
            cin >> name;
        
            cout << "Amount: " << endl;
            cin >> amount;

            addExpense(debts, n, amount, name);

        }
        else{
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
            continue;
        }
        

    }


}




int main(){

    // group initialization

    int n;

    cout << "Enter the number of participants (number from 2 to 5): ";
    cin >> n;

    if (n > MAX_PARTICIPANTS) {
        cout << "Number of participants exceeds the maximum allowed limit." << endl;
        return 1; 
    }
    else if (n < MIN_PARTICIPANTS){
        cout << "Number of participants must be at least 2." << endl;
        return 1;
    }

    S debts; 



    initialize(debts, n); 

    newExpense(debts, n);

    showDebtsTable(debts, n);

    showBalance(debts, n);



    // free memory
    for (int i = 0; i < n; ++i) {
        delete[] debts.costs[i];
    }
    delete[] debts.costs;
    delete[] debts.names;

    return 0;

}