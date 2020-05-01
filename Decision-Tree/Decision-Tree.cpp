#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>

#include <string>
#include <vector>
#include <map>

using namespace::std;
// an attribute
struct node
{
vector<string> attritibutevalue;
};

// one line of attributes
struct attritibutes
{
vector<node> datacell;
};

// array of attributes
struct datanode
{
vector<attritibutes> dataline;
};

// tree diagram
struct Tree
{
int decisionAttribute;
string label;
vector<Tree(*)> nodes;
};

// Read attributes from attributes file

void insertfAttributes(string filename, attritibutes& attVector ) {
ifstream file(filename);
string line;
int linenum = 0;
if (file.is_open())
{
while (getline(file, line))
{
node d;
string searchar = " ";
size_t pos = 0;
std::string token;
int i=0;
while ((pos = line.find(" ")) != std::string::npos) {
token = line.substr(0, pos);
if(i!=0)
d.attritibutevalue.push_back(token);
line.erase(0, pos + searchar.length());
i++;
}
d.attritibutevalue.push_back(line);
attVector.datacell.push_back(d);

}
file.close();
}
}

// Read Training and evaluation set
void getSets(string filename, datanode &dv)
{
ifstream file(filename);

string line;
attritibutes a;
node d;
string searchar = " ";
size_t pos = 0;
std::string token;
int iter = 0;
if (file.is_open())
{
while (getline(file, line))
{
a.datacell.clear();
pos = 0;
token.clear();
while ((pos = line.find(" ")) != std::string::npos)
{
d.attritibutevalue.clear();
token = line.substr(0, pos);
if (!token.empty())
{
d.attritibutevalue.push_back(token);
a.datacell.push_back(d);
}
line.erase(0, pos + searchar.length());
}
d.attritibutevalue.clear();
if (!line.empty())
{
d.attritibutevalue.push_back(line);
a.datacell.push_back(d);
dv.dataline.push_back(a);
}

}
file.close();
}
}

// Print attributes to screen, for debugging
void printAttribtes(attritibutes& dnode)
{
for (int k = 0; k <(int)dnode.datacell.size(); k++)
{
cout << "\t";
for (int j = 0; j<(int)dnode.datacell[k].attritibutevalue.size(); j++)
cout << dnode.datacell[k].attritibutevalue[j] << "\t";

}
cout << endl;
}

// print attribute array
void printVector(datanode dnode)
{
for (int i = 0; i <(int) dnode.dataline.size(); i++)
{
printAttribtes(dnode.dataline[i]);
}
}

// take log of 2
float log2(int nominator, int donomimnator)
{
if (nominator == 0)
return 0;

if (donomimnator == 0)
return 0;

return ((float)nominator / donomimnator);
}

// Calculate entropy
float entropy(datanode data, attritibutes Attributes, string AttributeValue, int attributeindex, int
targetAttribute, int& numofExaples)
{

int posex, negex;
float entr = 0.0f;
for (int k = 0; k < Attributes.datacell[targetAttribute].attritibutevalue.size(); k++)
{
posex = 0;
negex = 0;
numofExaples = 0;
for (int i = 0; i <(int) data.dataline.size(); i++)
{
if (data.dataline[i].datacell[attributeindex].attritibutevalue[0] ==

AttributeValue || AttributeValue == "*")

{
if (data.dataline[i].datacell[targetAttribute].attritibutevalue[0] ==

Attributes.datacell[targetAttribute].attritibutevalue[k])

{
posex++;
}
else
{
negex++;
}

}
}

numofExaples += posex + negex;
entr -= ((float)posex / (numofExaples))*log2(posex, numofExaples);
}
return entr;
}

// Calculate information gain
float informationgain(datanode data, attritibutes functionAttritibutes, int attributeindex, int
targetAttribute)
{
int totalexsub = 0;
float ig = entropy(data, functionAttritibutes, "*", attributeindex, targetAttribute , totalexsub);

for (int i = 0; i <(int) functionAttritibutes.datacell[attributeindex].attritibutevalue.size(); i++)
{
int numofex = 0;
float subent = entropy(data, functionAttritibutes,

functionAttritibutes.datacell[attributeindex].attritibutevalue[i], attributeindex,targetAttribute, numofex);

ig -= (((float)numofex) / totalexsub)*subent;
}

return ig;
}

// set attribute value is used
void setusedIndex(bool* usedindexesarr, int index)
{
usedindexesarr[index] = true;
}

// check attribute value weather is used or not
bool isIndexUsed(bool* usedindexesarr, int index)
{
return usedindexesarr[index];
}

// get best classifier index for a attribute
int GetBestClassifierIndex(datanode data, attritibutes functionAttritibutes,int targetattribute, bool*
usedindexes )
{
int bestindex = -1;
float bestval = 0.0f;
float temp = 0.0f;
for (int i = 0; i < (int)functionAttritibutes.datacell.size(); i++)
{
if (isIndexUsed(usedindexes, i))
continue;
else
{
temp = informationgain(data, functionAttritibutes, i, targetattribute);
if (temp > bestval)
{
bestval = temp;
bestindex = i;
}
}
}
return bestindex;
}

// Get index of attribute value

int GetIndexValue(string val, attritibutes attfunction)
{
for (int i = 0; i <(int) attfunction.datacell.size(); i++)
{
for (int k = 0; k <(int) attfunction.datacell[i].attritibutevalue.size(); k++)
{
if (attfunction.datacell[i].attritibutevalue[k] == val)
return i;

}
}
return -1;
}

// get most common value index
int commonValueIndex(datanode& trainset,attritibutes& functionAttritibutes, int targetAttribute) {
int * commonValue;
commonValue = new
int[(int)functionAttritibutes.datacell[targetAttribute].attritibutevalue.size()];
for (int i = 0; i < trainset.dataline.size(); i++)
{
for (int k = 0; k <

(int)functionAttritibutes.datacell[targetAttribute].attritibutevalue.size(); k++)

if (trainset.dataline[i].datacell[targetAttribute].attritibutevalue[0]==

functionAttritibutes.datacell[targetAttribute].attritibutevalue[k])

{
commonValue[k]++;
}

}
int maxindex = 0;
for (int i = 1; i < (int)functionAttritibutes.datacell[targetAttribute].attritibutevalue.size(); i++)
{
if (commonValue[i] > commonValue[maxindex])

maxindex = i;

}
delete[] commonValue;
return maxindex;
}

// control all attributes value are used
bool checkAllused(bool* usedindexes, attritibutes& functionAttritibutes)
{
bool allused = true;
for (int i = 0; i < functionAttritibutes.datacell.size(); i++)
{
allused &= usedindexes[i];
}
return allused;
}

// control all values in data vector are the same
bool checkAllAreSame(datanode& data,attritibutes& functionAttribute,int targetAttribute )
{
bool same;
for (int i = 0; i < functionAttribute.datacell[targetAttribute].attritibutevalue.size(); i++)
{
same = true;
for (int k = 0; k < data.dataline.size(); k++)
{
same &= (data.dataline[k].datacell[targetAttribute].attritibutevalue[0] ==

functionAttribute.datacell[targetAttribute].attritibutevalue[i]);

}
if (same)
return same;

}

return same;
}

// ID3 algorithim
void ID3(datanode& trainset, int targetAttribute, attritibutes& functionAttritibutes, Tree * node, bool*
usedindexes)
{

if (checkAllAreSame(trainset, functionAttritibutes, targetAttribute))
{
node->decisionAttribute = targetAttribute;
node->label = trainset.dataline[0].datacell[targetAttribute].attritibutevalue[0];

}
else if (functionAttritibutes.datacell.size() == 0 || checkAllused(usedindexes,
functionAttritibutes))
{
int maxindex = commonValueIndex(trainset, functionAttritibutes, targetAttribute);
node->decisionAttribute = targetAttribute;
node->label = functionAttritibutes.datacell[targetAttribute].attritibutevalue[maxindex];
}
else
{
int classifier = GetBestClassifierIndex(trainset, functionAttritibutes, targetAttribute,

usedindexes);

if (classifier == -1)
{
int maxindex = commonValueIndex(trainset, functionAttritibutes,

targetAttribute);

node->label =

functionAttritibutes.datacell[targetAttribute].attritibutevalue[maxindex];

return;

}
node->decisionAttribute = classifier;
setusedIndex(usedindexes, node->decisionAttribute);

for (int i = 0; i <

functionAttritibutes.datacell[node->decisionAttribute].attritibutevalue.size(); i++)

{
Tree * childnode = new Tree();
node->nodes.push_back(childnode);
childnode->decisionAttribute = node->decisionAttribute;
childnode->label =

functionAttritibutes.datacell[node->decisionAttribute].attritibutevalue[i];

datanode subexamples;
for (int j = 0; j < trainset.dataline.size(); j++)
{
if

(trainset.dataline[j].datacell[childnode->decisionAttribute].attritibutevalue[0] == childnode->label)

{
subexamples.dataline.push_back(trainset.dataline[j]);
}
}
if (subexamples.dataline.size() == 0)
{
Tree* subnode = new Tree();
int maxindex = commonValueIndex(trainset, functionAttritibutes,

targetAttribute);

subnode->label =

functionAttritibutes.datacell[targetAttribute].attritibutevalue[maxindex];
subnode->decisionAttribute = targetAttribute;
childnode->nodes.push_back(subnode);
}
else

{
Tree * subnode = new Tree();
ID3(subexamples, targetAttribute, functionAttritibutes, subnode,

usedindexes);

childnode->nodes.push_back(subnode);
}
}
}
}

// print string to file
void printFile(string line)
{
ofstream writefile("rules.txt", ofstream::app);
if (writefile.is_open())
writefile << line<<endl;
writefile.close();
}

// print decision tree rules to screen and file
void printRules(Tree* t, string rootfunction)
{
if (!t->label.empty())
{
if (t->nodes.size() != 0)
rootfunction += "Attribute["+std::to_string(t->decisionAttribute) + "] == " +

t->label + " and ";
else
{
rootfunction.erase((int)(rootfunction.find_last_of("and")-2),

(int)rootfunction.size());

rootfunction += " => Attribute[" + std::to_string(t->decisionAttribute) + "] = "

+ t->label + " ";
}
}
for (int i = 0; i < t->nodes.size(); i++)
{
printRules(t->nodes[i],rootfunction);
}
if (t->nodes.size() == 0)
{
// Open to print decision tree functions to screen :)
cout << rootfunction << endl;
printFile(rootfunction);
}
}

// Check attribute is controlling the guessed value for the attribute is true for the test attributes
bool Checkatt(attritibutes& evalAttribute, Tree* decisionTree)
{
if (evalAttribute.datacell[decisionTree->decisionAttribute].attritibutevalue[0] ==
decisionTree->label || decisionTree->label.empty())
{
if (decisionTree->nodes.size() > 0)
{
bool find = false;
for (int i = 0; i < decisionTree->nodes.size(); i++)
find |= Checkatt(evalAttribute, decisionTree->nodes[i]);
return find;
}
else
{
return true;
}

}
else
return false;

}

// SearchTree function searches on decision tree and calculates accuracy
float SearchTree(datanode& evalSet, Tree* decisionTree)
{
int posex=0, negex=0;
for (int i = 0; i < evalSet.dataline.size(); i++)
if (Checkatt(evalSet.dataline[i], decisionTree))
posex++;
else
negex++;

return (float) posex / (posex + negex);

}

int main()
{
// varriable definitions
attritibutes functionAttritibutes;
datanode trainingset, evaluationSet;
// read values from file
insertfAttributes("functionAttributes.txt", functionAttritibutes);
getSets("trainingSet.txt", trainingset);
// create a dynamic array for used attribute indexes
bool * usedindexes;
int targetAttribute = 0;
usedindexes = new bool[(int)functionAttritibutes.datacell.size()];
for (int i = 0; i < (int)functionAttritibutes.datacell.size(); i++)
{

usedindexes[i] = false;
}
// Set target attribute indexes as used to not use in calculations for information gain
setusedIndex(usedindexes, targetAttribute);
// create for root decision tree
Tree* decisionTree = new Tree();
ID3(trainingset, targetAttribute,functionAttritibutes,decisionTree,usedindexes);
string root;
// Clear rules.txt file
ofstream writefile("rules.txt", ofstream::ate);
writefile.close();
//Write decision tree to file
// you can enable cout function in print rules function to print decision tree to screen
cout << "Writing Decision Tree Rules" << endl;
printRules(decisionTree,root);
// get evaluation set
getSets("evaluationSet.txt", evaluationSet);
// Search tree for evaluation set and print accuracy value
cout <<"\nAccuracy: "<< SearchTree(evaluationSet, decisionTree)<<endl;

// wait for user input to end program :)
getchar();
return 0;
}