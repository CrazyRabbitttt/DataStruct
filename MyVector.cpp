//
// Created by SGX on 2022/1/11.
//

#include "MyVector.h"

//实现接口

//实现扩充算法
template <typename T>
void Vector<T>::expand() {
    if ( _size < _capacity) return;  //没有达到容量，不进行扩充
    if( _capacity < DEAULT_CAPACITY) _capacity = DEAULT_CAPACITY;
    T *old_elem = _elem;            //保存原来的内容到old中， 最终返回的还是原来的_elem，所以用_elem进行申请空间
    _elem = new T[_capacity <<= 1];          //扩容
    for (int i = 0; i < _size; i++) {   //原来一共有_size 个内存
        _elem[i] = old_elem[i];
    }
    delete [] old_elem;
}

template <typename T>
void Vector<T>::copyFrom(const T *A, Rank low, Rank high) {
    //[low, high)
    _elem = new T[_capacity = 2 * (high - low)];
    _size = 0;      //初始的元素个数是_size
    while (low < high) {
        _elem[_size ++ ] = A[low ++];
    }
}


