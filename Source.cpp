#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#include "BCD.h"
#include "MergeSort.h"
#include "MergeSort.cpp"  // nutné pro správnou kompilaci generických funkcí

using namespace std;

HANDLE thread1;
HANDLE thread2;

struct Param
{
	string file;
	bool desc;
};

struct retVal
{
	BCD * arr;
	int length;
};

retVal ret1, ret2;

retVal loadFile(bool desc, string file) {

	basic_ifstream<unsigned char> infile;
	infile.open(file, std::ios::binary);

	if (!infile.is_open()) {
		exit(EXIT_FAILURE);
	}
	
	unsigned char buffer;
	unsigned char low;
	unsigned char high;
	unsigned char tmp;
	
	int i = 0;
	string load = ""; // textová reprezentace BCD èísla
	bool first = true;
	BCD * arr = nullptr;
	int n = 0;
	retVal ret;
	
	// potøebujeme naèíct 8b, ktere rozdìlíme na 2x4b a hledáme hexa hodnotu, vyšší než 9 pro zjištìní konce BCD èísla 
	while (infile.read(&buffer, 1)) {

		low = buffer & 0xf;
		high = buffer >> 4;

		if (high > 9) {
			
			tmp = (high + 55); // chceme ASCII hodnotu, ne hexa
			load.push_back(tmp); // nelze provest append

			if (first) {
				cout << endl << "Vytvarim pole BCD cisel o delce: " << load << endl;
				n = BCD(load).getValue();
				arr = new BCD[n];
				first = false;
			} else {
				arr[i++] = BCD (load);
			}

			load = "";
			
		} else {
			load.append(to_string(high));
		}

		if (low > 9) {
			
			tmp = (low + 55);
			load.push_back(tmp);

			if (first) {
				cout << endl << "Vytvarim pole BCD cisel o delce: " << load << endl;
				n = BCD(load).getValue();
				arr = new BCD[n];
				first = false;
			} else {
				arr[i++] = BCD(load);
			}

			load = "";

		} else {
			load.append(to_string(low));
		}
	}
	
	MergeSort(desc, arr, n);

	ret.arr = arr;
	ret.length = n;
	return ret;
}

void load1(Param *p) {
	ret1 = loadFile(p->desc, p->file);
}

void load2(Param *p) {
	ret2 = loadFile(p->desc, p->file);
}

int main(int argc, char *argv[]) {

	if (argc != 3) {
		cout << "Nespravny pocet argumentu." << endl;
		getchar();
		return -1;
	}

	if (!strcmp(argv[2], "v") && !strcmp(argv[2], "s")) {
		cout << "Nespravne zadane argumenty. Argumenty musi byt ve tvaru: <nazev souboru> v nebo <nazev souboru> s." << endl;
		getchar();
		return -1;
	} 

	bool desc = false;

	if (strcmp(argv[2], "s")) {
		desc = true;
	}

	Param param1 = { string(argv[1]).append(".1"), desc };
	Param param2 = { string(argv[1]).append(".2"), desc };

	string file = argv[1];

	thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)load1, &param1, 0, NULL);
	thread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)load2, &param2, 0, NULL);

	WaitForSingleObject(thread1, INFINITE);
	cout << endl << "1. soubor setrizen! " << endl;

	WaitForSingleObject(thread2, INFINITE);
	cout << endl << "2. soubor setrizen! " << endl;

	MergeToFile(desc, file, ret1.arr, ret1.length, ret2.arr, ret2.length);
	cout << endl<< "Setrizene cisla byly slouceny do souboru." << endl;
	
	CloseHandle(thread1);
	CloseHandle(thread2);

	cout << endl << "Pro ukonceni stisknete libovolnou klavesu." << endl;

	getchar();
	return 0;
}