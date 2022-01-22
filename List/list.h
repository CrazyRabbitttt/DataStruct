//
// Created by SGX on 2022/1/22.
//

#include "listNode.h"
#ifndef LIST_LIST_H
#define LIST_LIST_H


template <typename T> class List {      //列表的模板类
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;            //规模，头哨兵结点，尾哨兵结点
protected:
    void init();        //列表创建时候的初始化
    void clear();
    //复制列表中自位置p起的n项
    ListNodePosi(T) merge ( ListNodePosi(T), int, List<T> &, ListNodePosi(T), int ); //归并
    void mergeSort ( ListNodePosi(T) &, int ); //对从p开始连续的n个节点归并排序
    void selectionSort ( ListNodePosi(T), int ); //对从p开始连续的n个节点选择排序
    void insertionSort ( ListNodePosi(T), int ); //对从p开始连续的n个节点插入排序
    void radixSort(ListNodePosi(T), int); //对从p开始连续的n个节点基数排序
    void copyNodes ( ListNodePosi(T), int );
public:
// 构造函数
    List() { init(); } //默认
    List ( List<T> const& L ); //整体复制列表L
    List ( List<T> const& L, Rank r, int n ); //复制列表L中自第r项起的n项
    List ( ListNodePosi(T) p, int n ); //复制列表中自位置p起的n项
// 析构函数
    ~List(); //释放（包含头、尾哨兵在内的）所有节点
// 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return _size <= 0; } //判空
    T& operator[] ( Rank r ) const; //重载，支持循秩访问（效率低）
    ListNodePosi(T) first() const { return header->succ; } //首节点位置
    ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
    bool valid ( ListNodePosi(T) p ) //判断位置p是否对外合法
    { return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL
    ListNodePosi(T) find ( T const& e ) const //无序列表查找
    { return find ( e, _size, trailer ); }
    ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const; //无序区间查找
    ListNodePosi(T) search ( T const& e ) const //有序列表查找
    { return search ( e, _size, trailer ); }
    ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const; //有序区间查找
    ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n ); //在p及其n-1个后继中选出最大者
    ListNodePosi(T) selectMax() { return selectMax ( header->succ, _size ); } //整体最大者
// 可写访问接口
    ListNodePosi(T) insertAsFirst ( T const& e ); //将e当作首节点插入
    ListNodePosi(T) insertAsLast ( T const& e ); //将e当作末节点插入
    ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e ); //将e当作p的后继插入（After）
    ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e ); //将e当作p的前驱插入（Before）
    T remove ( ListNodePosi(T) p ); //删除合法位置p处的节点,返回被删除节点
    void merge ( List<T> & L ) { merge ( header->succ, _size, L, L.header->succ, L._size ); } //全列表归并
    void sort ( ListNodePosi(T) p, int n ); //列表区间排序
    void sort() { sort ( first(), _size ); } //列表整体排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置（习题）
// 遍历
    void traverse ( void (* ) ( T& ) ); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    template <typename VST> //操作器
    void traverse ( VST& ); //遍历，依次实施visit操作（函数对象，可全局性修改）


};

template <typename T> void List<T>::init() {        //列表的初始化
    header = new ListNode<T>;       //创建头部的哨兵结点
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = nullptr;
    trailer->pred = header; trailer->succ = nullptr;
    _size = 0;      //没有规模
}

//在前面插入一个结点
template <typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const & e) {
    //insertBefore
    _size ++;
    return p->insertAsPred(e);          //把e当做前驱结点进行插入
}

//在后面插入节点
template <typename T> ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const & e) {
    //insertAfter
    _size ++;
    return p->insertAsSucc;
}
//在最后面插入节点
template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const & e) {
    //将e作为末尾结点插入到list最后面
    _size ++;
    return trailer->insertAsPred(e);
}
//在最前面插入结点
template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const & e) {
    _size++;
    return header->insertAsSucc;
}

//用一个链表初始化另外一个链表，从结点p开始复制n位
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();         //this->init()
    while (n--) {
        insertAsLast(p -> data);
        p = p -> succ;      //p指针向后移动
    }
}

//将结点p从List中删除掉，并且返回结点的内容
template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
    T value = p -> data;
    p -> pred -> succ = p -> succ;
    p -> succ -> pred = p -> pred;
    delete p;
    _size --;
    return value ;
}


//清除List列表中除了哨兵结点的内容
template <typename T>
void List<T>::clear() {
    while (_size) remove(header -> succ);       //反复删除首结点（哨兵的下一个，直到_size == 0）
}

//析构函数
template <typename T> List<T>::~List<T>() {
    clear();        //清空列表的内容
    delete header;delete trailer;       //释放头结点，尾结点
}






#endif //LIST_LIST_H
