//
// Created by SGX on 2022/1/11.
//

#include "MyVector.h"

//ʵ�ֽӿ�

//ʵ�������㷨
template <typename T>
void Vector<T>::expand() {
    if ( _size < _capacity) return;  //û�дﵽ����������������
    if( _capacity < DEAULT_CAPACITY) _capacity = DEAULT_CAPACITY;
    T *old_elem = _elem;            //����ԭ�������ݵ�old�У� ���շ��صĻ���ԭ����_elem��������_elem��������ռ�
    _elem = new T[_capacity <<= 1];          //����
    for (int i = 0; i < _size; i++) {   //ԭ��һ����_size ���ڴ�
        _elem[i] = old_elem[i];
    }
    delete [] old_elem;
}

template <typename T>
void Vector<T>::copyFrom(const T *A, Rank low, Rank high) {
    //[low, high)
    _elem = new T[_capacity = 2 * (high - low)];
    _size = 0;      //��ʼ��Ԫ�ظ�����_size
    while (low < high) {
        _elem[_size ++ ] = A[low ++];
    }
}


