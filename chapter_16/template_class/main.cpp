#include <iostream>
#include "blob.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    blob<string> article = {"a","b","c"};
    cout << article.size() << endl;
    cout << article.back() << endl;

    blob<int> num = {1,2,3,4};
    cout << num.size() << endl;
    cout << num.back() << endl;
    return 0;



}
