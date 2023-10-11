#include "Functions.h"
#include <iostream>

void Functions::v_alloc_table_fill34(int iSize) {
    if (iSize < 1 ) {
        std::cout << "Zly rozmiar tablicy." << std::endl;
        return;
    }
    int* pi_array;
    pi_array = new int[iSize];
    for (int iTmp = 0; iTmp < iSize; iTmp++) {
        pi_array[iTmp] = CI_VALUE;
    }
    for (int iTmp = 0; iTmp < iSize; iTmp++) {
        std::cout << "Wartosc elementu [" << iTmp << "] tablicy= " << pi_array[iTmp] << std::endl;
    }
    delete pi_array;
}

bool Functions::b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (iSizeX > 0 || iSizeY > 0 ) {
        *piTable = new int* [iSizeX];
        for (int iTmp = 0; iTmp < iSizeX; iTmp++) {
            (*piTable)[iTmp] = new int[iSizeY];
        }
        return true;
    }
    return false;
}

bool Functions::b_dealloc_table_2_dim(int*** piTable, int iSizeX) {
    if (iSizeX > 0) {
        for (int iTmp = 0; iTmp < iSizeX; iTmp++) {
            delete (*piTable)[iTmp];
        }
        delete* piTable;
        return true;
    }
    return false;
}

int main()
{
    std::cout << "Funkcjonalnosc nr 1:\n";
    Functions::v_alloc_table_fill34(3);
    std::cout << std::endl;
    Functions::v_alloc_table_fill34(0);
    std::cout << "\nFunkcjonalnosc nr 2:\n";
    int** pi_table;
    std::cout << std::boolalpha << Functions::b_alloc_table_2_dim(&pi_table, 5, 3) << std::endl;
    std::cout << "Funkcjonalnosc nr 3:\n";
    std::cout << std::boolalpha << Functions::b_dealloc_table_2_dim(&pi_table, 5) << std::endl;
    return 0;
}


