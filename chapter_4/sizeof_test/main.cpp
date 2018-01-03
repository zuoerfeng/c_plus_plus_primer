#include <iostream>
using std::cout; using std::endl;

#include "sales_data.h"

int main()
{
    //������ʽ��sizeof expr;������Բ����sizeof(type)
    Sales_data data, *p;

    sizeof(Sales_data); // size required to hold an object of type Sales_data
	sizeof data; // size of data's type, i.e., sizeof(Sales_data)
	sizeof p;    // size of a pointer
	sizeof *p;   // size of the type to which p points, i.e., sizeof(Sales_data)
	sizeof data.revenue; // size of the type of Sales_data's revenue member

#ifdef SIZEOF_MEMBER
	sizeof Sales_data::revenue; // alternative way to get the size of revenue
#else
	sizeof Sales_data().revenue; // use an object
#endif


	cout << "short: " << sizeof(short) << "\n"
	     << "short[3]: " << sizeof(short[3]) << "\n"
	     << "short*: " << sizeof(short*) << "\n"               //ָ����4�ֽ�
	     << "short&: " << sizeof(short&) << endl;              //���þ��Ƕ������͵Ĵ�Сshort�������ֽ�

	cout << endl;

	cout << "int: " << sizeof(int) << "\n"
	     << "int[3]: " << sizeof(int[3]) << "\n"
	     << "int*: " << sizeof(int*) << "\n"                   //ָ����4�ֽ�
	     << "int&: " << sizeof(int&) << endl;

	cout << endl;

	cout << "Sales_data: " << sizeof(Sales_data) << "\n"
	     << "Sales_data[3]: " << sizeof(Sales_data[3]) << "\n"
	     << "Sales_data*: " << sizeof(Sales_data*) << "\n"      //ָ����4�ֽ�
	     << "Sales_data*: " << sizeof *p << "\n"
	     << "Sales_data&: " << sizeof(Sales_data&) << "\n" << endl;

#ifdef SIZEOF_MEMBER
	cout << "Sales_data::revenue: " << sizeof Sales_data::revenue << "\n"
#else
	cout << "Sales_data().revenue: " << sizeof Sales_data().revenue << "\n"
	     << "data.revenue: " << sizeof data.revenue << endl;
#endif

	int x[10];
	int *ip = x;

	// number of elements in x
	cout << sizeof(x)/sizeof(*x) << endl;

	// divides sizeof a pointer by sizeof an int
	cout << sizeof(ip)/sizeof(*ip) << endl;

	return 0;
}
