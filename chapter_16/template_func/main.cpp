#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;


//函数模板
template <typename T>
int compare(const T& v1, const T& v2)
{
    if(v1 < v2)
        return -1;
    if(v1 > v2)
        return 1;
    return 0;
}

template<typename iterator, typename T>
iterator Find(const iterator &beg, const iterator &end, const T&ele)
{
    for(auto it = beg; it != end; ++it)
    {
        if(*it == ele)
            return it;
    }
    return end;
}



int main()
{
    cout << "Hello world!" << endl;

    int i1 = 10, i2 = 20;
    double d1 = 20.1, d2 = 20.01;
    unsigned u1 = 10, u2 = 10;
    std::cout << compare(i1, i2) << std::endl;
    std::cout << compare(d1, d2) << std::endl;
    std::cout << compare(u1, u2) << std::endl;

    std::vector<int>ivec1 = {1,2,3,4,5,6,7,8,9,0};
    auto ret = Find(begin(ivec1), end(ivec1), 3);           //实例化为template<typename iterator, int>
    if(ret == end(ivec1))
        std::cout << "not find" << std::endl;
    else
        std::cout << "find " << *ret << std::endl;

    std::list<std::string>il = {"111","222","333","444","555"};     //实例化为template<typename iterator, string>
    auto ret2 = Find(il.begin(), il.end(), "333");
    if(ret2 == il.end())
        std::cout << "not find" << std::endl;
    else
        std::cout << "find " << *ret2 << std::endl;

    return 0;
}
