#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstddef>
#include "Sales_data.h"

using namespace std;

int main()
{
    unordered_map<string, size_t> word_count;
    string word;
    while (cin >> word)
		++word_count[word];

	for (const auto &w : word_count)
		cout <<  w.first << " occurs " << w.second
		     << ((w.second > 1) ? " times" : " time") << endl;

	return 0;
}

size_t hasher(const Sales_data &sd)
{
	return hash<string>()(sd.isbn());
}
bool eqOp(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() == rhs.isbn();
}

typedef unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*> SD_multiset;   //提供了hash函数，比较函数，都是函数指针
SD_multiset bookstore(42, hasher, eqOp);                                                  //42表示桶大小，hasher对应使用的hash函数，eqOp表示比较函数


struct Foo { string s; };
bool operator==(const Foo& l, const Foo&r) { return l.s == r.s; }
size_t FooHash(const Foo& f) { return hash<string>()(f.s); }

unordered_set<Foo, decltype(FooHash)*> fooSet(10, FooHash);
