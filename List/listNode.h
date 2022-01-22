//
// Created by SGX on 2022/1/22.
//

#ifndef LIST_LISTNODE_H
#define LIST_LISTNODE_H


typedef int Rank;
#define ListNodePosi(T) ListNode<T>*  //列表结点位置

template <typename T> struct ListNode {         //列表结点的模板类T属于是结点？
    T data;
    ListNodePosi(T) pred; ListNodePosi(T) succ;     //前驱结点和后继结点

    ListNode(){};
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
        :data(e), pred(p), succ(s) {}

    ListNodePosi(T) insertAsPred (T const &e);

    ListNodePosi(T) insertAsSucc (T const &e);
};

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred (T const&e ) {
    ListNodePosi(T) x = new ListNode (e, pred, this);       //新建的结点的前驱结点就是this的前驱，后继就是this，因此这就是this的前驱节点了
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
