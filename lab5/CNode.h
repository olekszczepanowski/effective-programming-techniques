//
// Created by oleks on 15.12.2023.
//

#ifndef LAB5_CNODE_H
#define LAB5_CNODE_H

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "CString.h"

using namespace std;

static const char DEFAULT_VALUE = ' ';
static const char MULTIPLICATION = '*';
static const char DIVISION = '/';
static const char ADDITION = '+';
static const char SUBSTRACTION = '-';
static const string SIN = "sin";
static const string COS = "cos";

static const string INT = "int";
static const string DOUBLE = "double";
static const string STRING = "string";
static const string UNKNOWN = "unknown";

vector<string> stringToVec(string input) {
    vector<string> vecResult;
    stringstream ss(input);
    string tmp;
    while (getline(ss, tmp, DEFAULT_VALUE)) {
        vecResult.push_back(tmp);
    }
    return vecResult;
}

string vecToString(vector<string> vecInput, char connector) {
    string output = vecInput[0];
    for (int i = 1; i < vecInput.size(); i++) {
        output += DEFAULT_VALUE;
        output += connector;
        output += DEFAULT_VALUE;
        output += vecInput[i];
    }
    return output;
}

bool isVariable(string value) {
    for(int i = 0 ; i < value.length(); i++){
        if(!isdigit(value[i]))
            return true;
    }
    return false;
}

bool isStringVariable(string sValue)
{
    if (sValue[0] == '"' && sValue[sValue.length() - 1] == '"')
        return false;
    return true;
}

bool isDoubleVariable(string value) {
    bool hasDot = false;
    for (int i = 0; i < value.length(); i++) {
        if (!isdigit(value[i])) {
            if (value[i] == '.' && !hasDot) {
                hasDot = true;
            } else {
                return false;
            }
        }
    }
    return hasDot; // Zwraca true, jeśli wartość jest liczbą zmiennoprzecinkową z dokładnością do jednej kropki dziesiętnej
}


template <typename T> class CNode {
private:
    CNode *children;
    CNode *parent;
    int childrenCount;
    int currChildrenCount;
    string value;
public:
    CNode(){
        children = nullptr;
        parent = nullptr;
        childrenCount = 0;
        currChildrenCount = 0;
        value = DEFAULT_VALUE;
    }
    CNode(CNode *newParent, string newValue){
        parent = newParent;
        value = newValue;
        currChildrenCount = 0;
        if(newValue[0] == ADDITION || newValue[0] == SUBSTRACTION || newValue[0] == MULTIPLICATION || newValue[0] == DIVISION ){
            childrenCount = 2;
            children = new CNode[2];
        }
        else if(newValue == SIN || newValue == COS){
            if(getKnownType() == STRING){
                children = new CNode[0];
                children = 0;
            }
            childrenCount = 1;
            children = new CNode[1];
        }
        else{
            children=nullptr;
            childrenCount=0;
        }
    }
    CNode(CNode &refNode){
        value = refNode.value;
        childrenCount = refNode.childrenCount;
        currChildrenCount = refNode.currChildrenCount;
        if(refNode.parent==nullptr)
            parent = nullptr;
        switch(childrenCount){
            case 0 :
                children = nullptr;
                break;
            case 1:
                children = new CNode(*refNode.children);
                break;
            case 2:
                children = new CNode[2];
                children[0] = *(new CNode(refNode.children[0]));
                children[0].setParent(this);
                children[1] = *(new CNode(refNode.children[1]));
                children[1].setParent(this);
                break;
        }
    }
    ~CNode(){
        delete[] children;
    }
    CString getKnownType();
    string prefix(string appendString);
    T calculate(map<string, string> variables);
    CNode *getChildren();
    CNode* getParent();
    void setParent(CNode *newParent);
    int getChildrenCount() const;
    int getCurrChildrenCount() const;
    void setCurrChildrenCount(int newValue);
    string getValue();
};

template<>
CString CNode<int>::getKnownType() {
    CString type;
    type = INT;
    return type;
}
template<>
CString CNode<double>::getKnownType() {
    CString type;
    type = DOUBLE;
    return type;
}
template<>
CString CNode<string>::getKnownType() {
    CString type;
    type = STRING;
    return type;
}
template <typename T>
string CNode<T>::prefix(std::string appendString) {
    appendString += value;
    if(childrenCount ==1)
        appendString+=(DEFAULT_VALUE + children[0].prefix(""));
    if(childrenCount == 2){
        appendString+=(DEFAULT_VALUE + children[0].prefix(""));
        appendString+=(DEFAULT_VALUE + children[1].prefix(""));
    }
    return appendString;
}
template <>
double CNode<double>::calculate(map<std::string, string> variables) {
    if(childrenCount==0){
        if(!isVariable(value)) {
            return stod(value);
        }
        else{
            return stod(variables[this->value]);
        }
    }
    else if(childrenCount==1){
        if(value==SIN)
            return sin(children[0].calculate(variables));
        else
            return cos(children[0].calculate(variables));
    }
    else{
        switch(value[0]){
            case ADDITION:
                return children[0].calculate(variables) + children[1].calculate(variables);
                break;
            case SUBSTRACTION:
                return children[0].calculate(variables) - children[1].calculate(variables);
                break;
            case MULTIPLICATION:
                return children[0].calculate(variables) * children[1].calculate(variables);
                break;
            case DIVISION:
                return children[0].calculate(variables) / children[1].calculate(variables);
                break;

        }
    }
}
template <>
int CNode<int>::calculate(map<std::string, string> variables) {
    if(childrenCount==0){
        if (!isVariable(value)) {
            return stoi(value);
        } else {
            return stoi(variables[this->value]);
        }
    }
    else if(childrenCount==1){
        if(value==SIN)
            return (int)sin(children[0].calculate(variables));
        else
            return (int)cos(children[0].calculate(variables));
    }
    else{
        switch(value[0]){
            case ADDITION:
                return (int)children[0].calculate(variables) + children[1].calculate(variables);
                break;
            case SUBSTRACTION:
                return (int)children[0].calculate(variables) - children[1].calculate(variables);
                break;
            case MULTIPLICATION:
                return (int)children[0].calculate(variables) * children[1].calculate(variables);
                break;
            case DIVISION:
                return (int)children[0].calculate(variables) / children[1].calculate(variables);
                break;
        }
    }
}

template <>
string CNode<string>::calculate(map<std::string, string> variables) {
    if(childrenCount==0){
        if(!isStringVariable(value)) {
            return value.substr(1,value.size()-2);
        }
        else{
            return variables[this->value];
        }
    }
    else{
        CString child1 = children[0].calculate(variables);
        CString child2 = children[1].calculate(variables);
        switch(value[0]){
            case ADDITION:
                return (child1+child2).toString();
                break;
            case SUBSTRACTION:
                return (child1-child2).toString();
                break;
            case MULTIPLICATION:
                return (child1*child2).toString();
                break;
            case DIVISION:
                return (child1/child2).toString();
                break;
        }
    }
}

template <typename T>
string CNode<T>::getValue() {
    return value;
}
template <typename T>
CNode<T>* CNode<T>::getChildren() {
    return children;
}
template <typename T>
CNode<T>* CNode<T>::getParent() {
    return parent;
}
template <typename T>
void CNode<T>::setParent(CNode<T> *newParent) {
    parent = newParent;
}
template <typename T>
int CNode<T>::getChildrenCount() const {
    return childrenCount;
}
template <typename T>
int CNode<T>::getCurrChildrenCount() const {
    return currChildrenCount;
}
template <typename T>
void CNode<T>::setCurrChildrenCount(int newValue) {
    currChildrenCount=newValue;
}



#endif //LAB5_CNODE_H
