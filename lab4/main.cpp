#include <iostream>
#include "CConsole.h"

using namespace std;
int main() {
    bool quit = false;
    while (!quit){
        cout << endl << "===============================" << endl;
        cout << "Wybierz jakiego typu drzewo chcesz wprowadzic (string/double/int) lub wpisz quit aby opuscic program: " << endl << endl;
        string input;
        getline(cin, input);
        if (input == QUIT) {
            quit = true;
        }
        else if(input == INT){
            CConsole<int>* console = new CConsole<int>();
            console->menu();
            delete console;
        }
        else if(input == STRING){
            CConsole<string>* console = new CConsole<string>();
            console->menu();
            delete console;
        }
        else if(input == DOUBLE){
            CConsole<double>* console = new CConsole<double>();
            console->menu();
            delete console;
        }
        else {
            cout << "Niepoprawne polecenie, sprobuj ponownie!" << endl;
        }
    }
}
