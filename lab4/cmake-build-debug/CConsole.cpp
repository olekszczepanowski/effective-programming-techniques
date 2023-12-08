//
// Created by oleks on 08.12.2023.
//

#include "CConsole.h"
#include <iostream>
#include <string>
#include "CTree.h"
using namespace std;

CConsole::CConsole() {
    formula = "";
    tree = nullptr;
}

void CConsole::menu() {
    while(true){
        cout << endl << "-------------------------" << endl;
        cout << "Wpisz komende:" << endl;
        cout << "1. Wprowadz nowa formule: enter <formula>" << endl;
        cout << "2. Wyswietl zmienne w formule: vars" << endl;
        cout << "3. Oblicz formule dla podanych zmiennych: comp <var1> <var2> ... <varN> [ilosc wartosci musi rownac sie ilosc zmiennych w vars]" << endl;
        cout << "4. Wyswietl formule w postaci prefiksowej: print" << endl;
        cout << "5. Dolacz nowa formule do aktualnej: join <formula>" << endl;
        cout << "6. Wyjdz: quit" << endl << endl;
        string input;
        getline(cin, input);
        if (input == QUIT) {
            delete tree;
            return;
        }
        vector<string> vecInput = stringToVec(input);
        string key = vecInput[0];
        vecInput.erase(vecInput.begin());
        if (key == VARS) {
            if (tree != nullptr)
                cout << tree->variablesToString() << endl;
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == PRINT) {
            if (tree != nullptr)
                cout << tree->prefix() << endl;
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == COMP) {
            if (tree != nullptr) {
                if (tree->setVariables(vecInput))
                    cout << "Wartosc formuly wynosi: " << tree->treeValue() << endl;
            }
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == JOIN) {
            if (tree != nullptr) {
                tree->join(new CTree(vecInput));
                if (tree->getIsFixed())
                    cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci.";
            }
            else
                cout << "Nie podano drzewa." << endl;
        }
        else if (key == ENTER) {
            delete tree;
            tree = new CTree(vecInput);
            if (tree->getIsFixed())
                cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci.";
        }
        else {
            cout << "Niepoprawne polecenie! Sprobuj ponownie." << endl;
        }
    }
}
