
//
// Created by oleks on 08.12.2023.
//

#include <iostream>
#include <sstream>
#include "CTree.h"
using namespace std;
CTree::CTree() {
    root = nullptr;
    isFixed = false;
}
CTree::CTree(CNode *newRoot) {
    root = newRoot;
    isFixed = false;
}
CTree::CTree(vector<string> formula) {
    isFixed = false;
    root = new CNode(nullptr, formula[0]);
    if(root->getChildrenCount()==0 && isVariable(root->getValue()))
        variables[root->getValue()] = NULL;
    CNode *parent = root;
    CNode *child = root;
    for(int i = 1 ; i<formula.size(); i++){
        while((parent->getParent()!= nullptr) && parent->getChildrenCount() == parent->getCurrChildrenCount()){
            parent = parent->getParent();
        }
        if(parent->getChildrenCount()!= parent->getCurrChildrenCount()){
            child = new CNode(parent,formula[i]);
            parent->getChildren()[parent->getCurrChildrenCount()] = *child;
            if(child->getChildrenCount()==0 && isVariable(child->getValue()))
                variables[(parent->getChildren()[parent->getCurrChildrenCount()]).getValue()] = NULL;
            parent->setCurrChildrenCount(parent->getCurrChildrenCount() + 1);
            parent = &(parent->getChildren()[parent->getCurrChildrenCount() - 1]);
        }
        else{
            isFixed = true;
        }
    }
    if(parent->getChildrenCount() != parent->getCurrChildrenCount()){
        isFixed = true;
    }
    while (parent->getChildrenCount() != parent->getCurrChildrenCount()){
        switch (parent->getValue()[0]){
            case ADDITION:
                child = new CNode(parent, ADDITION_DEFAULT);
                break;
            case SUBSTRACTION:
                child =  new CNode(parent, ADDITION_DEFAULT);
                break;
            case MULTIPLICATION:
                child =  new CNode(parent, MULTIPLICATION_DEFAULT);
                break;
            case DIVISION:
                child = new CNode(parent, MULTIPLICATION_DEFAULT);
                break;
        }
        parent->getChildren()[parent->getCurrChildrenCount()] = *child;
        parent->setCurrChildrenCount(parent->getCurrChildrenCount() + 1);
        if(parent->getParent() != nullptr && parent->getCurrChildrenCount() == parent->getChildrenCount())
            parent = parent->getParent();
    }
}

CTree::CTree(const CTree &other) {
    isFixed = other.isFixed;
    root = new CNode(*other.root);
    map<string, double> tmpMap = other.variables;
    map<string, double>::iterator it;
    for (it = tmpMap.begin(); it != tmpMap.end(); it++)
        variables[it->first] = it->second;
}

CTree::~CTree() {
    delete root;
}

double CTree::treeValue() {
    return root->calculate(variables);
}

string CTree::variablesToString() {
    map<string, double>::iterator itr;
    string output;
    for(itr = variables.begin(); itr != variables.end(); itr++)
        output += ((*itr).first + DEFAULT_VALUE);
    return output;
}

string CTree::prefix() {
    return root->prefix("");
}

bool CTree::getIsFixed() {
    return isFixed;
}

bool CTree::setVariables(vector<string> values) {
    if(values.size()!=variables.size()){
        cout<<"Zla ilosc zmiennych"<<endl;
        return false;
    }
    if(variables.size()==0)
        return true;
    map<string, double>::iterator itr;
    int i = 0;
    for (itr = variables.begin(); itr != variables.end(); itr++) {
        (*itr).second = stod(values[i]);
        i++;
    }
    return true;
}

map<string, double> CTree::getVariables() {
    return variables;
}

void CTree::operator=(const CTree& newTree) {
    delete root;
    root = new CNode(*newTree.root);
    variables.clear();
    map<string, double> tmpMap = newTree.variables;
    map<string, double>::iterator itr;
    for(itr = tmpMap.begin(); itr != tmpMap.end(); itr++){
        variables[itr->first] = itr->second;
    }
}

CTree CTree::operator+(const CTree& newTree) {
    CTree* returnTree = new CTree(*this);
    CTree* addedElem = new CTree(newTree);
    CNode* tmp = returnTree->root;
    while(tmp->getChildrenCount()!=0){
        tmp = &tmp->getChildren()[0];
    }
    if(isVariable(tmp->getValue()))
        returnTree->variables.erase(tmp->getValue());
    CNode* parent = tmp->getParent();
    parent->getChildren()[0] = *addedElem->root;
    addedElem->root->setParent(parent);

    map<string, double>::iterator it;
    for (it = addedElem->variables.begin(); it != addedElem->variables.end(); it++)
        returnTree->variables[it->first] = it->second;

    addedElem = nullptr;
    parent = nullptr;
    return (*returnTree);
}

void CTree::join(CTree *newTree) {
    *this = *this + *newTree;
}

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
    return output;}


bool isVariable(string value) {
    for(int i = 0 ; i < value.length(); i++){
        if(!isdigit(value[i]))
            return true;
    }
    return false;
}

