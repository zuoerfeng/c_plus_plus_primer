#ifndef _TEXTQUERY_H_
#define _TEXTQUERY_H_

#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

class QueryResult;
class TextQuery;

using line_no = std::vector<std::string>::size_type;

class QueryResult
{
    friend class TextQuery;
    friend std::ostream& operator<<(std::ostream &os, const QueryResult &q);
    public:
        QueryResult() = default;
        QueryResult(std::string s, std::shared_ptr<std::set<line_no>>li, std::shared_ptr<std::vector<std::string>>wf):
            q_word(s), lines(li), wordfile(wf) { }
        std::set<line_no>::iterator begin();
        std::set<line_no>::iterator end();
        std::shared_ptr<std::vector<std::string>> get_file();

    private:
        std::string q_word;                                 //要查询单词
        std::shared_ptr<std::set<line_no>>lines;            //出现行号
        std::shared_ptr<std::vector<std::string>>wordfile;  //单词文件
};

class TextQuery
{
    friend class QueryResult;
    public:
        TextQuery() = default;
        TextQuery(std::ifstream &is);
        QueryResult query(const std::string &s)const;

    private:
        std::shared_ptr<std::vector<std::string>>m_file;
        std::map<std::string, std::shared_ptr<std::set<line_no>>>m_word_line;     //考虑共享数据的需求

};


//Query_base 抽象基类，制定一个标准
class Query_base
{
    friend class Query;
    protected:
        virtual ~Query_base() = default;

    private:
        //
        virtual QueryResult eval(const TextQuery &)const = 0;
        virtual std::string rep()const = 0;
};

//接口类,基类包括派生类都可以通过Query来使用，隐藏实现
class Query
{
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);
    friend std::ostream& operator<<(std::ostream &os, const Query &query);
    public:
        Query(const std::string&);//wait WordQuery
        //Query是Query_base的唯一接口，所以必须定义纯虚函数
        //且Query就可以通过指针来调用派生类各自Query_base虚函数
        QueryResult eval(const TextQuery &t)const
        { return q->eval(t); }
        std::string rep()const
        { return q->rep(); }
    private:
        //构造函数定义为private,不希望一般用户随便定义Query_base对象。
        Query(std::shared_ptr<Query_base> query):q(query) { }
        //通过智能指针实现动态绑定
        std::shared_ptr<Query_base> q;
};

//派生类
class WordQuery: public Query_base
{
    friend class Query;
    WordQuery(const std::string &s):query_word(s) { }
    //具体的类
    QueryResult eval(const TextQuery &t)const
    { return t.query(query_word); }
    std::string rep()const { return query_word; }
    std::string query_word;        //要查找的单词
};

//无论哪种查询都是建立在WordQuery的根本上，So Query的构造函数用一个WordQuery来初始化
inline Query::Query(const std::string &s):
    q(new WordQuery(s)) { }

class NotQuery: public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q):query(q) { }
    //具体的类，覆盖掉纯虚函数
    std::string rep()const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery &)const;
    Query query;
};

inline Query operator~(const Query &operand)
{
    //注意返回值
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

//两个运算符的抽象基类
class BinaryQuery: public Query_base
{
    protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
        lhs(l), rhs(r), opSym(s) { }
    std::string rep()const
    { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
    //eval函数没有定义，继承了纯虚函数，还是抽象基类

    Query lhs, rhs;
    std::string opSym;
};

class AndQuery: public BinaryQuery
{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "&") { }
    //具体的类，覆盖了eval并且继承了rep
    QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query&lhs, const Query&rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery: public BinaryQuery
{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "|") { }
    //具体的类，覆盖了eval并且继承了rep
    QueryResult eval(const TextQuery&)const;
};

inline Query operator|(const Query&lhs, const Query&rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

#endif
