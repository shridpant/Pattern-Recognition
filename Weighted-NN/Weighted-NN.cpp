#include <bits/stdc++.h>
using namespace std;

void toNormalize(vector<vector<float> >& v) {
    float minV = 1000000, maxV = -1000000, newMinV = 0.00, newMaxV = 1.00;
    int n = v.size();
    int f = v[0].size();
    for(int i = 0 ; i < f; i++) {
        minV = 1000000, maxV = -1000000;
        for(int j = 0; j < n; j++) {
            if(v[j][i] < minV) minV = v[j][i];
            if(v[j][i] > maxV) maxV = v[j][i];
        }
        for(int j = 0 ; j < n; j++) {
            v[j][i] = (float((v[j][i] - minV) / (maxV - minV)) * (newMaxV - newMinV)) + newMinV;
        }
    }
}

bool toSortSec(pair<string,int> a, pair<string,int> b) {
    return (a.second > b.second);
}

float toFindEucli(float n1, float n2) {
    return (n1 - n2) * (n1 - n2);
}

int main() {
    int c, f;
    map<string, int> classes;
    vector<string> nameClass;

    cout << "Enter number of classes : ";
    cin >> c;
    cout << "Enter number of features : ";
    cin >> f;

    string s;
    cout << "Enter the class names : " << endl;

    for(int i = 0 ; i < c; i++) {
        cin >> s;
        classes[s] = 0;
        nameClass.push_back(s);
    }

    vector<string> featureNames(f);
    cout << "Enter the feature names : " << endl;

    for(int i = 0; i < f; i++) cin >> featureNames[i];

    int n;
    cout << "Enter number of observations : ";
    cin >> n;

    vector<vector<float> > features (n, vector<float> (f));
    vector<pair<string, float> > weightedKNNclassValues(n);
    vector<pair<string, float> > normalizedKNNclassValues(n);

    cout << "Enter the observations : " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0 ;j < f; j++) {
            cin >> features[i][j];
        }
        cin >> weightedKNNclassValues[i].first;
        weightedKNNclassValues[i].second = 0;
        normalizedKNNclassValues[i].first = weightedKNNclassValues[i].first;
        normalizedKNNclassValues[i].second = 0;
    }

    vector<float> test(f);
    cout << "Enter test features : ";
    for(int j = 0 ; j < f; j++) cin >> test[j];

    for(int i = 0 ; i < n; i++) {
        for(int j = 0; j < f; j++) {
            weightedKNNclassValues[i].second += toFindEucli(test[j], features[i][j]);
        }
        weightedKNNclassValues[i].second = float(1 / sqrt(weightedKNNclassValues[i].second));
    }

    features.push_back(test);
    toNormalize(features);
    test = features[n];

    for(int i = 0 ; i < n; i++) {
        for(int j = 0; j < f; j++) {
            normalizedKNNclassValues[i].second += toFindEucli(test[j], features[i][j]);
        }
        normalizedKNNclassValues[i].second = sqrt(normalizedKNNclassValues[i].second);
    }

    cout << endl << "WEIGHTED KNN" << endl << endl;
    int k;
    cout << "Enter k for Weighted KNN: ";
    cin >> k;
    cout << "The weights: " << endl;
    for(int i = 1 ; i <= n; i++) {
        cout << i << ". " << weightedKNNclassValues[i - 1].second << endl;
    }

    sort(weightedKNNclassValues.begin(), weightedKNNclassValues.end(), toSortSec);
    int total = 0;
    string finalClass;
    map<string, float> freq;

    for(int i = 0 ; i < k; i++) {
        freq[weightedKNNclassValues[i].first] += weightedKNNclassValues[i].second;
    }
    float final_freq = 0;
    for(int i = 0; i < c; i++) {
        if(freq[nameClass[i]] > final_freq) {
            final_freq = freq[nameClass[i]];
            finalClass = nameClass[i];
        }
    }

    cout << endl << "Weighted KNN: The given feature set belongs to- " << finalClass << endl;

    cout << endl << "NORMALIZED KNN" << endl << endl;
    cout << "Enter k for Normalized KNN: ";
    cin >> k;

    cout << "The distances: " << endl;
    for(int i = 1 ; i <= n; i++) {
        cout << i << ". " << normalizedKNNclassValues[i - 1].second << endl;
    }

    sort(normalizedKNNclassValues.begin(), normalizedKNNclassValues.end(), toSortSec);
    total = 0;

    for(int i = 0 ; i < k; i++) {
        classes[normalizedKNNclassValues[n-i-1].first]++;
        if(classes[normalizedKNNclassValues[n-i-1].first] > total) {
            total++;
            finalClass = normalizedKNNclassValues[n-i-1].first;
        }
    }

    cout << endl << "Normalized KNN: The given feature set belongs to- " << finalClass << endl;

    return 0;
}