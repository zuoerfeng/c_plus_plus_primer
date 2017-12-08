#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <cstddef>
using std::size_t;

#include <cctype>
using std::isupper; using std::toupper;
using std::islower; using std::tolower;
using std::isalpha; using std::isspace;

int main()
{
    /*test1*/
    const string hexdights = "0123456789ABCDEF";
    cout << "Enter a series of numbers between 0 and 15"
         << "separated by spaces.  Hit ENTER when finished:"
         << endl;

    string result;
    string::size_type n;

    while(cin >> n)
    {
        if(n < hexdights.size())
            result += hexdights[n];
    }
    cout << "Your hex number is: " << result << endl;


    /*test2*/
    string s("hello world!!!");
    decltype(s.size()) punct_cnt = 0;

    //begin to count
    for(auto c:s)
    {
        if(ispunct(c))
            ++punct_cnt;
    }

    cout << punct_cnt << " punctuation characters in " << s << endl;

    /*test3*/
    string orig = s;
    for(auto &c:s)
        c = toupper(c);

    cout << s << endl;

    /*test4*/
    s = orig;
    decltype(s.size()) index = 0;

    while(index != s.size() && !isspace(s[index]))
    {
        s[index] = toupper(s[index]);
        ++index;
    }

    cout << s << endl;

    return 0;
}
