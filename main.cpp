#include <iostream>
#include "_MyVector.h"
using namespace std;



template <typename T>
void Test1() {
    Vector<T>v(8,8,2);
    Vector<T>a(12,4,3);
    cout << "v一的元素个数:" <<v.size() << endl;
    cout << "容量是:" << v.capacity() << endl;
    v.show_list();
    v.expand();
    cout << endl;
    cout << "v一的元素个数:" <<v.size() << endl;
    cout << "容量是:" << v.capacity() << endl;

}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Test1<int>();

    //template <typename T>
    Vector<int>b(18,6,3);
    b.show_list();
    Vector<int>d(9,9,9);
    d.show_list();
    return 0;
}
