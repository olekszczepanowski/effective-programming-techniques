#include <iostream>
#include "cmake-build-debug/CNode.h"
#include "cmake-build-debug/CTree.h"

int main() {
    vector<string> formula = {"*","2","5"};
    CTree ctree(formula);
    cout<<ctree.treeValue();
    return 0;
}
