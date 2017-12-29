#include <iostream>
#include <vector>
#include <set>   //ʹ�ü��Ϲ�������������ͷ�ļ�
#include <map>   //ʹ��key-value��ֵ�Թ�������������ͷ�ļ�

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

//set����������
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

//map����������
void count_word(void)
{
    map<string,size_t> word_count;
    string word;
    while(cin >> word)
        ++word_count[word];     //��map����ȡ�±������û�еĹؼ��ֻ���뵽������

    //ѭ����ӡÿ�����ʳ��ֵĴ���
    for(const auto &i : word_count)
        cout << i.first << "occurs " << i.second
             << ((i.second > 1)? " times" : " time") << endl;
}

//�����Զ���������Ӧ������
class Sales_data{

public:
    Sales_data() = default;    //ʹ��Ĭ�ϵĹ��캯��
    int isbn() const { return Isbn;}  //���еĺ�����ͨ�����еĺ���ȥ����˽�еĳ�Ա
private:
    int Isbn;
};

//�����Զ������ܿ�����û������<�ıȽϺ�����������Ҫ�Լ�����һ���Ƚϵĺ���
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

//�����ظ��������Ĳ���
void multi(void)
{
    vector<int> ivec;
    ivec.reserve(10);
    for (int i = 0; i != 10; ++i) {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    set<int> iset(ivec.cbegin(), ivec.cend()); // ����10�����ظ���elem
    multiset<int> miset(ivec.cbegin(), ivec.cend()); // ����ȫ��20��

    // ����mul setʱ�����ṩ��������
    // �ؼ������ͣ��Լ��Ƚϲ���
    multiset<Sales_data, decltype(compareIsbn)*> bookStore(compareIsbn);
}

// pair���͵Ĳ���
void pairOp()
{
    pair<string, string> anon;
    pair<string, size_t> wordCount;
    pair<string, vector<int>> line;
    // Ĭ��ֵ��ʼ��
    pair<string, string> author{"James", "Joycc"};
    cout << author.first << endl;
    cout << author.second << endl;
}

//pair�ķ���ֵ����
pair<string, int> process(vector<string> &v)
{
    if (!v.empty()) {
        return {v.back(), v.back().size()}; //  �б��ʼ��
        return make_pair(v.back(), v.back().size());
    } else
        return pair<string, int>(); //  ��ʽ���췵��ֵ
}

// ������������
void op1()
{
    set<string>::value_type v1; //  string
    set<string>::key_type v2;   //  ͬ value_type
    map<string, int>::value_type v3;    //  pair<const string, int>
    map<string, int>::key_type v4;      //  string
    map<string, int>::mapped_type v5;   //  int

    // ������
    map<string, size_t> wordCount;
    auto mapIt = wordCount.begin();   //map���صľ���pair�ĵ���������
    cout << mapIt->first;             //�ؼ���������ʲô��������const���͵�
    cout << " " << mapIt->second << endl;
//    mapIt->first = "new key";   //  error: key is const
    ++mapIt->second;
    cout << " " << mapIt->second << endl;

    // set :: iter is const
    // add element
    vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};
    set<int> iset;
    // set 2 �ֲ���
    iset.insert(ivec.cbegin(), ivec.cend());    //  4(set�ǲ��ظ���)
    iset.insert({1, 3, 1, 3});                  //  +2
    // map 4��
    string word;
    wordCount.insert({word, 1});
    wordCount.insert(make_pair(word, 1));
    wordCount.insert(pair<string, size_t>(word, 1));
    wordCount.insert(map<string, size_t>::value_type(word, 1));

    // insert ����ֵ pair<iter, bool>
    // iter ִ�о��и����ؼ��ֵ�elem(value_type)�� bool Ԫ���Ƿ����ɹ�
    auto ret = wordCount.insert({word, 1});
    if (!ret.second)    //  word ���� wordCound ��
        ++ret.first->second;    //  ++((ret.first)->second

    // delete element
    // ���� ɾ��Ԫ�ص�����
    map<string, size_t>::iterator pos;
    map<string, size_t>::const_iterator first, last;
    map<string, int>::key_type vv4;
    wordCount.erase(pos);
    wordCount.erase(first, last);
    wordCount.erase(vv4);
    // multi ret > 1 possibly
}










