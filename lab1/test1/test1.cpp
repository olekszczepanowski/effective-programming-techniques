// test1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

int iValue = 34;


void v_alloc_table_fill34(int iSize);
bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY);
bool b_dealloc_table_2_dim(int*** piTable, int iSizeX);



int main()
{
    std::cout << "Funkcjonalnosc nr 1:\n";
    v_alloc_table_fill34(3);
    std::cout << std::endl;
    v_alloc_table_fill34(0);
    std::cout << "\nFunkcjonalnosc nr 2:\n";
    int **pi_table = nullptr;
    std::cout<<std::boolalpha<<b_alloc_table_2_dim(&pi_table, 5, 3)<<std::endl;
    std::cout << "Funkcjonalnosc nr 3:\n";
    std::cout << std::boolalpha << b_dealloc_table_2_dim(&pi_table, 5) << std::endl;
    return 0;
}

void v_alloc_table_fill34(int iSize) {
    if (iSize<=0 || iSize>INT_MAX) {
        std::cout << "Zly rozmiar tablicy." << std::endl;
        return;
    }
    int *pi_array;
    pi_array = new int[iSize];

    for (int iTmp = 0; iTmp < iSize; iTmp++) {
        pi_array[iTmp] = iValue;
    }
    for (int iTmp = 0; iTmp < iSize; iTmp++) {
        std::cout << "Wartosc elementu ["<<iTmp<<"] tablicy= "<<pi_array[iTmp] << std::endl;
    }
    delete pi_array;
}

bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeX > INT_MAX || iSizeY <= 0 || iSizeY > INT_MAX) {
        return false;
    }

    *piTable = new int*[iSizeX];

    for (int iTmp = 0; iTmp < iSizeX; iTmp++) {
        (*piTable)[iTmp] = new int[iSizeY];
    }
    return true;
}

bool b_dealloc_table_2_dim(int*** piTable, int iSizeX) {
    if (iSizeX <= 0 || iSizeX > INT_MAX) {
        return false;
    }

    for(int iTmp = 0 ; iTmp<iSizeX; iTmp++){
        delete (*piTable)[iTmp];
    }
   
    delete *piTable;
    return true;
}

