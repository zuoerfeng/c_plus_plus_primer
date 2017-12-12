#include <string>
using std::string;

#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <vector>
using std::vector;

int main()
{
    vector<unsigned> grades;
    vector<unsigned> scores(11,0);

    /*test1*/
    //首先将输入的数据划分区间
    unsigned grade;
    while(cin >> grade)
    {
        if(grade <= 100)
        {
            grades.push_back(grade);
            ++scores[grade/10];
        }
    }

    cout << "grades.size = " << grades.size() << endl;
	for (auto it : grades)
		cout << it << " " ;
	cout << endl;

	cout << "scores.size = " << scores.size() << endl;
	for (auto it : scores)
		cout << it << " " ;
	cout << endl;

    return 0;
}
