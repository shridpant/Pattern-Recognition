// C++ Program for Bayes Classifier

#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector <pair<vector<string>,string> > v1;
    vector < string> classes;
    vector < string> features;
    map<string,float> mp;
    int cl_count,f_count;

    cout<<"Enter number of classes and features : "<<endl;
    cin>>cl_count>>f_count;
    vector<string> classvec;
    cout<<"Enter classes categories: "<<endl;

    for(int i=0;i<cl_count;i++)
    { 
        string value;
        cin>>value;
        classvec.push_back(value);
    }
    cout<<"Enter feature names : "<<endl;

    vector<string> featurevec;
    for(int i=0;i<f_count;i++)
    { 
        string fea;
        cin>>fea;
        featurevec.push_back(fea);
    }
    cout<<endl<<"--------------------------------------------------------------------------------------------------------"<<endl;
    
    cout<<"Enter data: "<<endl;
    for(int i=0;i<10;i++)
    {
        vector<string> temp;
        for(int j=0;j<f_count;j++)
        { 
            string feavalue;
            cin>>feavalue;
            temp.push_back(feavalue);
        }

        string output;
        cin>>output;
        mp[output]++;

        for(int k=0;k<f_count;k++)
        {
            mp[featurevec[k]+temp[k]+output]++;
            mp[featurevec[k]+temp[k]]++;
        }
        v1.push_back({temp,output});
    }

    map <string,float> probs;
    for(int i=0;i<cl_count;i++)
    {
        probs[classvec[i]]=mp[classvec[i]]/10;
    }

    for(int d=0;d<10;d++)
    {
        vector<string> s1=v1[d].first;
        string s2= v1[d].second;

        for(int z=0;z<f_count;z++)
        {
            probs[featurevec[z]+s1[z]+s2]=mp[featurevec[z]+s1[z]+s2]/mp[s2];
            // cout<<probs[featurevec[z]+s1[z]+s2]<<endl;
        }
    }
    cout<<endl<<"--------------------------------------------------------------------------------------------------------"<<endl;
    
    cout<<"Enter input : "<<endl;
    vector<string> input;

    for(int k=0;k<f_count;k++)
    {
        string s;
        cin>>s;
        input.push_back(s);
    }

    cout<<endl<<"--------------------------------------------------------------------------------------------------------"<<endl;
    
    string maxclass;
    float maxprob=0;

    for(int t=0;t<cl_count;t++)
    {
        float currprob=1;
        for(int f=0;f<f_count;f++)
        { 
            currprob=currprob*probs[featurevec[f]+input[f] + classvec[t]];
        }

        cout<<"Probability of the given data belonging to class : "<<classvec[t]<<":"<<currprob*probs[classvec[t]]<<endl;
        
        if(currprob>maxprob)
        {
            maxprob=currprob;
            maxclass=classvec[t];
        }
    }

    cout<<endl<<"--------------------------------------------------------------------------------------------------------"<<endl;
   
    cout<<"The input belongs to class : "<<maxclass<<endl;
}