#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

// 函数的声明
int min_element(vector<int>::iterator,
                vector<int>::iterator);

// 函数指针
int (*pf)(vector<int>::iterator, vector<int>::iterator)
        = min_element;

int main()
{
    vector<int> ivec;
    // give ivec some values
    cout << "Direct call: "
         << min_element(ivec.begin(), ivec.end()) << endl;

    cout << "Indirect call: "
         << pf(ivec.begin(), ivec.end()) << endl;     //注意函数指针可以不用解指针的调用

	cout << "equivalent indirect call: "
	     << (*pf)(ivec.begin(), ivec.end()) << endl;

    return 0;
}

// returns minimum element in an vector of ints
int min_element(vector<int>::iterator beg,
                vector<int>::iterator end) {
    int minVal = 0;
    while (beg != end) {
        if (minVal > *beg)
            minVal = *beg;
        ++beg;
    }
    return minVal;
}

