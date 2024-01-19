//
// Created by oleks on 18.12.2023.
//

#ifndef LAB5_CMYSMARTPOINTER_H
#define LAB5_CMYSMARTPOINTER_H

#include "CRefCounter.h"
#include <iostream>

using namespace std;

template<class T>
class CMySmartPointer {
private:
    T *pointer;
    CRefCounter *counter;
public:
    CMySmartPointer() {
        pointer = new T();
        counter = new CRefCounter();
        counter->add_ref();
        cout << "konstruktor bezparametrowy" << endl;
        printRef();
    }

    CMySmartPointer(T *newPointer) {
        pointer = newPointer;
        counter = new CRefCounter();
        counter->add_ref();
        cout << "konstruktor z parametrem" << endl;
        printRef();
    }

    CMySmartPointer(const CMySmartPointer<T> &other) {
        pointer = other.pointer;
        counter = other.counter;
        counter->add_ref();
        cout << "konstruktor kopiujacy" << endl;;
        printRef();
    }

    ~CMySmartPointer() {
        if (counter->dec_ref() == 0) {
            delete pointer;
            delete counter;
            cout << "destruktor" << endl;;
            printRef();
        }
    }

    CMySmartPointer &operator=(const CMySmartPointer<T> &other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (counter != nullptr && counter->dec_ref() == 0) {
            delete pointer;
            delete counter;
        }

        pointer = other.pointer;
        counter = other.counter;
        counter->add_ref();

        printRef();
        return *this;
    }

    T &operator*() const {
        return (*pointer);
    }

    T *operator->() const {
        return pointer;
    }

    void printRef() {
        cout << "Liczba odwolan: " << counter->get_refs() << endl;
    }

};

#endif //LAB5_CMYSMARTPOINTER_H
