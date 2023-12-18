//
// Created by oleks on 09.12.2023.
//

#include <vector>
#include "CString.h"


CString::CString() {
    value = "";
}

CString::CString(string newValue) {
    value = newValue;
}

void CString::operator=(const CString &other) {
    value = other.value;
}

void CString::operator=(const string &other) {
    value = other;
}

bool CString::operator==(const CString &other) {
    if(value==other.value)
        return true;
    else
        return false;
}

bool CString::operator==(const string &other) {
    if(value==other)
        return true;
    else
        return false;
}

string CString::toString() {
    return value;
}

CString CString::operator+(const CString &other) {
    return value + other.value;
}

CString CString::operator-(const CString &other) {
    int thisSize = value.size();
    int otherSize = other.value.size();
    string retValue = value;

    if (otherSize > thisSize)
        return retValue;

    bool loopBreak = false;
    int deletionIndex;

    int i = thisSize - otherSize; // Ustalenie początkowego indeksu porównywania.

    // Iteracja od końca aktualnego obiektu w kierunku początku, szukając drugiego obiektu.
    while (!loopBreak && i >= 0) {
        int iTmp = i;
        int iOtherTmp = 0;

        // Porównywanie znaków dwóch obiektów.
        while (value[iTmp] == other.value[iOtherTmp] && !loopBreak) {
            if ((iOtherTmp + 1) == otherSize) {
                loopBreak = true; // Jeśli znaleziono other.value w value, ustaw przerywnik pętli na true
                deletionIndex = i; // Ustalenie indeksu, od którego należy usunąć drugi obiekt.
            } else {
                iTmp++;
                iOtherTmp++;
            }
        }
        i--;
    }

    // Jeśli znaleziono drugi obiekt, zmodyfikuj retValue
    if (loopBreak) {
        retValue = "";
        for (int j = 0; j < thisSize; j++) {
            if (!(j >= deletionIndex && j < (deletionIndex + otherSize)))
                retValue += value[j];
        }
    }

    return retValue;
}

CString CString::operator*(const CString &other) {
    int thisSize = value.size();
    int otherSize = other.value.size();

    if (thisSize == 0 || otherSize == 0)
        return value; //

    string retValue = "";
    for (int i = 0; i < thisSize; i++) {
        retValue += value[i]; // Dodaj bieżący znak z aktualnego obiektu do wynikowego.
        if (value[i] == other.value[0]) {
            retValue += other.value.substr(1); // Dodaj resztę drugiego obiektu, jeśli znaleziono pasujący znak.
        }
    }

    return retValue;
}
CString CString::operator/(const CString &other) {
    int thisSize = value.size();
    int otherSize = other.value.size();
    string retValue = value;

    if (otherSize > thisSize)
        return retValue;

    vector<int> vecDeletionIndexes; // Wektor przechowujący indeksy do usunięcia z obiektu.
    bool loopBreak;

    // Iteracja przez value, szukając wszystkich wystąpień other.value
    for (int i = 0; i < thisSize; i++) {
        int iTmp = i;
        int iOtherTmp = 0;
        loopBreak = false;

        // Porównywanie znaków dwóch obiektów.
        while (value[iTmp] == other.value[iOtherTmp] && !loopBreak) {
            if ((iOtherTmp + 1) == otherSize) {
                loopBreak = true; // Jeśli znaleziono other.value w value, ustaw przerywnik pętli na true
                vecDeletionIndexes.push_back(i); // Dodaj indeks do usunięcia.
                i += (otherSize - 1); // Przesuń indeks, by pominąć całe wystąpienie drugiego obiektu.
            } else {
                iTmp++;
                iOtherTmp++;
            }
        }
    }

    bool toDelete = false; // Bool pomocniczy do usuwania odpowiednich znakow

    // Jeśli znaleziono wystąpienia other.value, usuń je z aktualnego obiektu.
    if (!vecDeletionIndexes.empty()) {
        retValue = "";
        int iCurrIndex;
        for (int i = 0; i < thisSize; i++) {
            if (toDelete && i == (iCurrIndex + otherSize))
                toDelete = false;
            if (!toDelete) {
                retValue += value[i];
            }
            if (!vecDeletionIndexes.empty() && i == vecDeletionIndexes.front()) {
                iCurrIndex = vecDeletionIndexes.front();
                toDelete = true;
                vecDeletionIndexes.erase(vecDeletionIndexes.begin());
            }
        }
    }

    return retValue;
}



