#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cctype>
using std::isupper; using std::toupper;
using std::islower; using std::tolower;
using std::isalpha; using std::isspace;

int main()
{
    /*test1*/
    string str("some string");
    string orig = str;

    if(!str.empty())
        cout << str[0] << endl;
    if(!str.empty())
        str[0] = toupper(str[0]);
    cout << str[0] << endl;


    /*test2*/
    if(str.begin() != str.end())
    {
        auto it = str.begin();
        *it = toupper(*it);
    }
    cout << str << endl;

    /*test3*/
    str = orig;
    for(decltype(str.size()) index = 0;
        index != str.size() && !isspace(str[index]); ++index)
        str[index] = toupper(str[index]);
    cout << str << endl;

    /*test4*/
    str = orig;
    for(auto it = str.begin(); it!=str.end() && !isspace(str[*it]); ++it)
        *it = toupper(*it);
    cout << str << endl;

    /*test5*/
    str = orig;
    decltype(str.size()) index = 0;
    while(index != str.size() && !isspace(str[index]))
    {
        str[index] = toupper(str[index]);
        ++index;
    }
    cout << str << endl;

    /*test6*/
    str = orig;
    auto beg = str.begin();
    while(beg != str.end() && !isspace(str[*beg]))
    {
        *beg = toupper(*beg);
        ++beg;
    }
    cout << str << endl;

    /*test7*/
    //string test("12345678");
    vector<int> test{1,2,3,4,5,6,7,8};
    auto begn = test.begin();
    auto endd = test.end();
    auto mid = begn + (endd - begn)/2;
    auto sought = 3;

    //cout << "please input search number:" << endl;
    //cin >> sought;
    while(mid != endd && *mid != sought)
    {
        if(sought < *mid)
            endd = mid;
        else if(sought > *mid)
            begn = mid;

        mid = begn + (endd - begn)/2;
    }

    if(mid != endd)
        cout << "the search is :" << *mid << endl;
    else
        cout << "the search is NULL." << endl;

    return 0;
}
