#include <iostream>
#include "_MyVector.h"
using namespace std;



template <typename T>
void Test1() {
    Vector<T>v(8,8,2);
    Vector<T>a(12,4,3);
    cout << "vһ��Ԫ�ظ���:" <<v.size() << endl;
    cout << "������:" << v.capacity() << endl;
    v.show_list();
    v.expand();
    cout << endl;
    cout << "vһ��Ԫ�ظ���:" <<v.size() << endl;
    cout << "������:" << v.capacity() << endl;

}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Test1<int>();

    //template <typename T>
    Vector<int>b(18,6,3);
    b.show_list();
    Vector<int>d(9,9,9);
    d.show_list();
    cout << "\nd2�ǣ�" << d[2] << endl;
    return 0;
}
