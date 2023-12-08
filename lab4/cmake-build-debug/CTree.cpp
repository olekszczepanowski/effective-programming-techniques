//
// Created by oleks on 08.12.2023.
//

#include <iostream>
#include <sstream>
#include "CTree.h"
using namespace std;
// Konstruktor bezparametrowy
CTree::CTree() {
    root = NULL;
    isFixed = false;
}
// Konstruktor z parametrem tworzacy nowy korzen w drzewie
CTree::CTree(CNode *newRoot) {
    root = newRoot;
    isFixed = false;
}
// Konstruktor z parametrem tworzacy drzewo na podstawie podanej formuly
CTree::CTree(vector<string> formula) {
    isFixed = false;
    root = new CNode(NULL, formula[0]); // Tworzenie korzenia drzewa na podstawie pierwszego elementu formuły

    // Sprawdzenie, czy korzeń jest zmienną i ustawienie jej w mapie zmiennych
    if (root->getChildrenCount() == 0 && isVariable(root->getValue()))
        variables[root->getValue()] = NULL;

    CNode *parent = root; // Ustawienie rodzica jako korzeń
    CNode *child = root; // Ustawienie dziecka jako korzeń

    // Przechodzenie przez formułę, zaczynając od indeksu 1, ponieważ pierwszy element został użyty do stworzenia korzenia
    for (int i = 1; i < formula.size(); i++) {
        // Dopóki rodzic ma rodzica i ilość docelowa dzieci jest równa aktualnej liczbie dzieci
        while ((parent->getParent() != NULL) && parent->getChildrenCount() == parent->getCurrChildrenCount()) {
            parent = parent->getParent(); // Przejdź do góry w drzewie
        }

        // Jeśli docelowa liczba dzieci rodzica nie jest równa aktualnej liczbie dzieci
        if (parent->getChildrenCount() != parent->getCurrChildrenCount()) {
            child = new CNode(parent, formula[i]); // Stwórz nowe dziecko dla rodzica
            parent->getChildren()[parent->getCurrChildrenCount()] = *child; // Dodaj dziecko do tablicy dzieci rodzica
            if (child->getChildrenCount() == 0 && isVariable(child->getValue()))
                variables[(parent->getChildren()[parent->getCurrChildrenCount()]).getValue()] = NULL; // Dodaj zmienną do mapy zmiennych
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
        parent->getChildren()[parent->getCurrChildrenCount()] = *child; // Dodaj dziecko do tablicy dzieci rodzica
        parent->setCurrChildrenCount(parent->getCurrChildrenCount() + 1); // Zwiększ licznik dzieci rodzica

        // Jeśli rodzic ma swojego rodzica i liczba aktualnych dzieci jest równa docelowej liczbie dzieci rodzica
        if (parent->getParent() != NULL && parent->getCurrChildrenCount() == parent->getChildrenCount())
            parent = parent->getParent(); // Przejdź do góry w drzewie
    }
}

// Konstruktor kopiujący
CTree::CTree(const CTree &other) {
    isFixed = other.isFixed;
    root = new CNode(*other.root);
    map<string, double> tmpMap = other.variables;
    map<string, double>::iterator it;
    // Przepisywanie wartosci z mapy variables
    for (it = tmpMap.begin(); it != tmpMap.end(); it++)
        variables[it->first] = it->second;
}

// Destruktor
CTree::~CTree() {
    delete root;
}

// Obliczanie wartosci drzewa
double CTree::treeValue() {
    return root->calculate(variables);
}

// Zamiana zmiennych do typu string
string CTree::variablesToString() {
    map<string, double>::iterator itr;
    string output;
    for(itr = variables.begin(); itr != variables.end(); itr++)
        output += ((*itr).first + DEFAULT_VALUE);
    return output;
}
// Drzewo w postaci prefixowej
string CTree::prefix() {
    return root->prefix("");
}
// Getter isFixed
bool CTree::getIsFixed() {
    return isFixed;
}

// Ustawienie wartosci zmiennych
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

// Getter wartosci
map<string, double> CTree::getVariables() {
    return variables;
}

// Operator=
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
// Operator+ wykorzystywany w metodzie join
CTree CTree::operator+(const CTree& newTree) {
    // Tworzenie nowego drzewa i kopiowanie zawartości bieżącego drzewa
    CTree* returnTree = new CTree(*this);
    // Inicjalizacja nowego drzewa danymi z drzewa newTree
    CTree* addedElem = new CTree(newTree);
    // Ustawienie wskaźnika tmp na korzeń drzewa returnTree
    CNode* tmp = returnTree->root;
    // Przeszukiwanie drzewa w poszukiwaniu ostatniego elementu
    while(tmp->getChildrenCount()!=0){
        tmp = &tmp->getChildren()[0];
    }
    // Jeśli ostatni element jest zmienną, usuwa ją z mapy zmiennych w returnTree
    if(isVariable(tmp->getValue()))
        returnTree->variables.erase(tmp->getValue());
    // Przypisanie rodzica ostatniego elementu do zmiennej parent
    CNode* parent = tmp->getParent();
    // Zamiana pierwszego dziecka rodzica na korzeń drzewa addedElem
    parent->getChildren()[0] = *addedElem->root;
    // Ustawienie rodzica korzenia drzewa addedElem jako parent
    addedElem->root->setParent(parent);

    // Kopiowanie zmiennych z addedElem do returnTree
    map<string, double>::iterator it;
    for (it = addedElem->variables.begin(); it != addedElem->variables.end(); it++)
        returnTree->variables[it->first] = it->second;

    // Zwolnienie pamieci poprzez ustawienie wskaźników na nullptr
    addedElem = nullptr;
    parent = nullptr;

    return (*returnTree);
}

// Dolaczenie drzewa
void CTree::join(CTree *newTree) {
    *this = *this + *newTree;
}
// Zamiana stringa na vector
vector<string> stringToVec(string input) {
    vector<string> vecResult;
    stringstream ss(input);
    string tmp;
    while (getline(ss, tmp, DEFAULT_VALUE)) {
        vecResult.push_back(tmp);

    }
    return vecResult;
}
// Zamiana vectora na string
string vecToString(vector<string> vecInput, char connector) {
    string output = vecInput[0];
    for (int i = 1; i < vecInput.size(); i++) {
        output += DEFAULT_VALUE;
        output += connector;
        output += DEFAULT_VALUE;
        output += vecInput[i];
    }
    return output;}

// Sprawdzenie czy value jest zmienną
bool isVariable(string value) {
    for(int i = 0 ; i < value.length(); i++){
        if(!isdigit(value[i]))
            return true;
    }
    return false;
}
