#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

map<string,string> build_map(ifstream &map_file);
const string & transform(const string &s, const map<string, string> &m);
void word_transform(ifstream &map_file, ifstream &input);

//����ת�����������������ı���һ������������ת�����򣬼�map���ӳ���ϵ���ڶ����ı�����ת����ʼ�ĵ�
int main(int argc, char *argv[])
{
    cout << "Hello world!" << endl;

    if(argc != 3)
        throw runtime_error("wrong number of arguments");

    ifstream map_file(argv[1]);
    if(!map_file)
        throw runtime_error("no transformation file");

    ifstream input(argv[2]);
    if(!input)
        throw runtime_error("no input file");

    //�����������֤�ɹ���ִ�е��ʵ�ת������
    word_transform(map_file, input);

    return 0;
}

void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = build_map(map_file);   //����ķ�������Ӧ����һ��map������
    //��ӡһ���洢��ת��ӳ���ϵ
    for(auto entry : trans_map)
        cout << "key: "   << entry.first
             << "\tvalue: " << entry.second << endl;
    cout << "\n\n";

    //��ʼ�������ĵ��ж�ȡ���ݣ�����map��������Ȼ�����ת���������д�ӡ���
    string text;
    while(getline(input,text)){
        istringstream stream(text);     //��ȡһ�������ÿ������,�ÿո��������
        string word;
        bool firstword = true;
        while(stream >> word){
            if(firstword)
                firstword = false;
            else
                cout << " ";
                cout << transform(word,trans_map);
        }
        cout << endl;
    }
}


//map���������������洢�ļ���ת����ϵ(�����������������ڴ�������ŵ�)
map<string,string> build_map(ifstream &map_file)
{
    map<string,string> trans_map;
    string key;
    string value;

    //��������ܾ��䣬�����ĵ�һ�����ʸ�key��һ��ʣ��ĸ�value
    while(map_file >> key && getline(map_file,value)){
        if(value.size() > 1)
            trans_map[key] = value.substr();    //����ǰ���ո�
        else
            throw runtime_error("no rule for " + key);
    }
    return trans_map;
}

//����ת������ĵ�
const string & transform(const string &s, const map<string, string> &m)
{
    auto map_it = m.find(s);
    if(map_it != m.cend())
        return map_it->second;
    else
        return s ;
}
