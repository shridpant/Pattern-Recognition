// C++ code for Risk Classifier
#include<bits/stdc++.h>
using namespace std;

int main(){
    //Print Statements regarding the risk classifier
	cout<<"-- RISK CLASSIFIER --"<<endl;
	cout<<"Action 1 :  Loan Accepted"<<endl;
	cout<<"Action 2 :  Loan Declined"<<endl;

	cout<<"Class 1 : Good Loan Application"<<endl;
	cout<<"Class 2 : Poor Loan Application"<<endl;
    cout<<"Class 3 : Average Application"<<endl;

    //Input the relevant data
    float L[2][3];
	cout<<"Enter L(A1/W1)"<<endl;
	cin>>L[0][0];
	cout<<"Enter L(A1/W2)"<<endl;
	cin>>L[0][1];
    cout<<"Enter L(A1/W3)"<<endl;
    cin>>L[0][2];

	cout<<"Enter L(A2/W1)"<<endl;
	cin>>L[1][0];
	cout<<"Enter L(A2/W2)"<<endl;
	cin>>L[1][1];
    cout<<"Enter L(A2/W3)"<<endl;
    cin>>L[1][2];

    //Compute the relevant probabilities
    float P[3];
	cout<<"Enter P(w1/x) "<<endl;
    cin>>P[0];

    cout<<"Enter P(w2/x) "<<endl;
    cin>>P[1];

    cout<<"Enter P(w3/x)"<<endl;
    cin>>P[2];

    float R[2]={0};

    for(int i=0;i<2;i++){
       for(int j=0;j<3;j++){
       	 R[i]+=L[i][j]*P[j];
       }
    }

    //Printing the output
    int ans=0;
    for(int i=0;i<2;i++){
        if(ans<R[i])
        	ans=0;

        cout<<"Average Risk for Action"<<i+1<<"- "<<R[i]<<endl;
    }


    //Result
    if(R[0]<R[1])
    	cout<<"Loan Sanctioned"<<endl;
    else
    	cout<<"Loan Rejected"<<endl;

    return 0;
}
