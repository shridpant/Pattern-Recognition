// C++ Program for Naive Bayes

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int numCounter, tempVar;
    int c,f;
    cout << "Enter the number of categories: " ;
    cin >> c;
    map<string, int> categories;
    cout << "Enter the categories: ";
    for(int i = 0 ; i < c; i++){
        string s;
        cin >> s;
        categories.insert(make_pair(s,0));
    }
    cout << "Enter the number of features: ";
    cin>>f;
    cout << "Enter the features : ";
    vector<string> attributes;
    for(int i=0; i<f; i++){
        string s;
        cin>>s;
        attributes.push_back(s);
    }

    int n;
    cout << "Enter the number of observations: ";
    cin >> n;
    multimap<vector <string> , string >mp;

    cout<<"\nEnter the feature and class value:\n";
    for(int i = 0 ; i < n; i++)
    {
        vector<string> feature(f);
        for(int j = 0 ; j < attributes.size(); j++) {
            cin >> feature[j];
        }
        string s;
        cin >> s;
        categories[s]++;
        mp.insert(make_pair(feature, s));
    }

    vector<string> fea(f);
    cout << "Enter the feature values for which you want to find the class : \n";
    for(int i = 0 ; i < f; i++) {
        cin >> fea[i];
    }

    multimap<vector<string>, string >:: iterator it;

    map<string, float> probOfClasses;

    map<string, int> :: iterator it2 ;
    for(it2 = categories.begin() ; it2 != categories.end(); it2++) {
        string className = it2->first;
        cout << endl << className << endl;

        float prob = 1, p =  1;
        for(int i = 0 ; i < f; i++){
            int cnt1 = 0;
            int cnt2 = 0;

            for(it = mp.begin(); it != mp.end(); it++){
                if(it->first[i] == fea[i]) {
                    cnt1++;
                    if(it->second == className) {
                        cnt2++;
                    }
                }
            }
            p = float(cnt2) / categories[className] ;
            cout << "P(" << fea[i] << "/" << className << ") = " << p << endl;
            prob *= p;
        }
        probOfClasses.insert(make_pair(className, prob));

    }

    map<string, float> :: iterator it1;
    float maxProb = 0;
    string output;
    for(it1 = probOfClasses.begin(); it1 != probOfClasses.end(); it1++){
        if(it1->second > maxProb) {
            maxProb = it1->second;
            output = it1->first;
        }
        cout << endl << "The given feature set belongs to the class " << it1->first << " with a probability of " << it1->second << endl;
    }

    cout << endl << "Thus, the given feature set belongs to the class " << output << " with a probability of " << maxProb;
    return 0;
}