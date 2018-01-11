#include "textquery.h"

//重载<<
std::ostream& operator<<(std::ostream &os, const QueryResult &q)
{
    os << "element occurs:" << q.lines->size() << " times\n";
    for(line_no i : *q.lines)
    {
        os << "   " << "line(" << i+1 << ") ";
        os << *(q.wordfile->begin()+i) << "\n";
        //os << (*(q.wordfile))[i] << "\n";   //注意运算符优先级
    }
    return os;
}

TextQuery::TextQuery(std::ifstream &is):m_file(new std::vector<std::string>)
{
    std::string word;
    std::string line;
    static int i = 0;
    while(std::getline(is, line))
    {
            //行号
        m_file->push_back(line);
        i = m_file->size()-1;
        std::istringstream ist(line);
        while(ist >> word)
        {
            auto &li = m_word_line[word];  //返回set的shared_ptr
            if(!li)
                li.reset(new std::set<line_no>);
            li->insert(i);
        }
    }
}

QueryResult TextQuery::query(const std::string &s)const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto ret = m_word_line.find(s);
    if(ret == m_word_line.end())
        return QueryResult(s, nodata, m_file);
    else
        return QueryResult(s, ret->second, m_file);
}

std::ostream& operator<<(std::ostream &os, const Query &query)
{
    //query.rep()内部还是通过指针来调用的，是需调用
    return os << query.rep();
}

//QueryResult
std::set<line_no>::iterator QueryResult::begin()
{
    return lines->begin();
}

std::set<line_no>::iterator QueryResult::end()
{
    return lines->end();
}

std::shared_ptr<std::vector<std::string>> QueryResult::get_file()
{
    return wordfile;
}


//eval

QueryResult
OrQuery::eval(const TextQuery &text)const
{
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult
AndQuery::eval(const TextQuery &text)const
{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult
NotQuery::eval(const TextQuery &text)const
{
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    //相当于两个集合两个指针一起走。
    for(std::size_t n = 0; n != sz; ++n)
    {
        if(beg == end || *beg != n)
            ret_lines->insert(n);
        else if(beg != end)
            ++beg;
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}
