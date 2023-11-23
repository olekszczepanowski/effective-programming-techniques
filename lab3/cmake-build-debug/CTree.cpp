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
        while((parent->getParent()!= nullptr) && parent->getChildrenCount() == parent->getTmpChildrenCount()){
            parent = parent->getParent();
        }
        if(parent->getChildrenCount()!=parent->getTmpChildrenCount()){
            child = new CNode(parent,formula[i]);
            parent->getChildren()[parent->getTmpChildrenCount()] = *child;
            if(child->getChildrenCount()==0 && isVariable(child->getValue()))
                variables[(parent->getChildren()[parent->getTmpChildrenCount()]).getValue()] = NULL;
            parent->setTmpChildrenCount(parent->getTmpChildrenCount()+1);
            parent = &(parent->getChildren()[parent->getTmpChildrenCount()-1]);
        }
        else{
            isFixed = true;
        }
    }
    if(parent->getChildrenCount() != parent->getTmpChildrenCount()){
        isFixed = true;
    }
    while (parent->getChildrenCount() != parent->getTmpChildrenCount()){
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
        parent->getChildren()[parent->getTmpChildrenCount()] = *child;
        parent->setTmpChildrenCount(parent->getTmpChildrenCount()+1);
        if(parent->getParent() != nullptr && parent->getTmpChildrenCount() == parent->getChildrenCount())
            parent = parent->getParent();
    }
}
bool isVariable(string value) {
    for(int i = 0 ; i < value.length(); i++){
        if(!isdigit(value[i]))
            return true;
    }
    return false;
}
