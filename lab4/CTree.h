//
// Created by oleks on 09.12.2023.
//

#ifndef LAB4TEST_CTREE_H
#define LAB4TEST_CTREE_H

#include <map>
#include <vector>
#include "CNode.h"
using namespace std;

static const string MULTIPLICATION_DEFAULT = "1";
static const string ADDITION_DEFAULT = "0";

template <typename T> class CTree {
private:
    CNode<T> *root;
    bool isFixed;
    map<string,string> variables;
public:
    CTree(){
        root = NULL;
        isFixed = false;
    }
    CTree(CNode<T>* newRoot){
        root = newRoot;
        isFixed = false;
    }

    CTree(vector<string> formula){
        isFixed = false;
        root = new CNode<T>(NULL, formula[0]); // Tworzenie korzenia drzewa na podstawie pierwszego elementu formuły

        // Sprawdzenie, czy korzeń jest zmienną i ustawienie jej w mapie zmiennych
        addVars(root,root);

        CNode<T> *parent = root; // Ustawienie rodzica jako korzeń
        CNode<T> *child = root; // Ustawienie dziecka jako korzeń

        // Przechodzenie przez formułę, zaczynając od indeksu 1, ponieważ pierwszy element został użyty do stworzenia korzenia
        for (int i = 1; i < formula.size(); i++) {
            // Dopóki rodzic ma rodzica i ilość docelowa dzieci jest równa aktualnej liczbie dzieci
            while ((parent->getParent() != NULL) && parent->getChildrenCount() == parent->getCurrChildrenCount()) {
                parent = parent->getParent(); // Przejdź do góry w drzewie
            }

            // Jeśli docelowa liczba dzieci rodzica nie jest równa aktualnej liczbie dzieci
            if (parent->getChildrenCount() != parent->getCurrChildrenCount()) {
                child = new CNode<T>(parent, formula[i]); // Stwórz nowe dziecko dla rodzica
                parent->getChildren()[parent->getCurrChildrenCount()] = *child; // Dodaj dziecko do tablicy dzieci rodzica
                addVars(child,parent);

                parent->setCurrChildrenCount(parent->getCurrChildrenCount() + 1); // Zwiększ licznik dzieci rodzica
                parent = &(parent->getChildren()[parent->getCurrChildrenCount() - 1]); // Przejdź do ostatniego utworzonego dziecka
            } else {
                isFixed = true; // Ustaw isFixed na true, gdy liczba dzieci jest równa maksymalnej liczbie dzieci rodzica
            }
        }

        // Sprawdzenie, czy docelowa liczba dzieci ostatniego rodzica nie jest równa aktualnej liczbie dzieci
        if (parent->getChildrenCount() != parent->getCurrChildrenCount()) {
            isFixed = true; // Ustaw flagę isFixed na true, gdy liczba dzieci jest różna od aktualnej liczby dzieci rodzica
        }

        // Dopoki docelowa liczba dzieci ostatniego rodzica nie jest równa aktualnej liczbie dzieci
        while (parent->getChildrenCount() != parent->getCurrChildrenCount()) {
            switch (parent->getValue()[0]) {
                case ADDITION:
                    child = new CNode<T>(parent, ADDITION_DEFAULT);
                    break;
                case SUBSTRACTION:
                    child =  new CNode<T>(parent, ADDITION_DEFAULT);
                    break;
                case MULTIPLICATION:
                    child =  new CNode<T>(parent, MULTIPLICATION_DEFAULT);
                    break;
                case DIVISION:
                    child = new CNode<T>(parent, MULTIPLICATION_DEFAULT);
                    break;
            }
            parent->getChildren()[parent->getCurrChildrenCount()] = *child; // Dodaj dziecko do tablicy dzieci rodzica
            parent->setCurrChildrenCount(parent->getCurrChildrenCount() + 1); // Zwiększ licznik dzieci rodzica

            // Jeśli rodzic ma swojego rodzica i liczba aktualnych dzieci jest równa docelowej liczbie dzieci rodzica
            if (parent->getParent() != NULL && parent->getCurrChildrenCount() == parent->getChildrenCount())
                parent = parent->getParent(); // Przejdź do góry w drzewie
        }

    }
    CTree(const CTree& other){
        isFixed = other.isFixed;
        root = new CNode<T>(*other.root);
        map<string, string> tmpMap = other.variables;
        map<string, string>::iterator it;
        for (it = tmpMap.begin(); it != tmpMap.end(); it++)
            variables[it->first] = it->second;
    }
    ~CTree(){
        delete root;
    };
    void addVars(CNode<T>* child, CNode<T>* parent);
    T treeValue();
    CString getKnownType();
    string variablesToString();
    string prefix();
    bool getIsFixed();
    bool setVariables(vector<string> values);
    map<string, string> getVariables();
    void join(CTree* newTree);
    void operator=(const CTree& newTree);
    CTree operator+(const CTree& newTree);

};

template<typename T>
void CTree<T>::addVars(CNode<T>* child, CNode<T>* parent)
{
    if (child->getChildrenCount() == 0 && isVariable(child->getValue()))
        variables[(parent->getChildren()[parent->getCurrChildrenCount()]).getValue()] = DEFAULT_VALUE;
}
template<>
void CTree<string>::addVars(CNode<string>* child, CNode<string>* parent)
{
    if (child->getChildrenCount() == 0 && isStringVariable(child->getValue()))
        variables[(parent->getChildren()[parent->getCurrChildrenCount()]).getValue()] = DEFAULT_VALUE;
}
template <typename T>
CString CTree<T>::getKnownType() {
    return root->getKnownType();
}
template <>
CString CTree<int>::getKnownType() {
    return root->getKnownType();
}
template <>
CString CTree<double>::getKnownType() {
    return root->getKnownType();
}
template <>
CString CTree<string>::getKnownType() {
    return root->getKnownType();
}
template <typename T>
T CTree<T>::treeValue() {
    return root->calculate(variables);
}
template <typename T>
string CTree<T>::variablesToString() {
    map<string, string>::iterator itr;
    string output;
    for(itr = variables.begin(); itr != variables.end(); itr++)
        output += ((*itr).first + DEFAULT_VALUE);
    return output;
}
template <typename T>
string CTree<T>::prefix() {
    return root->prefix("");
}
template <typename T>
bool CTree<T>::getIsFixed() {
    return isFixed;
}
template <typename T>
bool CTree<T>::setVariables(vector<string> values) {
    if (values.size() != variables.size()) {
        return false;
    }
    if (variables.size() == 0)
        return true;
    map<string, string>::iterator itr;
    int i = 0;
    for (itr = variables.begin(); itr != variables.end(); itr++) {
        if (getKnownType() == STRING) {
            if (!isStringVariable(values[i]))
                (*itr).second = values[i].substr(1, values[i].size() - 2);
            else
                return false;
        } else if (getKnownType() == DOUBLE) {
            if (!isDoubleVariable(values[i])) {
                    (*itr).second = to_string(stod(values[i]));
            } else {
                return false;
            }
        } else {
            if (!isVariable(values[i]))
                (*itr).second = values[i];
            else
                return false;
        }
        i++;
    }
    return true;
}

template <typename T>
map<string, string> CTree<T>::getVariables() {
    return variables;
}
template <typename T>
void CTree<T>::join(CTree<T> *newTree) {
    *this = *this + *newTree;
}
template <typename T>
void CTree<T>::operator=(const CTree<T>& newTree) {
    delete root;
    root = new CNode<T>(*newTree.root);
    variables.clear();
    map<string, string> tmpMap = newTree.variables;
    map<string, string>::iterator itr;
    for(itr = tmpMap.begin(); itr != tmpMap.end(); itr++){
        variables[itr->first] = itr->second;
    }
}
template <typename T>
CTree<T> CTree<T>::operator+(const CTree<T>& newTree) {
    CTree* returnTree = new CTree(*this);
    CTree* addedElem = new CTree(newTree);
    CNode<T>* tmp = (returnTree->root);
    while(tmp->getChildrenCount()!=0){
        tmp = &tmp->getChildren()[0];
    }
    if(isVariable(tmp->getValue()))
        returnTree->variables.erase(tmp->getValue());
    CNode<T>* parent = tmp->getParent();
    parent->getChildren()[0] = *addedElem->root;
    addedElem->root->setParent(parent);

    map<string, string>::iterator it;
    for (it = addedElem->variables.begin(); it != addedElem->variables.end(); it++)
        returnTree->variables[it->first] = it->second;

    addedElem = NULL;
    parent = NULL;
    return (*returnTree);
}
#endif //LAB4TEST_CTREE_H
