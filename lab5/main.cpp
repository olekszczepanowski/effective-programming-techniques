#include <iostream>
#include "CConsole.h"
#include "CMySmartPointer.h"

int main() {
//    CMySmartPointer<int> ptr1;
//    int *data = new int(10);
//    CMySmartPointer<int> ptr2(data);
//    CMySmartPointer<int> ptr3 = ptr2;

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
return 0;
}

