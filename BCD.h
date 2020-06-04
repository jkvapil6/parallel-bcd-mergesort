/* BCD.h */
#ifndef BCD_H_

#define BCD_H_

#include <string>

using namespace std;

class BCD {
private:
	string number;
	char code;
	int value;

public:
	BCD();

	BCD(string in);

	string ToString();

	char getCode();

	unsigned char *toBinary();

	int getValue();

	bool operator < (BCD &other);

	bool operator <= (BCD &other);

	bool operator > (BCD &other);

	bool operator >= (BCD &other);

	bool operator == (BCD &other);

	bool operator != (BCD &other);
};

#endif // BCD_H_


