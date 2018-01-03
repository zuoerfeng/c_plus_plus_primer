#include "TextQuery.h"

//TextQuery�Ĺ��캯��
TextQuery::TextQuery(std::ifstream &infile):m_file(new std::vector<std::string>)  //make_shared<vector<string>>()
{
    std::string line;
    std::string word;
    static int i = 0;

    //���о��ı�������������vector�洢����
    while(std::getline(infile,line))
    {
        i++;
        m_file->push_back(line);//���б����ı�.
        std::istringstream i_line(line);
        while(!i_line.eof())
        {
            i_line >> word;

            auto &li = m_word_line[word];    //li��һ��ָ�룬ָ�����vector���汣����кţ������ѯ��������кţ��򷵻ؿ�ָ��
            if(!li)             //Ϊ�˱��⿽��set�кŶ�̬����
                li.reset(new std::set<line_no>);   //������µĵ��ʣ����ʱ����Ҫ���´���һ��set��������һ������ָ��ָ����

            //��������ʶ�Ӧ��ǰ���кŲ��뵽set��,�����ǲ������ظ��Ĺؼ��ֵ��������ʲ���ͬ�����к���û��Ӱ���
            li->insert(i);
        }
    }
}

//��ѯ������ʵ�ʲ���
QueryResult TextQuery::query(const std::string& sought)const
{
    static std::shared_ptr<std::set<line_no>>nodata(new std::set<line_no>);    //����һ��ָ���кż��ϵ�����ָ��

    auto loc = m_word_line.find(sought);

    //�ж��Ƿ��ҵ��˵��ʣ��ҵ�������һ��������
    if(loc == m_word_line.end())
        return QueryResult(sought, nodata, m_file);
    else
        return QueryResult(sought, loc->second, m_file);
}

//���������ѯ���кţ��������Ӧ�кŵ�����
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
