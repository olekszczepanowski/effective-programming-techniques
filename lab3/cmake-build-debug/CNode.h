//
// Created by oleks on 20.11.2023.
//

#ifndef LAB3_CNODE_H
#define LAB3_CNODE_H
#include <map>
#include <string>
using namespace std;
class CNode {
private:
    CNode *children;
    CNode *parent;
    int childrenCount;
    int tmpChildrenCount;
    string value;
public:
    CNode();
    CNode(CNode *newParent, string newValue);
    CNode(CNode &refNode);
    ~CNode();
    string prefix(string appendString);
    double calculate(map<string, double> variables);
    CNode *getChildren();
    CNode* getParent();
    void setParent(CNode *newParent);
    int getChildrenCount() const;
    int getTmpChildrenCount() const;
    void setTmpChildrenCount(int newValue);
    string getValue();
};
static const char DEFAULT_VALUE = ' ';
static const char MULTIPLICATION = '*';
static const char DIVISION = '/';
static const char ADDITION = '+';
static const char SUBSTRACTION = '-';
static const string SIN = "sin";
static const string COS = "cos";



#endif //LAB3_CNODE_H
