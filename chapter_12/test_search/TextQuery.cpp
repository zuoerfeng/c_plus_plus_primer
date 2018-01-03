#include "TextQuery.h"

//TextQuery的构造函数
TextQuery::TextQuery(std::ifstream &infile):m_file(new std::vector<std::string>)  //make_shared<vector<string>>()
{
    std::string line;
    std::string word;
    static int i = 0;

    //按行就文本的数据用容器vector存储起来
    while(std::getline(infile,line))
    {
        i++;
        m_file->push_back(line);//按行保存文本.
        std::istringstream i_line(line);
        while(!i_line.eof())
        {
            i_line >> word;

            auto &li = m_word_line[word];    //li是一个指针，指向的是vector里面保存的行号，如果查询不到这个行号，则返回空指针
            if(!li)             //为了避免拷贝set行号动态分配
                li.reset(new std::set<line_no>);   //如果是新的单词，这个时候需要重新创建一个set，并且用一个智能指针指向它

            //将这个单词对应当前的行号插入到set中,由于是不包含重复的关键字的容器，故插入同样的行号是没有影响的
            li->insert(i);
        }
    }
}

//查询函数的实际操作
QueryResult TextQuery::query(const std::string& sought)const
{
    static std::shared_ptr<std::set<line_no>>nodata(new std::set<line_no>);    //定义一个指向行号集合的智能指针

    auto loc = m_word_line.find(sought);

    //判断是否找到了单词，找到了则构造一个返回类
    if(loc == m_word_line.end())
        return QueryResult(sought, nodata, m_file);
    else
        return QueryResult(sought, loc->second, m_file);
}

//首先输出查询的行号，在输出对应行号的内容
std::ostream& print(std::ostream &os, const QueryResult &qr)
{
    os << "element occurs " << qr.lines->size() << " times" << std::endl;
    for(line_no i : *qr.lines)
    {
        os << "    " << "(line " << i<< ") ";
        os << *(qr.file->begin()+i-1)<< std::endl;
    }

    return os;
}
