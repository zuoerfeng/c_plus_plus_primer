#include <cstddef>
using std::size_t;

#include <cassert>

#include <string>
using std::string;

#include <iostream>
using std::endl; using std::cerr; using std::cin;

#include <cstddef>
using std::size_t;

//#define NDEBUG
//有NDEBUG定义的时候，assert就关闭调试状态，没有定义的时候，就打开assert的调试状态

int main()
{
    string word = "foo";
    const string::size_type threshold = 5;

    if (word.size() < threshold)
        cerr << "Error: " << __FILE__
    #ifdef FUNC_CPP
             << " : in function " << __func__
    #else
             << " : in function " << __FUNCTION__
    #endif
             << " at line " << __LINE__ << endl
             << "       Compiled on " << __DATE__
             << " at " << __TIME__ << endl
             << "       Word read was \"" << word
             << "\":  Length too short" << endl;

    word = "something longer than five chars";
    assert(word.size() > threshold);

    return 0;
}
