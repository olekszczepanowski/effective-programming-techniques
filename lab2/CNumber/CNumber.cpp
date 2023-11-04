#include "CNumber.h"
#include <iostream>
#include <sstream>
#include <string>
CNumber::CNumber() {
	i_length = CI_DEFAULT_LENGTH;
	pi_table = new int[i_length];
	b_is_negative = false;
	v_fill_table(0);
}
CNumber::CNumber(int iSize) {
	i_length = iSize;
	pi_table = new int[i_length];
	b_is_negative = false;
	v_fill_table(0);
}

CNumber::CNumber(const CNumber& pcOther) {
	i_length = pcOther.i_length;
	pi_table = new int[i_length];
	b_copy_values(pcOther);
}
CNumber::~CNumber() {
	delete[] pi_table;
}
CNumber& CNumber::operator=(const CNumber& other) {
	if (this != &other) {
		b_copy_variables(other);
		b_copy_values(other);
	}
	return *this;
}
CNumber& CNumber::operator=(int iValue) {
	if (iValue < 0) {
		iValue *= -1;
		b_is_negative = true;
	}
	else {
		b_is_negative = false;
	}

	int i_digits = i_getValueLength(iValue);
	if (i_digits > i_length) {
		i_length = i_digits;
		v_fill_with_values(iValue, i_length - 1);
	}
	else {
		v_fill_with_values(iValue, i_length - 1);
	}
	return *this;
}
void CNumber::v_ToStr() {
	int i_start_index = 0;
	while (pi_table[i_start_index] == 0) {
		i_start_index++;
	}
	for (int i = i_start_index; i < i_length; i++) {
		std::cout << pi_table[i];
	}
}
bool CNumber::b_copy_values(const CNumber& pcOther) {
	for (int i = 0; i < i_length; i++) {
		pi_table[i] = pcOther.pi_table[i];
	}
	return true;
}
bool CNumber::b_copy_variables(const CNumber& pcOther) {
	delete[] pi_table;
	i_length = pcOther.i_length;
	pi_table = new int[i_length];
	return true;
}
void CNumber::v_fill_with_values(int iValue, int iTmp) {
	while (iTmp >= 0) {
		pi_table[iTmp] = iValue % 10;
		iTmp--;
		iValue/=10;
	}
}
int CNumber::i_getValueLength(int iValue) {
	int i_tmpLength = 0;
	int i_tmp = iValue;
	while (i_tmp != 0) {
		i_tmp /= 10;
		i_tmpLength++;
	}
	return i_tmpLength;
}
void CNumber::v_fill_table(int iValue) {
	for (int i = 0; i < i_length; i++) {
		pi_table[i] = iValue;
	}
}
CNumber CNumber::operator+(const CNumber& pcNewVal) {
	CNumber c_result;
	if (pcNewVal.b_is_negative == b_is_negative) {
		c_result.b_is_negative = b_is_negative;
		v_addHelper(pcNewVal, c_result);
	}
	else {
		bool b_sign = b_is_negative;
		if (b_get_sign_of_bigger_table(pcNewVal)) {
			v_substractHelper(pcNewVal, c_result, *this);
		}
		else {
			b_sign = pcNewVal.b_is_negative;
			v_substractHelper(*this, c_result, pcNewVal);
		}
		c_result.b_is_negative = b_sign;
	}

	return c_result;
}

CNumber CNumber::operator-(const CNumber& pcNewVal) {
	CNumber c_result;
	bool b_sign;
	if (pcNewVal.b_is_negative && !b_is_negative || !pcNewVal.b_is_negative && b_is_negative) {
		c_result.b_is_negative = b_is_negative;
		v_addHelper(pcNewVal, c_result);
	}
	else if (!b_is_negative && !pcNewVal.b_is_negative) {
		if (b_get_sign_of_bigger_table(pcNewVal)) {
			b_sign = b_is_negative;
			v_substractHelper(pcNewVal, c_result, *this);
		}
		else {
			b_sign = !pcNewVal.b_is_negative;
			v_substractHelper(*this, c_result, pcNewVal);
		}
		c_result.b_is_negative = b_sign;
	}
	else {
		if (b_get_sign_of_bigger_table(pcNewVal)) {
			v_substractHelper(pcNewVal, c_result, *this);
			b_sign = true;
		}
		else {
			v_substractHelper(*this, c_result, pcNewVal);
			b_sign = false;
		}
		c_result.b_is_negative = b_sign;
	}
	
	return c_result;
}
CNumber CNumber::operator*(const CNumber& pcNewVal) {
	CNumber c_result(i_length+pcNewVal.i_length);
	int i_carry, i_product;
	for (int i = i_length - 1; i >= 0; i--) {
		i_carry = 0;
		for (int j = pcNewVal.i_length - 1; j >= 0; j--) {
			i_product = pi_table[i] * pcNewVal.pi_table[j] + i_carry + c_result.pi_table[i + j + 1];
			i_carry = i_product / 10;
			c_result.pi_table[i + j + 1] = i_product % 10;
		}
		c_result.pi_table[i] += i_carry;
	}
	c_result.b_is_negative = b_is_negative != pcNewVal.b_is_negative;
	
	return c_result;
}
CNumber CNumber::operator/(const CNumber& pcNewVal) {
	CNumber c_result;
	CNumber c_tmp;
	CNumber tmpOther;
	CNumber c_iter;
	c_iter = 1;
	c_result = 0;
	if (pcNewVal.i_length > i_length || pcNewVal == 0) {
		return CNumber();
	}
	else {
		c_result = 0;
		c_tmp = *this;

		c_tmp.v_set_is_negative(false);
		tmpOther = pcNewVal;
		tmpOther.v_set_is_negative(false);
		while (c_tmp >= tmpOther) {
			c_tmp = c_tmp - tmpOther;
			c_result = c_result + c_iter;
		}
		c_result.b_is_negative = (b_is_negative != pcNewVal.b_is_negative);
	

		return c_result;
	}
}

bool CNumber::operator==(int iValue) const {
	for (int i = i_length - 1; i >= 0; i--) {
		if (pi_table[i] != iValue) {
			return false;
		}
	}
	return true;
}
bool CNumber::operator>=(const CNumber& cOther) const {
	for (int i = 0; i < i_length; i++) {
		if (pi_table[i] > cOther.pi_table[i]) {
			return true;
		}
		else if (pi_table[i] < cOther.pi_table[i]) {
			return false;
		}
	}
	return true;
}

void CNumber::v_addHelper(const CNumber& pcOther, CNumber& cResult) {
	int i_carry = 0;
	for (int i = i_length - 1; i >= 0; i--) {
		cResult.pi_table[i] = pi_table[i] + pcOther.pi_table[i] + i_carry;
		i_carry = cResult.pi_table[i] / 10;
		cResult.pi_table[i] %= 10;
	}
}
void CNumber::v_substractHelper(const CNumber& pcOther, CNumber &cResult, const CNumber &cThisObject)  {
	int i_borrow = 0;
	for (int i = i_length - 1; i >= 0; i--) {
		cResult.pi_table[i] = cThisObject.pi_table[i] - pcOther.pi_table[i] - i_borrow;
		if (cResult.pi_table[i] < 0) {
			i_borrow = 1;
			cResult.pi_table[i] += 10;
		}
		else {
			i_borrow = 0;
		}
	}
}
bool CNumber::b_get_sign_of_bigger_table(const CNumber& cOther) const {
	for (int i = 0; i < i_length; i++) {
		if (pi_table[i] < cOther.pi_table[i]) {
			return false;
		}
		else if (pi_table[i] > cOther.pi_table[i]) {
			return true;
		}
	}
	return false;
}
bool CNumber :: b_get_isNegative() {
	return b_is_negative;
}
void CNumber::v_set_is_negative(bool bIsNegative) {
	b_is_negative = bIsNegative;
}
int CNumber::i_get_len() {
	return i_length;
}
int* CNumber::pi_get_pi_table() {
	return pi_table;
}
std::string CNumber::sToStr()
{
	std::ostringstream oss;
	int i_start_index = 0;
	while (pi_table[i_start_index] == 0) {
		i_start_index++;
	}
	if (b_is_negative) {
		oss << "-";
	}
	for (int i = i_start_index; i < i_length; i++) {
		oss << pi_table[i];
	}
	
	return oss.str();
}

int main() {
	CNumber c_num_0, c_num_1,c_num_2,c_num_3,c_num_4,c_num_5,c_res_1,c_res_2,c_res_3;
	CNumber c_sub_res_1, c_sub_res_2, c_sub_res_3;
	CNumber c_mul_res_1, c_mul_res_2;
	CNumber c_div_res_1;
	c_num_4 = -10;
	c_num_5 = 1;
	c_num_0 = 1200;
	c_num_1 = 900;
	c_num_2 = -1100;
	c_num_3 = -500;
	std::cout << std::endl;
	std::cout << "1200+900 = ";
	c_res_1 = c_num_0 + c_num_1;
	c_res_1.v_ToStr();
	std::cout << std::endl;
	std::cout << "-1100+(-500) = ";
	c_res_2 = c_num_2 + c_num_3;
	c_res_2.v_ToStr();
	std::cout << std::endl;
	std::cout << "1200+(-1100) = ";
	c_res_3 = c_num_0 + c_num_2;
	c_res_3.v_ToStr();
	std::cout << std::endl;
	std::cout << "900-1200 = ";
	c_sub_res_1 = c_num_1 - c_num_0;
	c_sub_res_1.v_ToStr();
	std::cout << std::endl;
	c_sub_res_2 = c_num_0 - c_num_2;
	std::cout << "1200-(-1100) = ";
	c_sub_res_2.v_ToStr();
	std::cout << std::endl;
	std::cout << "-500-(-1100) = ";
	c_sub_res_3 = c_num_3 - c_num_2;
	c_sub_res_3.v_ToStr();
	std::cout << std::endl;
	std::cout << "1200*900 = ";
	c_mul_res_1 = c_num_0 * c_num_1;
	c_mul_res_1.v_ToStr();
	std::cout << std::endl;
	std::cout << "1200*(-1100)= ";
	c_mul_res_2 = c_num_0 * c_num_2;
	c_mul_res_2.v_ToStr();
	std::cout << std::endl;
	std::cout << "1200/10 = ";
	c_div_res_1 = c_num_0 / c_num_4;
	c_div_res_1.v_ToStr();
}


