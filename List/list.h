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

template <typename T>
ListNodePosi(T) List<T>::find(const T & e, int n, ListNodePosi(T) p) const {        //在n个前驱节点中进行查找是否有匹配结点p的结点
    while (n--) {
        if (e == (p = p -> pred) -> data) return p;
    }
    return NULL;        //查找失败，返回空指针
}

template <typename T>
int List<T>::deduplicate() {        //无序去重，返回去掉的重复元素的个数
    int old_size = _size;
    if (old_size < 2) return 0;     //至少数量是2才能去重
    //基本的思路是查找第r个数前面是否是有和他重复的结点，如果有就去除掉前面重复的，然后curnode 指向下一个继续去重
    ListNodePosi(T) p = first();        //首结点开始
    Rank index = 1;                     //index用于find函数中的n,就是查找前面n个结点
    while (p = (p -> succ) != trailer) {
        ListNodePosi(T) node = find(p->data, index, p);
        node ? remove(node) : index++;          //如果查到重复的节点了就删除，否则index自加
    }
    return old_size - _size;
}

template <typename T>
int List<T>::uniquify() {       //有序列表的唯一化
    if (_size < 2) return 0;
    int old_size = _size;
    ListNodePosi(T) p = first();            //p用于确定最终的所有的结点：p指向的一定是最终保留的结点
    ListNodePosi(T) node = p -> succ;       //node是用于移动和确定移除的结点
    while (trailer != (node = p -> succ)) {
        node -> data == p -> data ? remove(node) : p = node;
    }
    return old_size - _size;
}
template <typename T>
ListNodePosi(T) List<T>::search(const T & e, int n, ListNodePosi(T) p) const{               //同find类似，在前n个前驱结点中查找不大于p的结点
    ListNodePosi(T) node = p -> pred;
    while (n --) {
        if ((p = p -> pred) -> data <= e) break;
    }
    return p;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {      //查找从结点p开始的后面n个节点中，最大的节点
    ListNodePosi(T) maxNode = p;
    ListNodePosi(T) curNode = p;
    while (n > 1) {
        if ((curNode = curNode -> succ) -> data >= maxNode -> data) maxNode = curNode;
    }
    return maxNode;
}

template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
    //从p开始向后n个结点进行选择排序
    ListNodePosi(T) head = p -> pred;       //排序的区间(head, tail) ,全部都是开区间
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; ++i) tail = tail->succ;      //末尾哨兵结点，开区间，取不到tail  ： (head, tail)
    while (n > 1) {
        //注意理解这一个函数（一定要明确区间的范围是什么，一直在变化的），首先选出待排区间的最大值，在原位置删除掉然后插入到待排区间末尾（那就是哨兵tail的前面了）
        insertB(tail, remove(selectMax(head -> succ,n)));
        tail = tail -> pred;        //待排区间收缩，哨兵前移
        n--;        //进行n - 1次的排列就行
    }
}


template <typename T> //对列表中起始于位置p、宽度为n的区间做插入排序
void List<T>::insertionSort ( ListNodePosi(T) p, int n ) { //valid(p) && rank(p) + n <= size
    for ( int r = 0; r < n; r++ ) { //逐一为各节点
        insertA ( search ( p->data, r, p ), p->data ); //查找适当的位置并插入
        p = p->succ; remove ( p->pred ); //转向下一节点
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
