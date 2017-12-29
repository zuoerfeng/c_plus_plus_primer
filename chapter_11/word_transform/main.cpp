#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

map<string,string> build_map(ifstream &map_file);
const string & transform(const string &s, const map<string, string> &m);
void word_transform(ifstream &map_file, ifstream &input);

//单词转换程序，首先有两个文本，一个是用来保存转换规则，即map存的映射关系，第二个文本用来转换初始文档
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

    //当输入参数验证成功后，执行单词的转换程序
    word_transform(map_file, input);

    return 0;
}

void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = build_map(map_file);   //这里的返回类型应该是一个map的容器
    //打印一个存储的转换映射关系
    for(auto entry : trans_map)
        cout << "key: "   << entry.first
             << "\tvalue: " << entry.second << endl;
    cout << "\n\n";

    //开始从输入文档中读取数据，查找map的容器，然后进行转换，最后进行打印输出
    string text;
    while(getline(input,text)){
        istringstream stream(text);     //读取一行里面的每个单词,用空格进行区分
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


//map容器函数，用来存储文件的转换关系(容器这种类型是在内存堆里面存放的)
map<string,string> build_map(ifstream &map_file)
{
    map<string,string> trans_map;
    string key;
    string value;

    //这个操作很经典，将流的第一个单词给key，一行剩余的给value
    while(map_file >> key && getline(map_file,value)){
        if(value.size() > 1)
            trans_map[key] = value.substr();    //跳过前导空格
        else
            throw runtime_error("no rule for " + key);
    }
    return trans_map;
}

//生成转换后的文档
const string & transform(const string &s, const map<string, string> &m)
{
    auto map_it = m.find(s);
    if(map_it != m.cend())
        return map_it->second;
    else
        return s ;
}
