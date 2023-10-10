#pragma once

#include <string>

class CTable {
private:
    std::string s_name;
    int i_table_len;
    int *pi_table;

public:
    CTable();
    CTable(std::string sName, int iTableLen);
    CTable(CTable& pcOther);
    ~CTable();
   void vSetName(std::string sName);
   bool bSetNewSize(int iTableLen);
   CTable* pcClone();
   
};
void v_mod_tab(CTable* pcTab, int iNewSize);
void v_mod_tab(CTable cTab, int iNewSize);
void v_test_default();
void v_test_param();
void v_test_copy();
void v_test_name();
void v_test_clone();





