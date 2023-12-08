//
// Created by oleks on 08.12.2023.
//

#ifndef LAB4_CCONSOLE_H
#define LAB4_CCONSOLE_H


#include "CTree.h"
using namespace std;
class CConsole {
private:
    string formula;
    CTree* tree;
public:
    CConsole();
    void menu();
};
static const string JOIN = "join";
static const string PRINT = "print";
static const string COMP = "comp";
static const string ENTER = "enter";
static const string VARS = "vars";
static const string QUIT = "quit";



#endif //LAB4_CCONSOLE_H
