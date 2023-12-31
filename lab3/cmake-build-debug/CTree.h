//
// Created by oleks on 20.11.2023.
//

#ifndef LAB3_CTREE_H
#define LAB3_CTREE_H
#include <map>
#include <vector>
#include "CNode.h"
using namespace std;
class CTree {
private:
    CNode *root;
    bool isFixed;
    map<string,double> variables;
public:
    CTree();
    CTree(CNode* newRoot);
    CTree(vector<string> formula);
    CTree(const CTree& other);
    ~CTree();
    double treeValue();
    string variablesToString();
    string prefix();
    bool getIsFixed();
    bool setVariables(vector<string> values);
    map<string, double> getVariables();
    void join(CTree* newTree);
    void operator=(const CTree& newTree);
    CTree operator+(const CTree& newTree);

};
vector<string> stringToVec(string input);
string vecToString(vector<string> vecInput, char connector);
bool isVariable(string sValue);
static const string MULTIPLICATION_DEFAULT = "1";
static const string ADDITION_DEFAULT = "0";
#endif //LAB3_CTREE_H
