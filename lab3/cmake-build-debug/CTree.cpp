//
// Created by oleks on 20.11.2023.
//

#include <iostream>
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


bool isVariable(string value) {
    for(int i = 0 ; i < value.length(); i++){
        if(!isdigit(value[i]))
            return true;
    }
    return false;
}
