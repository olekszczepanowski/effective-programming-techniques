#include <iostream>
#include "CConsole.h"

int main() {
    CConsole* console = new CConsole();
    console->menu();
    delete console;
}
