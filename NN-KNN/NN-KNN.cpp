// C++ Program for Nearest Neighbor and K-NN

#include <bits/stdc++.h>
using namespace std;

bool toSortSec(pair<string,int> a, pair<string,int> b) {
    return (a.second < b.second);
}

int toFindEucli(int n1, int n2) {
    return (n1 - n2) * (n1 - n2);
}

int main()
{
    int c, f;

    cout << "Enter the number of classes : ";
    cin >> c;
    cout << "Enter the number of features : ";
    cin >> f;
    string s;
    cout << "Enter the classes : " << endl;

    map<string, int> classes;
    
    for(int i = 0 ; i < c; i++) {
        cin >> s;
        classes[s] = 0;
    }

    vector<string> featureNames(f);
    cout << "Enter the features : " << endl;
    for(int i = 0; i < f; i++) cin >> featureNames[i];

    int n;
    cout << "Enter the number of observations : ";
    cin >> n;

    vector<vector<int> > features (n, vector<int> (f));
    vector<pair<string, float> > classValues(n);

    cout << "Enter the observations : " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0 ;j < f; j++) {
            cin >> features[i][j];
        }
        cin >> classValues[i].first;
        classValues[i].second = 0;
    }


    int k;
    cout << "Enter the value of k for KNN: ";
    cin >> k;
    vector<int> test(f);
    cout << "Enter the feature set that you want to find the class for : ";
    for(int j = 0 ; j < f; j++) cin >> test[j];

    for(int i = 0 ; i < n; i++) {
        for(int j = 0; j < f; j++) {
            classValues[i].second += toFindEucli(test[j], features[i][j]);
        }
        classValues[i].second = sqrt(classValues[i].second);
    }

    cout << "Distances between the given observations and the concerned point : " << endl;
    for(int i = 1 ; i <= n; i++) {
        cout << i << ". " << classValues[i - 1].second << endl;
    }

    sort(classValues.begin(), classValues.end(), toSortSec);
    int total = 0;
    string finalClass;

    for(int i = 0 ; i < k; i++) {
        classes[classValues[i].first]++;
        if(classes[classValues[i].first] > total) {
            total++;
            finalClass = classValues[i].first;
        }
    }
    cout << endl << "NN: The given feature set belongs to the class " << classValues[0].first << endl;
    cout << endl << "KNN: The given feature set belongs to the class " << finalClass << endl;
    return 0;
}