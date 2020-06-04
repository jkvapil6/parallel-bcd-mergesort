
#include "MergeSort.h"

template<class T>
void Merge(bool desc, T A[], T L[], int nL, T R[], int nR) {

	int i = 0, j = 0, k = 0;
	while (i < nL && j < nR) {
		if (desc) {
			if (L[i] < R[j]) {
				A[k++] = L[i++];
			} else {
				A[k++] = R[j++];
			}
		} else {
			if (L[i] > R[j]) {
				A[k++] = L[i++];
			} else {
				A[k++] = R[j++];
			}
		}
	}
	while (i < nL) {
		A[k++] = L[i++];
	}
	while (j < nR) {
		A[k++] = R[j++];
	}
}


template<class T>
void MergeSort(bool desc, T A[], int n) {

	int mid;
	T *L, *R;
	if (n < 2) return;
	mid = n / 2;

	L = new T[mid];
	R = new T[n - mid];

	for (int i = 0; i < mid; i++) {
		L[i] = A[i];
	}
	for (int i = mid; i < n; i++) {
		R[i - mid] = A[i];
	}
	MergeSort(desc, L, mid);
	MergeSort(desc, R, n - mid);
	Merge(desc, A, L, mid, R, n - mid);
	delete[] L;
	delete[] R;
}

inline void putBCDToFile(basic_ofstream<unsigned char> &outfile, BCD tmp) {

	int len = tmp.ToString().length() / 2;
	unsigned char * binTemp = tmp.toBinary();

	for (int x = 0; x < len; x++) {
		outfile.put(binTemp[x]);
	}
}

template<class T>
void MergeToFile(bool desc, string filename, T L[], int nL, T R[], int nR) {

	basic_ofstream<unsigned char> outfile;
	BCD tmp(to_string(nL + nR).append("C"));

	int i = 0, j = 0, k = 0;
	
	outfile.open(filename, ios::out | ios::binary);
	putBCDToFile(outfile, tmp);
	
	while (i < nL && j < nR) {
		if (desc) {
			if (L[i] < R[j]) {
				putBCDToFile(outfile, L[i++]);
			} else {
				putBCDToFile(outfile, R[j++]);
			}
		} else {
			if (L[i] > R[j]) {
				putBCDToFile(outfile, L[i++]);
			} else {
				putBCDToFile(outfile, R[j++]);
			}
		}
	}
	while (i < nL) {
		putBCDToFile(outfile, L[i++]);
	}
	while (j < nR) {
		putBCDToFile(outfile, R[j++]);
	}
	
	outfile.close();
}