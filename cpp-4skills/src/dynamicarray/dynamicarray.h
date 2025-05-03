/*
 * dynamicarracy.h
 *
 *  Created on: May 2, 2025
 *      Author: 5miiss
 */

#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_


#include <cstdlib>
#include <iostream>
using namespace std;
template<class T>
class DynamicArray {

	int currentSize;
	int totalSize;
	T **arr;
private:
	void ensureCapacity() {
		if (this->currentSize < this->totalSize) {
			return;
		}
		this->totalSize *= 2;
		T **newArr = (T**) malloc(sizeof(T*) * this->totalSize);
		for (int i = 0; i < this->currentSize; i++) {
			newArr[i] = this->arr[i];
		}
		for (int i = this->currentSize; i < this->totalSize; i++) {
			newArr[i] = nullptr;
		}
		T **temp = this->arr;
		free(temp);
		this->arr = newArr;
	}
public:
	DynamicArray() {
		this->totalSize = 100;
		this->currentSize = 0;
		this->arr = (T**) malloc(sizeof(T*) * this->totalSize);
		for (int i = this->currentSize; i < this->totalSize; i++) {
			this->arr[i] = nullptr;
		}
	}
	DynamicArray(int _totalSize) {
		this->totalSize = _totalSize;
		this->currentSize = 0;
		this->arr = (T**) malloc(sizeof(T*) * this->totalSize);
		for (int i = this->currentSize; i < this->totalSize; i++) {
			this->arr[i] = nullptr;
		}
	}
	
	~DynamicArray() {
		cout << "destructor called for dynamic array!!!! at current size! " << this->currentSize << endl;
		for (int i = 0; i < this->totalSize; i++) {
			if (this->arr[i] == nullptr) {
				break;
			}
			free(this->arr[i]);
			this->arr[i] = nullptr;
		}
		free(this->arr);
		this->arr = nullptr;
	}
	int getSize() {
		return this->currentSize;
	}
	T* get(int i) {
		if (i >= this->currentSize) {
			return nullptr;
		}
		return arr[i];
	}
	T** getArr() {
		return this->arr;
	}

	void push_back(T *val){
		this->ensureCapacity();
		// this->arr[this->currentSize] = (T *) malloc(sizeof(T));
		this->arr[this->currentSize] = val;
		this->currentSize++;
	}
	void deleteByEntry(T *val) {
		cout << "deleting value !! " << endl;
		int idx = -1;
		for (int i = 0; i < this->currentSize; i++)
		{
			if (this->arr[i] == val)
			{
				idx = i;
				break;
			}
		}
		while (idx != -1 && idx != this->currentSize - 1) {
			this->arr[idx] = this->arr[idx + 1];
			idx++;
		}
		free(this->arr[this->currentSize]);
		this->arr[this->currentSize] = nullptr;
		this->currentSize--;


	}
	T* remove_back();
	void push_front(T* val);
	T* remove_front();
	void print();
};

template<class T>
T* DynamicArray<T>::remove_back(){
	T *temp = this->arr[this->currentSize];
	// free(this->arr[this->currentSize]);
	this->arr[this->currentSize] = nullptr;
	this->currentSize--;
	return temp;
}
template<class T>
void DynamicArray<T>::push_front(T* val){
	this->ensureCapacity();
	for (int i = this->currentSize; i > 0; i--) {
		this->arr[i] = this->arr[i - 1];
	}
	this->arr[0] = val;
	this->currentSize++;
}
template<class T>
T* DynamicArray<T>::remove_front(){
	T *temp = this->arr[0];
	for (int i = 0; i < this->currentSize - 1; i++) {
		this->arr[i] = this->arr[i + 1];
	}
	this->currentSize--;
	this->arr[this->currentSize] = nullptr;
	return temp;
}

template<class T>
void DynamicArray<T>::print(){
	for (int i = 0; i < this->currentSize; i++) {
		cout << *this->arr[i] << ",   ";
	}
	cout << endl;
}




#endif /* DYNAMICARRAY_DYNAMICARRACY_H_ */
