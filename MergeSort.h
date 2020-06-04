/* MergeSort.h */
#ifndef MERGESORT_H_

#define MERGESORT_H_

#include <fstream>
#include <string>
#include "BCD.h"

using namespace std;

template<class T>
void Merge(bool desc, T A[], T L[], int nL, T R[], int nR);

template<class T>
void MergeSort(bool desc, T A[], int n);

template<class T>
void MergeToFile(bool desc, string filename, T L[], int nL, T R[], int nR);

#endif // MERGESORT_H_

