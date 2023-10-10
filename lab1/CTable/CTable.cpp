#include "CTable.h"
#include <iostream>


int DEFAULT_LEN = 5;
std::string DEFAULT_NAME = "default";

CTable::CTable() {
    s_name = DEFAULT_NAME;
    std::cout << "bezp: " << s_name << std::endl;
    i_table_len = DEFAULT_LEN;
    pi_table = new int[i_table_len];
}

CTable::CTable(std::string sName, int iTableLen) {
    if (iTableLen <= 0) {
        return;
    }
    s_name = sName;
    std::cout << "parametr: " << s_name << std::endl;
    i_table_len = iTableLen;
    pi_table = new int[i_table_len];
}

CTable::CTable(CTable& pcOther) {
    s_name = pcOther.s_name + "_copy";
    i_table_len = pcOther.i_table_len;
    pi_table = new int[i_table_len];
    for (int ii = 0; ii < i_table_len; ii++) {
        pi_table[ii] = pcOther.pi_table[ii];
    }
    std::cout << "kopiuj: " << s_name << std::endl;
}
CTable::~CTable() {
    delete pi_table;
    std::cout << "usuwam " << s_name << std::endl;
}
void CTable::vSetName(std::string sName) {
    s_name = sName;
}
bool CTable::bSetNewSize(int iTableLen) {
    if (iTableLen <= 0) {
        return false;
    }
    int* pi_new_table = new int[iTableLen];
    delete pi_table;
    pi_table = pi_new_table;
    return true;
}
CTable* CTable::pcClone() {
    return new CTable(s_name, i_table_len);
}
void v_mod_tab(CTable* pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);
}
void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}
void v_test_default() {
    std::cout << "Konstruktor bezparametrowy: " << std::endl;
    CTable* pcTab = new CTable();
    v_mod_tab(pcTab, 10);
    delete pcTab;
    std::cout <<std::endl;
    CTable cTab;
    v_mod_tab(cTab, 10);
}

void v_test_param() {
    std::cout << "Konstruktor z parametrem:" << std::endl;
    CTable* pcTab = new CTable("*pcTab", 3);
    v_mod_tab(pcTab, 10);
    delete pcTab;
    std::cout << std::endl;
    CTable cTab("cTab",3);
    v_mod_tab(cTab, 10);
}

void v_test_copy() {
    std::cout << "Konstruktor z kopiujacy:" << std::endl;
    CTable* pcTab1 = new CTable("*pcTab1",3);
    CTable* pcTab2 = new CTable(*pcTab1);
    v_mod_tab(pcTab2, 10);
    delete pcTab1;
    delete pcTab2;
    std::cout << std::endl;
    CTable cTab1("cTab1", 3);
    CTable cTab2(cTab1);
    v_mod_tab(cTab2, 10);
}
void v_test_name() {
    std::cout << "Test zmiany nazwy: " << std::endl;
    CTable* pcTab = new CTable("*pcTab", 3);
    pcTab->vSetName("*pcTabChangedName");
    delete pcTab;
    std::cout << std::endl;
    CTable cTab("cTab", 3);
    cTab.vSetName("cTabChanged");
}
void v_test_clone() {
    std::cout << "Test klonowania: " << std::endl;
    CTable* pcTab1 = new CTable("*pcTab", 3);
    CTable* pcTab2 = pcTab1->pcClone();
    delete pcTab1;
    delete pcTab2;
    std::cout << std::endl;
    CTable cTab1("cTab1", 3);
    CTable *pcTab3 = cTab1.pcClone();
    delete pcTab3;
}
int main() {
    v_test_default();
    std::cout << std::endl;
    v_test_param();
    std::cout << std::endl;
    v_test_copy();
    std::cout << std::endl;
    v_test_name();
    std::cout << std::endl;
    v_test_clone();
    return 0;
}