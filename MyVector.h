//
// Created by SGX on 2022/1/11.
//

#ifndef DATASTRUCT_STUDY_MYVECTOR_H
#define DATASTRUCT_STUDY_MYVECTOR_H
#include <cstdio>
//用于实现清华数据结构中的vector
typedef int Rank;       //秩
#define DEAULT_CAPACITY 3
template<typename T> class Vector{
public:
    Rank _size;
    int _capacity;
    T *_elem;       //规模，容量，数据区,头指针？
    void copyFrom ( T const* A, Rank low, Rank high ); //复制数组区间A[lo, hi)
    void expand(); //空间不足时扩容
    bool bubble ( Rank lo, Rank hi ); //扫描交换
    void shrink();      //装填的因子过小_size不足_capacity >> 2
    int disordered();
public:
    Vector(int c=DEAULT_CAPACITY,int s= 0,T v=0)
    {
        _elem = new T[_capacity = c];
        //初始化所有的元素为v = 0
        for (_size = 0; _size < s; _size++) _elem[_size] = v;
    }
    //数组的整体赋值 0 - n
    Vector(T const*A, Rank n) {
        copyFrom(A, 0 ,n);//0到n赋值到vector中
    }
    //数组的区间赋值 low - high
    Vector(T const*A, Rank low, Rank high) {
        copyFrom(A, low, high);
    }
    //向量的整体赋值
    Vector(Vector<T> const &V) {
        copyFrom(V._elem, 0, V._size);
    }
    //向量的区间赋值
    Vector(Vector<T> &V, Rank low, Rank high) {
        copyFrom(V._elem, low, high);
    }
    //析构函数
    ~Vector() {
        delete [] _elem;
    }

    //只读的接口
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    Rank capacity() const { return _capacity;}//容量
    Rank find(T const& e, Rank low, Rank high);//区间查找
    Rank search(T const &e, Rank low, Rank high) const; //有序的区间查找

    //可以进行访问操作的接口

    T & operator[](Rank r);             //使用‘【】’进行vector的访问
    Rank insert(Rank r, T const &e);    //向下标为r的位置插入e
    int remove(Rank low, Rank high);    //删除[low,high)的元素
    T remove(Rank r);                   //删除的是一个元素
    int deduplicate();                  //无序去重,返回删除元素的个数
    int uniquify();                     //有序去重
    //遍历
    void show_list();

    void traverse(void (* ) (T& ));                     //使用函数指针遍历，只读或者局部性修改
    template <typename VST> void traverse ( VST& );     //遍历（使用函数对象，可全局性修改）

};



















#endif //DATASTRUCT_STUDY_MYVECTOR_H
