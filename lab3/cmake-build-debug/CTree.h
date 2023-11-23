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
};

bool isVariable(string sValue);
static const string MULTIPLICATION_DEFAULT = "1";
static const string ADDITION_DEFAULT = "0";
#endif //LAB3_CTREE_H
