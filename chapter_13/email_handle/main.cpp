#include <iostream>
#include "Folder.h"
#include "Message.h"

using namespace std;


int main()
{
    Folder file1("mail1");
    Folder file2("mail2");
    Message m1;
    Message m2;

    cout << "please input first message:" << endl;
    read(std::cin, m1);
    m1.save(file1);
    m1.save(file2);

    cout << "please input second message:" << endl;
    read(std::cin, m2);
    m2.save(file1);
    m2.save(file2);

    print(std::cout, m1);
    print(std::cout, m2);
    swap(m1,m2);
    print(std::cout, m1);
    print(std::cout, m2);
}
