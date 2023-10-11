#pragma once
class Functions {
	
public:
	static const int CI_VALUE = 34;
	static void v_alloc_table_fill34(int iSize);
	static bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY);
	static bool b_dealloc_table_2_dim(int*** piTable, int iSizeX);
};