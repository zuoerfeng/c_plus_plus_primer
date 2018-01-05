#include "vector.h"

std::allocator<std::string> StrVec::alloc;

int main()
{
    StrVec sv;
    std::string s;
    while(std::cin >> s && s != "q")
    {
        sv.push_back(s);
    }
    std::cout << "size:" << sv.size() << " ";
    std::cout << "capacity:" << sv.capacity() << " ";
    std::cout << "begin:" <<  *sv.begin() << " ";
    std::cout << "end:" << *(sv.end()-1) << std::endl;
    s = "stop";
    sv.push_back(s);
    sv.push_back(s);
    std::cout << "size:" << sv.size() << " ";
    std::cout << "capacity:" << sv.capacity() << " ";
    std::cout << "begin:" <<  *sv.begin() << " ";
    std::cout << "end:" << *(sv.end()-1) << std::endl;
    sv.reserve(10);
    std::cout << "reserve:" << std::endl;
    std::cout << "size:" << sv.size() << " ";
    std::cout << "capacity:" << sv.capacity() << " ";
    std::cout << "begin:" <<  *sv.begin() << " ";
    std::cout << "end:" << *(sv.end()-1) << std::endl;
    sv.resize(11);
    std::cout << "resize:" << std::endl;
    std::cout << "size:" << sv.size() << " ";
    std::cout << "capacity:" << sv.capacity() << " ";
    std::cout << "begin:" <<  *sv.begin() << " ";
    std::cout << "end:" << *(sv.end()-1) << std::endl;
    std::cout << "构造函数初始值列表:" << std::endl;
    StrVec sv2({"wang","wei","hao"});
    std::cout << "size:" << sv2.size() << " ";
    std::cout << "capacity:" << sv2.capacity() << " ";
    std::cout << "begin:" <<  *sv2.begin() << " ";
    std::cout << "end:" << *(sv2.end()-1) << std::endl;

    StrVec sv3(sv2);
    StrVec sv4;
    sv4 = sv2;
    std::cout << "拷贝构造:" << std::endl;
    std::cout << "size:" << sv3.size() << " ";
    std::cout << "capacity:" << sv3.capacity() << " ";
    std::cout << "begin:" <<  *sv3.begin() << " ";
    std::cout << "end:" << *(sv3.end()-1) << std::endl;
    std::cout << "赋值构造:" << std::endl;
    std::cout << "size:" << sv4.size() << " ";
    std::cout << "capacity:" << sv4.capacity() << " ";
    std::cout << "begin:" <<  *sv4.begin() << " ";
    std::cout << "end:" << *(sv4.end()-1) << std::endl;
}
