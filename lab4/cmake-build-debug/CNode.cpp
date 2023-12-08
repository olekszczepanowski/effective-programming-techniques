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
// Konstruktor bezparametrowy wezla
CNode::CNode() {
    children = NULL;
    parent = NULL;
    childrenCount = 0;
    currChildrenCount = 0;
    value = DEFAULT_VALUE;
}
// Konstruktor wezla z parametrem
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
        children=NULL;
        childrenCount=0;
    }
}
CNode::CNode(CNode &refNode) {
    value = refNode.value;
    childrenCount = refNode.childrenCount;
    currChildrenCount = refNode.currChildrenCount;
    if(refNode.parent==NULL)
        parent = NULL;
    switch(childrenCount){
        case 0 :
            children = NULL;
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
// Konstruowanie stringa w postaci prefixowej
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
// Obliczanie wartosci wezla
double CNode::calculate(map<std::string, double> variables) {
    // Jesli ma 0 dzieci
    if(childrenCount==0){
        // Sprawdzamy czy jest zmienna, jesli nie to zwracamy wartosc double ze stringa,
        // Jesli jest zmienna zwracamy wartosc z mapy variables
        if(!isVariable(value)) {
            double dValue = stod(value);
            return dValue;
        }
        else{
            return variables[this->value];
        }
    }
        // Jesli ma 1 dziecko to obliczamy albo wartosc sinusa albo cosinusa
    else if(childrenCount==1){
        if(value==SIN)
            return sin(children[0].calculate(variables));
        else
            return cos(children[0].calculate(variables));
    }
        // Jesli ma 2 dzieci, to obliczamy sume/roznice/iloczyn/iloraz dzieci
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
// Destruktor
CNode::~CNode() {
    delete[] children;
}
// Gettery i settery
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


