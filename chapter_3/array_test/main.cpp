#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <string>
using std::string;


int main()
{
    char one = 'e';
    char two = 's';
    string test0("123456");
    char test1[]="123456";

    auto ia = test0;       //ia是一个string类型的对象
    auto ib = test1;       //ia是一个char*型的指针
    auto ic = test0[0];    //ic是一个char型的字符
    auto id = test1[0];    //id是一个char型的字符

    decltype(test0) ie;             //ie是一个string类型的对象
    decltype(test1) ig="123456";    //ig是一个由7个字符大小的数组
    decltype(test0[0]) ih = one;    //ih是一个char&型的引用
    decltype(test1[0]) ip = two;    //ip是一个char&型的引用

    ia = "abc";
    ib = &one;
    ic = '9';
    id = 'x';

    ie = "efg";
    ig[0] = 'p';
    ih = 'k';
    ip = 'l';

    cout << ia << endl;
    cout << *ib << endl;
    cout << ic << test0[0] << endl;
    cout << id << test1[0] << endl;

    cout << ie << endl;
    cout << ig << endl;
    cout << ih << one << endl;
    cout << ip << two << endl;

    return 0;

}
