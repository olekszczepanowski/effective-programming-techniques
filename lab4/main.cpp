#include <iostream>
#include "cmake-build-debug/CConsole.h"
#include "cmake-build-debug/CNode.h"
#include "cmake-build-debug/CTree.h"
int main() {
    CConsole* console = new CConsole();
    console->menu();
    delete console;
}
