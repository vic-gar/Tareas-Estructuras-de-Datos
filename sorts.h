/*
 * sorts.h
 *
 *  	Created on: 09/09/2025
 *      Author: Víctor A. García 
 */

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>

template <class T>
class Sorts {
    private: 
        void swap(std::vector<T>&, int, int);
        void copyArr(std::vector<T>&, std::vector<T>&, int, int);
        void mergeArr(std::vector<T>&, std::vector<T>&, int, int, int);
        void mergeDivide(std::vector<T>&, std::vector<T>&, int, int);
		int busqBinaria_aux(const std::vector<T>&, int, int, int);
    public:
        void ordenaSeleccion(std::vector<T>&);
        void ordenaBurbuja(std::vector<T>&);
        void ordenaMerge(std::vector<T>&);
		int busqSecuencial(const std::vector<T>&, int);
		int busqBinaria(const std::vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &source) {
	std::vector<T> v(source);
	int pos;

	for (int i = v.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (v[j] > v[pos]) {
				pos = j;
			}
		}

		if (pos != i) {
			swap(v, i, pos);
		}
	}
	source.swap(v);
}

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &source) {
	std::vector<T> v(source);

	for (int i = v.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (v[j] > v[j + 1]) {
				swap(v, j, j + 1);
			}
		}
	}

	source.swap(v);
}

template <class T>
void Sorts<T>::copyArr(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArr(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid &&j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeDivide(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeDivide(A, B, low, mid);
	mergeDivide(A, B, mid + 1, high);
	mergeArr(A, B, low, mid, high);
	copyArr(A, B, low, high);
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &source) {
	std::vector<T> v(source);
	std::vector<T> tmp(v.size());

	mergeDivide(v, tmp, 0, v.size() - 1);

	source.swap(v);
}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &source, int val) {
	std::vector<T> v(source);

	    for (int i = 0; i < v.size(); i++){
        	if (v[i] == val){
            return i;
        }
    }
    return -1;
}


template <class T>
int Sorts<T>::busqBinaria_aux(const std::vector<T> &v, int low, int high, int val) {
	int mid;

	if (low > high){
		return -1;
	}

	if (low <= high) {
		mid = (high + low) / 2;
		if (val == v[mid]) {
			return mid;
		} else if (val < v[mid]) {
			return busqBinaria_aux(v, low, mid - 1, val);
		} else if (val > v[mid]) {
			return busqBinaria_aux(v, mid + 1, high, val);
		}
	}
	return low;
}

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &source, int val) {
	std::vector<T> v(source);

	return busqBinaria_aux(v, 0, v.size() - 1, val);
}

#endif