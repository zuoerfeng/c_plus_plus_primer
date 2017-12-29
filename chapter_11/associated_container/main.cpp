#include <iostream>
#include <vector>
#include <set>   //使用集合关联容器包含的头文件
#include <map>   //使用key-value键值对关联容器包含的头文件

void use_set(void);
void count_word(void);

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    use_set();
    count_word();
    return 0;
}

//set型容器概述
void use_set(void)
{
    set<string> exclude = {"the", "but", "and", "or", "an", "a",
                       "The", "But", "And", "Or", "An", "A"};
    string word("but");
    if(exclude.find(word) == exclude.cend())
        cout << "not found" << endl;
    else
        cout << "found" << endl;
}

//map型容器概述
void count_word(void)
{
    map<string,size_t> word_count;
    string word;
    while(cin >> word)
        ++word_count[word];     //对map容器取下标操作，没有的关键字会插入到容器中

    //循环打印每个单词出现的次数
    for(const auto &i : word_count)
        cout << i.first << "occurs " << i.second
             << ((i.second > 1)? " times" : " time") << endl;
}

//测试自定义的类如何应用容器
class Sales_data{

public:
    Sales_data() = default;    //使用默认的构造函数
    int isbn() const { return Isbn;}  //公有的函数，通过公有的函数去访问私有的成员
private:
    int Isbn;
};

//由于自定义的类很可能是没有类似<的比较函数，所以需要自己定义一个比较的函数
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

//可以重复性容器的测试
void multi(void)
{
    vector<int> ivec;
    ivec.reserve(10);
    for (int i = 0; i != 10; ++i) {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    set<int> iset(ivec.cbegin(), ivec.cend()); // 包含10个不重复的elem
    multiset<int> miset(ivec.cbegin(), ivec.cend()); // 包含全部20个

    // 定义mul set时必须提供两个类型
    // 关键字类型，以及比较操作
    multiset<Sales_data, decltype(compareIsbn)*> bookStore(compareIsbn);
}

// pair类型的测试
void pairOp()
{
    pair<string, string> anon;
    pair<string, size_t> wordCount;
    pair<string, vector<int>> line;
    // 默认值初始化
    pair<string, string> author{"James", "Joycc"};
    cout << author.first << endl;
    cout << author.second << endl;
}

//pair的返回值测试
pair<string, int> process(vector<string> &v)
{
    if (!v.empty()) {
        return {v.back(), v.back().size()}; //  列表初始化
        return make_pair(v.back(), v.back().size());
    } else
        return pair<string, int>(); //  隐式构造返回值
}

// 关联容器操作
void op1()
{
    set<string>::value_type v1; //  string
    set<string>::key_type v2;   //  同 value_type
    map<string, int>::value_type v3;    //  pair<const string, int>
    map<string, int>::key_type v4;      //  string
    map<string, int>::mapped_type v5;   //  int

    // 迭代器
    map<string, size_t> wordCount;
    auto mapIt = wordCount.begin();   //map返回的就是pair的迭代器类型
    cout << mapIt->first;             //关键字无论是什么容器都是const类型的
    cout << " " << mapIt->second << endl;
//    mapIt->first = "new key";   //  error: key is const
    ++mapIt->second;
    cout << " " << mapIt->second << endl;

    // set :: iter is const
    // add element
    vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};
    set<int> iset;
    // set 2 种插入
    iset.insert(ivec.cbegin(), ivec.cend());    //  4(set是不重复的)
    iset.insert({1, 3, 1, 3});                  //  +2
    // map 4种
    string word;
    wordCount.insert({word, 1});
    wordCount.insert(make_pair(word, 1));
    wordCount.insert(pair<string, size_t>(word, 1));
    wordCount.insert(map<string, size_t>::value_type(word, 1));

    // insert 返回值 pair<iter, bool>
    // iter 执行具有给定关键字的elem(value_type)， bool 元素是否插入成功
    auto ret = wordCount.insert({word, 1});
    if (!ret.second)    //  word 已在 wordCound 中
        ++ret.first->second;    //  ++((ret.first)->second

    // delete element
    // 返回 删除元素的数量
    map<string, size_t>::iterator pos;
    map<string, size_t>::const_iterator first, last;
    map<string, int>::key_type vv4;
    wordCount.erase(pos);
    wordCount.erase(first, last);
    wordCount.erase(vv4);
    // multi ret > 1 possibly
}










