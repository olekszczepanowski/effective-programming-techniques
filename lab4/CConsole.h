//
// Created by oleks on 09.12.2023.
//

#ifndef LAB4TEST_CCONSOLE_H
#define LAB4TEST_CCONSOLE_H
#include "CTree.h"
#include <string>

static const string JOIN = "join";
static const string PRINT = "print";
static const string COMP = "comp";
static const string ENTER = "enter";
static const string VARS = "vars";
static const string QUIT = "quit";
static const string RETURN = "return";

using namespace std;

template <typename T> class CConsole {
private:
    string formula;
    CTree<T> *tree;

public:
    CConsole(){
        formula = "";
        tree = NULL;
    }
    void menu();
};

template <typename T>
void CConsole<T>::menu() {
    while(true){
        cout << endl << "-------------------------" << endl;
        cout << "Wpisz komende:" << endl;
        cout << "1. Wprowadz nowa formule: enter <formula>" << endl;
        cout << "2. Wyswietl zmienne w formule: vars" << endl;
        cout << "3. Oblicz formule dla podanych zmiennych: comp <var1> <var2> ... <varN> [ilosc wartosci musi rownac sie ilosc zmiennych w vars]" << endl;
        cout << "4. Wyswietl formule w postaci prefiksowej: print" << endl;
        cout << "5. Dolacz nowa formule do aktualnej: join <formula>" << endl;
        cout << "6. Wroc do wyboru typu: return" << endl << endl;
        string input;
        getline(cin, input);
        if (input == RETURN) {
            delete tree;
            return;
        }
        vector<string> vecInput = stringToVec(input);
        string key = vecInput[0];
        vecInput.erase(vecInput.begin());
        if (key == VARS) {
            if (tree != NULL)
                cout << tree->variablesToString() << endl;
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == PRINT) {
            if (tree != NULL)
                cout << tree->prefix() << endl;
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == COMP) {
            if (tree != NULL) {
                if (tree->setVariables(vecInput))
                    cout << "Wartosc formuly wynosi: " << tree->treeValue() << endl;
            }
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == JOIN) {
            if (tree != NULL) {
                tree->join(new CTree<T>(vecInput));
                if (tree->getIsFixed())
                    cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci.";
            }
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == ENTER) {
            delete tree;
            tree = new CTree<T>(vecInput);
            if (tree->getIsFixed())
                cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci.";
        }
        else {
            cout << "Niepoprawne polecenie! Sprobuj ponownie." << endl;
        }
    }
}

#endif //LAB4TEST_CCONSOLE_H
