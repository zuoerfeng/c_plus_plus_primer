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
        std::string q_word;                                 //Ҫ��ѯ����
        std::shared_ptr<std::set<line_no>>lines;            //�����к�
        std::shared_ptr<std::vector<std::string>>wordfile;  //�����ļ�
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
        std::map<std::string, std::shared_ptr<std::set<line_no>>>m_word_line;     //���ǹ������ݵ�����

};


//Query_base ������࣬�ƶ�һ����׼
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

//�ӿ���,������������඼����ͨ��Query��ʹ�ã�����ʵ��
class Query
{
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);
    friend std::ostream& operator<<(std::ostream &os, const Query &query);
    public:
        Query(const std::string&);//wait WordQuery
        //Query��Query_base��Ψһ�ӿڣ����Ա��붨�崿�麯��
        //��Query�Ϳ���ͨ��ָ�����������������Query_base�麯��
        QueryResult eval(const TextQuery &t)const
        { return q->eval(t); }
        std::string rep()const
        { return q->rep(); }
    private:
        //���캯������Ϊprivate,��ϣ��һ���û���㶨��Query_base����
        Query(std::shared_ptr<Query_base> query):q(query) { }
        //ͨ������ָ��ʵ�ֶ�̬��
        std::shared_ptr<Query_base> q;
};

//������
class WordQuery: public Query_base
{
    friend class Query;
    WordQuery(const std::string &s):query_word(s) { }
    //�������
    QueryResult eval(const TextQuery &t)const
    { return t.query(query_word); }
    std::string rep()const { return query_word; }
    std::string query_word;        //Ҫ���ҵĵ���
};

//�������ֲ�ѯ���ǽ�����WordQuery�ĸ����ϣ�So Query�Ĺ��캯����һ��WordQuery����ʼ��
inline Query::Query(const std::string &s):
    q(new WordQuery(s)) { }

class NotQuery: public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q):query(q) { }
    //������࣬���ǵ����麯��
    std::string rep()const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery &)const;
    Query query;
};

inline Query operator~(const Query &operand)
{
    //ע�ⷵ��ֵ
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

//����������ĳ������
class BinaryQuery: public Query_base
{
    protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
        lhs(l), rhs(r), opSym(s) { }
    std::string rep()const
    { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
    //eval����û�ж��壬�̳��˴��麯�������ǳ������

    Query lhs, rhs;
    std::string opSym;
};

class AndQuery: public BinaryQuery
{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "&") { }
    //������࣬������eval���Ҽ̳���rep
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
    //������࣬������eval���Ҽ̳���rep
    QueryResult eval(const TextQuery&)const;
};

inline Query operator|(const Query&lhs, const Query&rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

#endif
