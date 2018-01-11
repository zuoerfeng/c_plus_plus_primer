#include "textquery.h"

int main(int argc, char *argv[])
{
    std::ifstream is(argv[1]);
    TextQuery t1(is);     //��������ı��洢��TextQuery������

    std::string word;
    Query q = Query("fiery") & Query("bird") | Query("wind");
    //Query q = Query("fiery");
    //Query q = Query("A");

    std::cout << q << std::endl;                 // <<������
    std::cout << q.eval(t1) << std::endl;

}
