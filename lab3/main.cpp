#include <iostream>
#include "cmake-build-debug/CNode.h"
#include "cmake-build-debug/CTree.h"

int main() {
    CNode cnode;
    cnode.print();
    CTree ctree;
    ctree.v_print();
    return 0;
}
