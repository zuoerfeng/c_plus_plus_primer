#ifndef _TEXTQUERY_H_
#define _TEXTQUERY_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>

using line_no = std::vector<std::string>::size_type;

class TextQuery;
class QueryResult;

class QueryResult
{
    friend class TextQuery;
    friend std::ostream& print(std::ostream &os, const QueryResult &qr);
    public:
        //类的构造函数，显示的传入三个参数分别初始化三个成员
        QueryResult(std::string s,
                    std::shared_ptr<std::set<line_no>>l,
                    std::shared_ptr<std::vector<std::string>> f):
            s_word(s),lines(l),file(f) { }


    private:   //三个成员，一个字符串，一个指向set容器的智能指针，一个指向vector的智能指针
        std::string s_word;
        std::shared_ptr<std::set<line_no>>lines;
        std::shared_ptr<std::vector<std::string>>file;
};

class TextQuery
{
    friend class QueryResult;
    public:
        //两个构造函数
        TextQuery() = default;
        TextQuery(std::ifstream &infile);
        QueryResult query(const std::string&)const;    //定义了查询操作

    private:   //两个成员，一个指向保存文本的智能指针，一个map的容器，key为关键字，value为智能指针，指向一个set的容器，里面装的是行号
        std::shared_ptr<std::vector<std::string>>m_file;
        std::map<std::string, std::shared_ptr<std::set<line_no>>>m_word_line;
};

#endif
