
#include "BCD.h"

// default konstruktor
BCD::BCD() : number("A0"), code('A'), value(0) {}

// konstruktor
BCD::BCD(string in) : number(in) {
	code = number[number.length() - 1];
	if (code == 'B' || code == 'D') {
		value = -stoi((number.substr(0, number.length() - 1)).c_str());
	}
	else {
		value = stoi((number.substr(0, number.length() - 1)).c_str());
	}
}

string BCD::ToString() {
	return number;
}

char BCD::getCode() {
	return code;
}

unsigned char *BCD::toBinary() {

	unsigned char * retArr;

	unsigned char tmpHigh, tmpLow;
	
	int len = number.length() / 2;

	retArr = new unsigned char[len];

	for (int i = 0; i < number.length() - 2; i = i + 2) {

		tmpHigh = number[i] - 48;
		tmpLow = number[i + 1] - 48;

		retArr[i / 2] = (tmpHigh << 4) | tmpLow;
	}

	tmpHigh = number[number.length() - 2] - 48;
	tmpLow = number[number.length() - 1] - 55;
	retArr[len - 1] = (tmpHigh << 4) | tmpLow;

	return retArr;
}

int BCD::getValue() {
	return value;
}

bool BCD::operator < (BCD &other)
{
	return this->value < other.getValue();
}

bool BCD::operator <= (BCD &other)
{
	return this->value <= other.getValue();
}

bool BCD::operator > (BCD &other)
{
	return this->value > other.getValue();
}

bool BCD::operator >= (BCD &other)
{
	return this->value >= other.getValue();
}

bool BCD::operator == (BCD &other)
{
	return this->value == other.getValue();
}

bool BCD::operator != (BCD &other)
{
	return this->value != other.getValue();
}




