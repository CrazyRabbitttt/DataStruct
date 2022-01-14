//
// Created by SGX on 2022/1/11.
//

#ifndef DATASTRUCT_STUDY_MYVECTOR_H
#define DATASTRUCT_STUDY_MYVECTOR_H
#include <cstdio>
//����ʵ���廪���ݽṹ�е�vector
typedef int Rank;       //��
#define DEAULT_CAPACITY 3
template<typename T> class Vector{
public:
    Rank _size;
    int _capacity;
    T *_elem;       //��ģ��������������,ͷָ�룿
    void copyFrom ( T const* A, Rank low, Rank high ); //������������A[lo, hi)
    void expand(); //�ռ䲻��ʱ����
    bool bubble ( Rank lo, Rank hi ); //ɨ�轻��
    void shrink();      //װ������ӹ�С_size����_capacity >> 2
    int disordered();
    void bubbleSort ( Rank lo, Rank hi ); //���������㷨
    Rank max ( Rank lo, Rank hi ); //ѡȡ���Ԫ��
    void selectionSort ( Rank lo, Rank hi ); //ѡ�������㷨
    void merge ( Rank lo, Rank mi, Rank hi ); //�鲢�㷨
    void mergeSort ( Rank lo, Rank hi ); //�鲢�����㷨
    void heapSort ( Rank lo, Rank hi ); //�������Ժ�����ȫ�ѽ��⣩
    Rank partition ( Rank lo, Rank hi ); //��㹹���㷨
    void quickSort ( Rank lo, Rank hi ); //���������㷨
    void shellSort ( Rank lo, Rank hi ); //ϣ�������㷨
public:
    Vector(int c=DEAULT_CAPACITY,int s= 0,T v=0)
    {
        _elem = new T[_capacity = c];
        //��ʼ�����е�Ԫ��Ϊv = 0
        for (_size = 0; _size < s; _size++) _elem[_size] = v;
    }
    //��������帳ֵ 0 - n
    Vector(T const*A, Rank n) {
        copyFrom(A, 0 ,n);//0��n��ֵ��vector��
    }
    //��������丳ֵ low - high
    Vector(T const*A, Rank low, Rank high) {
        copyFrom(A, low, high);
    }
    //���������帳ֵ
    Vector(Vector<T> const &V) {
        copyFrom(V._elem, 0, V._size);
    }
    //���������丳ֵ
    Vector(Vector<T> &V, Rank low, Rank high) {
        copyFrom(V._elem, low, high);
    }
    //��������
    ~Vector() {
        delete [] _elem;
    }

    //ֻ���Ľӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    Rank capacity() const { return _capacity;}//����
    Rank find(T const& e, Rank low, Rank high);//�������
    //Rank search(T const &e, Rank low, Rank high) const; //������������

    //���Խ��з��ʲ����Ľӿ�
    void sort(Rank low, Rank high);     //����Ľӿ�
    T & operator[](Rank r);             //ʹ�á�����������vector�ķ���
    Rank insert(Rank r, T const &e);    //���±�Ϊr��λ�ò���e
    int remove(Rank low, Rank high);    //ɾ��[low,high)��Ԫ��
    T remove(Rank r);                   //ɾ������һ��Ԫ��
    int deduplicate();                  //����ȥ��,����ɾ��Ԫ�صĸ���
    int uniquify();                     //����ȥ��
    //����
    void show_list();

    void traverse(void (* ) (T& ));                     //ʹ�ú���ָ�������ֻ�����߾ֲ����޸�
    template <typename VST> void traverse ( VST& );     //������ʹ�ú������󣬿�ȫ�����޸ģ�

};



















#endif //DATASTRUCT_STUDY_MYVECTOR_H
