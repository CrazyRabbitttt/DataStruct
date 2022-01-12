//
// Created by lenovo on 2022/1/11.
//

#ifndef DATASTRUCT_STUDY__MYVECTOR_H
#define DATASTRUCT_STUDY__MYVECTOR_H
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

template <typename T>
void Vector<T>::show_list() {
    for (int i = 0; i < _size; i++) {
        printf("%d ", _elem[i]);
    }
}

template <typename T>   //重载[]
T & Vector<T>::operator[] (Rank r) {return _elem[r];}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e) {    // 0 <= r <= size
    expand();
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i - 1];        //向后移动一位
    }
    _elem[r] = e;
    _size ++;
    return r;
}

template <typename T>
void Vector<T>::shrink() {
    //按照是否达到_capacity >> 2为界限
    if (_capacity < DEAULT_CAPACITY << 1) return ;      //本身容量就不算很大(还不到两倍的default) 就return
    if (_size << 2 > _capacity) return;                 //大于四分之一，就不收缩了
    T *old_elem = _elem;
    _elem = new T[_capacity >>= 1];                     //收缩为一半
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
    //将low后面的进行丢弃
    _size = low;
    shrink();
    return high - low;
}

template <typename T>
T Vector<T>::remove(Rank r) {
    //删除的是一个元素[r, r + 1)
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
Rank Vector<T>::find(const T &e, Rank low, Rank high) {
    //返回的是查找的元素下标
    while ((low < high--) && (e != _elem[high]));
    return high;        //如果hi < low就代表没有找到，用户自定义程序判断就行
}


template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    //从1开始查找前面的数是否有相同的
    for (int i = 1; i < _size; i++) {
        if (find(_elem[i], 0, i) < 0) continue;    //在[0,i)没找到一样的就删除
        remove(i);  //找到一样的就删除当前的元素
    }
    return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify() {
    //有序版本的去重,双指针算法
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
void Vector<T>::traverse(void (* visit)(T &)) {         //调用函数指针进行遍历
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template<typename T>
struct visit{
            void operator () (T &e) {e++;}
        };

template <typename T> template <typename VST> //元素类型、操作器
void Vector<T>::traverse ( VST& visit ) //借助函数对象机制
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //遍历向量

template<typename T>
int Vector<T>::disordered() {
    int n = 0;          //逆序就计数
    for (int i = 1; i < _size; i++) {
        if (_elem[i - 1] > _elem[i]) n++;
    }
    return n;
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank low, Rank high) const {
    //用二分或者是斐波那契查找
    return (rand() % 2) ? binSearch(_elem, e, low, high) : fibSearch(_elem, e, low, high);
}










#endif //DATASTRUCT_STUDY__MYVECTOR_H
