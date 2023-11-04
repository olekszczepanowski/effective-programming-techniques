#pragma once
#include <string>
#include <sstream>

class CNumber
{
private:
	int i_length;
	int* pi_table;
	bool b_is_negative;
	void v_fill_table(int iValue);
	int i_getValueLength(int iValue);
	void v_fill_with_values(int iValue, int iTmp);
	bool b_copy_values(const CNumber& pcOther);
	bool b_copy_variables(const CNumber& pcOther);
	void v_addHelper(const CNumber& pcOther, CNumber &cResult);
	void v_substractHelper(const CNumber& pcOther, CNumber &cResult, const CNumber& cThisObject);
	bool b_get_sign_of_bigger_table(const CNumber& pcOther) const;

public:
	const int CI_DEFAULT_LENGTH = 100;
	CNumber();
	CNumber(int iSize);
	CNumber(const CNumber& pcOther);
	~CNumber();
	bool b_get_isNegative();
	void v_set_is_negative(bool bIsNegative);
	void v_ToStr();
	std::string sToStr();
	int i_get_len();
	int* pi_get_pi_table();
	CNumber& operator= (int iValue);
	CNumber& operator=(const CNumber& pcOther);
	CNumber operator+(const CNumber& pcNewVal) ;
	CNumber operator-(const CNumber& pcNewVal);
	CNumber operator*(const CNumber& pcNewVal);
	CNumber operator/(const CNumber& pcNewVal);
	bool operator==(int iValue) const;
	bool operator>=(const CNumber& cOther) const;

	
	

};

