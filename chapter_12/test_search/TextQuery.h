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
        //��Ĺ��캯������ʾ�Ĵ������������ֱ��ʼ��������Ա
        QueryResult(std::string s,
                    std::shared_ptr<std::set<line_no>>l,
                    std::shared_ptr<std::vector<std::string>> f):
            s_word(s),lines(l),file(f) { }


    private:   //������Ա��һ���ַ�����һ��ָ��set����������ָ�룬һ��ָ��vector������ָ��
        std::string s_word;
        std::shared_ptr<std::set<line_no>>lines;
        std::shared_ptr<std::vector<std::string>>file;
};

class TextQuery
{
    friend class QueryResult;
    public:
        //�������캯��
        TextQuery() = default;
        TextQuery(std::ifstream &infile);
        QueryResult query(const std::string&)const;    //�����˲�ѯ����

    private:   //������Ա��һ��ָ�򱣴��ı�������ָ�룬һ��map��������keyΪ�ؼ��֣�valueΪ����ָ�룬ָ��һ��set������������װ�����к�
        std::shared_ptr<std::vector<std::string>>m_file;
        std::map<std::string, std::shared_ptr<std::set<line_no>>>m_word_line;
};

#endif
