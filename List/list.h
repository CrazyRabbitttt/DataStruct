//
// Created by SGX on 2022/1/22.
//

#include "listNode.h"
#ifndef LIST_LIST_H
#define LIST_LIST_H


template <typename T> class List {      //�б��ģ����
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;            //��ģ��ͷ�ڱ���㣬β�ڱ����
protected:
    void init();        //�б���ʱ��ĳ�ʼ��
    void clear();
    //�����б�����λ��p���n��
    ListNodePosi(T) merge ( ListNodePosi(T), int, List<T> &, ListNodePosi(T), int ); //�鲢
    void mergeSort ( ListNodePosi(T) &, int ); //�Դ�p��ʼ������n���ڵ�鲢����
    void selectionSort ( ListNodePosi(T), int ); //�Դ�p��ʼ������n���ڵ�ѡ������
    void insertionSort ( ListNodePosi(T), int ); //�Դ�p��ʼ������n���ڵ��������
    void radixSort(ListNodePosi(T), int); //�Դ�p��ʼ������n���ڵ��������
    void copyNodes ( ListNodePosi(T), int );
public:
// ���캯��
    List() { init(); } //Ĭ��
    List ( List<T> const& L ); //���帴���б�L
    List ( List<T> const& L, Rank r, int n ); //�����б�L���Ե�r�����n��
    List ( ListNodePosi(T) p, int n ); //�����б�����λ��p���n��
// ��������
    ~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
// ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return _size <= 0; } //�п�
    T& operator[] ( Rank r ) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
    ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
    ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
    bool valid ( ListNodePosi(T) p ) //�ж�λ��p�Ƿ����Ϸ�
    { return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL
    ListNodePosi(T) find ( T const& e ) const //�����б����
    { return find ( e, _size, trailer ); }
    ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const; //�����������
    ListNodePosi(T) search ( T const& e ) const //�����б����
    { return search ( e, _size, trailer ); }
    ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const; //�����������
    ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n ); //��p����n-1�������ѡ�������
    ListNodePosi(T) selectMax() { return selectMax ( header->succ, _size ); } //���������
// ��д���ʽӿ�
    ListNodePosi(T) insertAsFirst ( T const& e ); //��e�����׽ڵ����
    ListNodePosi(T) insertAsLast ( T const& e ); //��e����ĩ�ڵ����
    ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e ); //��e����p�ĺ�̲��루After��
    ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e ); //��e����p��ǰ�����루Before��
    T remove ( ListNodePosi(T) p ); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
    void merge ( List<T> & L ) { merge ( header->succ, _size, L, L.header->succ, L._size ); } //ȫ�б�鲢
    void sort ( ListNodePosi(T) p, int n ); //�б���������
    void sort() { sort ( first(), _size ); } //�б���������
    int deduplicate(); //����ȥ��
    int uniquify(); //����ȥ��
    void reverse(); //ǰ���ã�ϰ�⣩
// ����
    void traverse ( void (* ) ( T& ) ); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> //������
    void traverse ( VST& ); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�


};

template <typename T> void List<T>::init() {        //�б�ĳ�ʼ��
    header = new ListNode<T>;       //����ͷ�����ڱ����
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = nullptr;
    trailer->pred = header; trailer->succ = nullptr;
    _size = 0;      //û�й�ģ
}

//��ǰ�����һ�����
template <typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const & e) {
    //insertBefore
    _size ++;
    return p->insertAsPred(e);          //��e����ǰ�������в���
}

//�ں������ڵ�
template <typename T> ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const & e) {
    //insertAfter
    _size ++;
    return p->insertAsSucc;
}
//����������ڵ�
template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const & e) {
    //��e��Ϊĩβ�����뵽list�����
    _size ++;
    return trailer->insertAsPred(e);
}
//����ǰ�������
template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const & e) {
    _size++;
    return header->insertAsSucc;
}

//��һ�������ʼ������һ�������ӽ��p��ʼ����nλ
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();         //this->init()
    while (n--) {
        insertAsLast(p -> data);
        p = p -> succ;      //pָ������ƶ�
    }
}

template <typename T>
ListNodePosi(T) List<T>::find(const T & e, int n, ListNodePosi(T) p) const {        //��n��ǰ���ڵ��н��в����Ƿ���ƥ����p�Ľ��
    while (n--) {
        if (e == (p = p -> pred) -> data) return p;
    }
    return NULL;        //����ʧ�ܣ����ؿ�ָ��
}

template <typename T>
int List<T>::deduplicate() {        //����ȥ�أ�����ȥ�����ظ�Ԫ�صĸ���
    int old_size = _size;
    if (old_size < 2) return 0;     //����������2����ȥ��
    //������˼·�ǲ��ҵ�r����ǰ���Ƿ����к����ظ��Ľ�㣬����о�ȥ����ǰ���ظ��ģ�Ȼ��curnode ָ����һ������ȥ��
    ListNodePosi(T) p = first();        //�׽�㿪ʼ
    Rank index = 1;                     //index����find�����е�n,���ǲ���ǰ��n�����
    while (p = (p -> succ) != trailer) {
        ListNodePosi(T) node = find(p->data, index, p);
        node ? remove(node) : index++;          //����鵽�ظ��Ľڵ��˾�ɾ��������index�Լ�
    }
    return old_size - _size;
}

template <typename T>
int List<T>::uniquify() {       //�����б��Ψһ��
    if (_size < 2) return 0;
    int old_size = _size;
    ListNodePosi(T) p = first();            //p����ȷ�����յ����еĽ�㣺pָ���һ�������ձ����Ľ��
    ListNodePosi(T) node = p -> succ;       //node�������ƶ���ȷ���Ƴ��Ľ��
    while (trailer != (node = p -> succ)) {
        node -> data == p -> data ? remove(node) : p = node;
    }
    return old_size - _size;
}
template <typename T>
ListNodePosi(T) List<T>::search(const T & e, int n, ListNodePosi(T) p) const{               //ͬfind���ƣ���ǰn��ǰ������в��Ҳ�����p�Ľ��
    ListNodePosi(T) node = p -> pred;
    while (n --) {
        if ((p = p -> pred) -> data <= e) break;
    }
    return p;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {      //���Ҵӽ��p��ʼ�ĺ���n���ڵ��У����Ľڵ�
    ListNodePosi(T) maxNode = p;
    ListNodePosi(T) curNode = p;
    while (n > 1) {
        if ((curNode = curNode -> succ) -> data >= maxNode -> data) maxNode = curNode;
    }
    return maxNode;
}

template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
    //��p��ʼ���n��������ѡ������
    ListNodePosi(T) head = p -> pred;       //���������(head, tail) ,ȫ�����ǿ�����
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; ++i) tail = tail->succ;      //ĩβ�ڱ���㣬�����䣬ȡ����tail  �� (head, tail)
    while (n > 1) {
        //ע�������һ��������һ��Ҫ��ȷ����ķ�Χ��ʲô��һֱ�ڱ仯�ģ�������ѡ��������������ֵ����ԭλ��ɾ����Ȼ����뵽��������ĩβ���Ǿ����ڱ�tail��ǰ���ˣ�
        insertB(tail, remove(selectMax(head -> succ,n)));
        tail = tail -> pred;        //���������������ڱ�ǰ��
        n--;        //����n - 1�ε����о���
    }
}


template <typename T> //���б�����ʼ��λ��p�����Ϊn����������������
void List<T>::insertionSort ( ListNodePosi(T) p, int n ) { //valid(p) && rank(p) + n <= size
    for ( int r = 0; r < n; r++ ) { //��һΪ���ڵ�
        insertA ( search ( p->data, r, p ), p->data ); //�����ʵ���λ�ò�����
        p = p->succ; remove ( p->pred ); //ת����һ�ڵ�
    }
}

//�����p��List��ɾ���������ҷ��ؽ�������
template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
    T value = p -> data;
    p -> pred -> succ = p -> succ;
    p -> succ -> pred = p -> pred;
    delete p;
    _size --;
    return value ;
}


//���List�б��г����ڱ���������
template <typename T>
void List<T>::clear() {
    while (_size) remove(header -> succ);       //����ɾ���׽�㣨�ڱ�����һ����ֱ��_size == 0��
}

//��������
template <typename T> List<T>::~List<T>() {
    clear();        //����б������
    delete header;delete trailer;       //�ͷ�ͷ��㣬β���
}


#endif //LIST_LIST_H
