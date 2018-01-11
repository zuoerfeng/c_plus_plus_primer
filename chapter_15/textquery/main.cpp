#include "textquery.h"

int main(int argc, char *argv[])
{
    std::ifstream is(argv[1]);
    TextQuery t1(is);     //将输入的文本存储在TextQuery类型中

    std::string word;
    Query q = Query("fiery") & Query("bird") | Query("wind");
    //Query q = Query("fiery");
    //Query q = Query("A");

    std::cout << q << std::endl;                 // <<被重载
    std::cout << q.eval(t1) << std::endl;

}
