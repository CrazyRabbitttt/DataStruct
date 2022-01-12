//
// Created by lenovo on 2022/1/11.
//

#ifndef DATASTRUCT_STUDY__MYVECTOR_H
#define DATASTRUCT_STUDY__MYVECTOR_H
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

template <typename T>
void Vector<T>::show_list() {
    for (int i = 0; i < _size; i++) {
        printf("%d ", _elem[i]);
    }
}

template <typename T>   //����[]
T & Vector<T>::operator[] (Rank r) {return _elem[r];}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e) {    // 0 <= r <= size
    expand();
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i - 1];        //����ƶ�һλ
    }
    _elem[r] = e;
    _size ++;
    return r;
}

template <typename T>
void Vector<T>::shrink() {
    //�����Ƿ�ﵽ_capacity >> 2Ϊ����
    if (_capacity < DEAULT_CAPACITY << 1) return ;      //���������Ͳ���ܴ�(������������default) ��return
    if (_size << 2 > _capacity) return;                 //�����ķ�֮һ���Ͳ�������
    T *old_elem = _elem;
    _elem = new T[_capacity >>= 1];                     //����Ϊһ��
    for (int i = 0; i < _size; i++) {
        _elem[i] = old_elem[i];
    }
    delete [] old_elem;
}

template <typename T>
Rank Vector<T>::remove(Rank low, Rank high) {
    if (low == high) return 0;
    while (high < _size) {
        _elem[low ++] = _elem[high ++];
    }
    //��low����Ľ��ж���
    _size = low;
    shrink();
    return high - low;
}

template <typename T>
T Vector<T>::remove(Rank r) {
    //ɾ������һ��Ԫ��[r, r + 1)
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
Rank Vector<T>::find(const T &e, Rank low, Rank high) {
    //���ص��ǲ��ҵ�Ԫ���±�
    while ((low < high--) && (e != _elem[high]));
    return high;        //���hi < low�ʹ���û���ҵ����û��Զ�������жϾ���
}


template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    //��1��ʼ����ǰ������Ƿ�����ͬ��
    for (int i = 1; i < _size; i++) {
        if (find(_elem[i], 0, i) < 0) continue;    //��[0,i)û�ҵ�һ���ľ�ɾ��
        remove(i);  //�ҵ�һ���ľ�ɾ����ǰ��Ԫ��
    }
    return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify() {
    //����汾��ȥ��,˫ָ���㷨
    Rank i = 0, j = 0;
    while (++j < _size) {
        if (_elem[j] != _elem[i]) {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();
    return j - i;
}

template <typename T>
void Vector<T>::traverse(void (* visit)(T &)) {         //���ú���ָ����б���
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template<typename T>
struct visit{
            void operator () (T &e) {e++;}
        };

template <typename T> template <typename VST> //Ԫ�����͡�������
void Vector<T>::traverse ( VST& visit ) //���������������
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //��������

template<typename T>
int Vector<T>::disordered() {
    int n = 0;          //����ͼ���
    for (int i = 1; i < _size; i++) {
        if (_elem[i - 1] > _elem[i]) n++;
    }
    return n;
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank low, Rank high) const {
    //�ö��ֻ�����쳲���������
    return (rand() % 2) ? binSearch(_elem, e, low, high) : fibSearch(_elem, e, low, high);
}










#endif //DATASTRUCT_STUDY__MYVECTOR_H
