//
// Created by oleks on 08.12.2023.
//

#include <iostream>
#include "CNode.h"
#include "CTree.h"

using namespace std;
#include <string>
#include <cmath>
#include <vector>
#include <map>

CNode::CNode() {
    children = nullptr;
    parent = nullptr;
    childrenCount = 0;
    currChildrenCount = 0;
    value = DEFAULT_VALUE;
}
CNode::CNode(CNode *newParent, string newValue) {
    parent = newParent;
    value = newValue;
    currChildrenCount = 0;
    if(newValue[0] == ADDITION || newValue[0] == SUBSTRACTION || newValue[0] == MULTIPLICATION || newValue[0] == DIVISION ){
        childrenCount = 2;
        children = new CNode[2];
    }
    else if(newValue == SIN || newValue == COS){
        childrenCount = 1;
        children = new CNode[1];
    }
    else{
        children=nullptr;
        childrenCount=0;
    }
}
CNode::CNode(CNode &refNode) {
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
string CNode::prefix(std::string appendString) {
    appendString += value;
    if(childrenCount ==1)
        appendString+=(DEFAULT_VALUE + children[0].prefix(""));
    if(childrenCount == 2){
        appendString+=(DEFAULT_VALUE + children[0].prefix(""));
        appendString+=(DEFAULT_VALUE + children[1].prefix(""));
    }
    return appendString;
}
double CNode::calculate(map<std::string, double> variables) {
    if(childrenCount==0){
        if(!isVariable(value)) {
            double dValue = stod(value);
            return dValue;
        }
        else{
            return variables[this->value];
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
            case SUBSTRACTION:
                return children[0].calculate(variables) - children[1].calculate(variables);
            case MULTIPLICATION:
                return children[0].calculate(variables) * children[1].calculate(variables);
            case DIVISION:
                return children[0].calculate(variables) / children[1].calculate(variables);
        }
    }
}

CNode::~CNode() {
    delete[] children;
}
CNode* CNode::getChildren() {
    return children;
}
CNode* CNode::getParent() {
    return parent;
}
void CNode::setParent(CNode *newParent) {
    parent = newParent;
}
int CNode::getChildrenCount() const {
    return childrenCount;
}
string CNode::getValue() {
    return value;
}

int CNode::getCurrChildrenCount() const {
    return currChildrenCount;
}

void CNode::setCurrChildrenCount(int newValue) {
    currChildrenCount=newValue;
}

