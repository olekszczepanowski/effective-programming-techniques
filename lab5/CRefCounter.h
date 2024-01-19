//
// Created by oleks on 18.12.2023.
//

#ifndef LAB5_CREFCOUNTER_H
#define LAB5_CREFCOUNTER_H
#include <iostream>
class CRefCounter {
private:
    int i_counter;

public:
    CRefCounter() {
        i_counter = 0;
    }

    void add_ref() {
        i_counter++;
    }

    int dec_ref() {
        return --i_counter;
    }

    int get_refs() const {
        return i_counter;
    }
};


#endif //LAB5_CREFCOUNTER_H
