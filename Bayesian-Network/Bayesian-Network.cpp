#include<iostream>

#define DOORS_TOTAL 3
#define TRIES_TOTAL 10000

int correctData = 0;
int incorrectData = 0;

using namespace std;

//This function sets the environment randomly
void questionnaire(bool *doors) {

cout << "Setting the doors" << endl;
for(int i = 0; i < DOORS_TOTAL; i++) {
doors[i] = false;
}
doors[rand()%DOORS_TOTAL] = true;
}

//main function
int main() {

bool doors[DOORS_TOTAL];
double finalProbability;
questionnaire(doors);

//Runs until finite number of tries
for(int i = 0; i < TRIES_TOTAL; i++) {
//Door is randomly picked

int selectedAns = rand()%DOORS_TOTAL;
cout << "Contestant has selected door number: "<< selectedAns << endl;

int eliminated_door;

//Elimination of one false answer
for(int j = 0; j < DOORS_TOTAL; j++) {
if(doors[j] == false && j != selectedAns) {
eliminated_door = j;
break;
}
}
cout << "The host has eliminated door number: " << eliminated_door << endl;

//New door selection
for(int j=0; j < DOORS_TOTAL; j++) {
if(j != selectedAns && j != eliminated_door) {
selectedAns = j;
break;
}
}
cout << "Contestant had changed his answer to door number: " << selectedAns << endl;

if(doors[selectedAns] == true) {
correctData++;
cout << "Result: Behind door number " << selectedAns << " is the prize!" << endl;
} else {
incorrectData++;
cout << "Result: Behind door number " << selectedAns << " is nothing!" << endl;
}
cout << endl << "_____**_____" << endl;
questionnaire(doors);

}

finalProbability = (float)correctData/(float)TRIES_TOTAL;

cout << endl << "*** Final Data after " << TRIES_TOTAL << " epochs ***" << endl;

cout << "Number of Correct : " << correctData << endl;
cout << "Number of Incorrect : " << incorrectData << endl;
cout << endl;

cout << "If changed, the probability ratio : " << 100*finalProbability << "%" << endl;
cout << "If unchanged, the probability ratio : " << 100*(1-finalProbability) << "%" << endl;

return 0;
}