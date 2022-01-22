//
// Created by SGX on 2022/1/22.
//

#ifndef LIST_LISTNODE_H
#define LIST_LISTNODE_H


typedef int Rank;
#define ListNodePosi(T) ListNode<T>*  //�б���λ��

template <typename T> struct ListNode {         //�б����ģ����T�����ǽ�㣿
    T data;
    ListNodePosi(T) pred; ListNodePosi(T) succ;     //ǰ�����ͺ�̽��

    ListNode(){};
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
        :data(e), pred(p), succ(s) {}

    ListNodePosi(T) insertAsPred (T const &e);

    ListNodePosi(T) insertAsSucc (T const &e);
};

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred (T const&e ) {
    ListNodePosi(T) x = new ListNode (e, pred, this);       //�½��Ľ���ǰ��������this��ǰ������̾���this����������this��ǰ���ڵ���
    this->pred->succ = x;
    this->pred = x;
    return x;
}


template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc (T const & e) {
    ListNodePosi(T) x = new ListNode(e, this, this->succ);
    succ->pre = x; succ = x;
    return x;
}



#endif //LIST_LISTNODE_H
