#include "TextQuery.h"

int main(int argc, char *argv[])
{
    std::ifstream is(argv[1]);
    TextQuery essay(is);        //���ı����ڶ���eaasy��

    std::string word;
    std::cout << "input search word('q' is quit):";
    while(std::cin >> word && word != "q")
    {
        std::cout << std::endl;
        print(std::cout, essay.query(word));      //���ı���ѯ�Ľ����ӡ����

        std::cout << "input search word('q' is quit):";
    }
}
