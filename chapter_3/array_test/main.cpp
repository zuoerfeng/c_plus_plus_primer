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

    auto ia = test0;       //ia��һ��string���͵Ķ���
    auto ib = test1;       //ia��һ��char*�͵�ָ��
    auto ic = test0[0];    //ic��һ��char�͵��ַ�
    auto id = test1[0];    //id��һ��char�͵��ַ�

    decltype(test0) ie;             //ie��һ��string���͵Ķ���
    decltype(test1) ig="123456";    //ig��һ����7���ַ���С������
    decltype(test0[0]) ih = one;    //ih��һ��char&�͵�����
    decltype(test1[0]) ip = two;    //ip��һ��char&�͵�����

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
