#include <iostream>
#include "list.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "������е��ýӿڵ��Ժð�:)\n" << std::endl;
    List<int> l;
    l.insertAsLast(5);
    l.insertAsLast(6);
    l.insertAsLast(2);
    l.insertAsLast(3);
    l.insertAsLast(9);
    std::cout << "�����ǣ� " << l.size() << std::endl;
   /* List<int> l2;
    ListNodePosi(int) point = l.header -> succ;
    l2.copyNodes(point,3);
    std::cout << "l2�������ǣ�" << l2.size() << std::endl;*/
    return 0;
}
