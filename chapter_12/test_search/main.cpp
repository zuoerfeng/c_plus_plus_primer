#include "TextQuery.h"

int main(int argc, char *argv[])
{
    std::ifstream is(argv[1]);
    TextQuery essay(is);        //将文本存在对象eaasy中

    std::string word;
    std::cout << "input search word('q' is quit):";
    while(std::cin >> word && word != "q")
    {
        std::cout << std::endl;
        print(std::cout, essay.query(word));      //将文本查询的结果打印出来

        std::cout << "input search word('q' is quit):";
    }
}
