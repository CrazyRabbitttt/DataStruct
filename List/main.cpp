#include <iostream>
#include "list.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "大家自行调用接口调试好吧:)\n" << std::endl;
    List<int> l;
    l.insertAsLast(5);
    l.insertAsLast(6);
    l.insertAsLast(2);
    l.insertAsLast(3);
    l.insertAsLast(9);
    std::cout << "容量是： " << l.size() << std::endl;
   /* List<int> l2;
    ListNodePosi(int) point = l.header -> succ;
    l2.copyNodes(point,3);
    std::cout << "l2的容量是：" << l2.size() << std::endl;*/
    return 0;
}
