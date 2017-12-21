#ifndef SALES_DATA_H
#define SALES_DATA_H
#endif // SALES_DATA_H

#include <string>
#include <iostream>
using std::istream; using std::ostream;

class Sales_data{
    //定义友元
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    //定义公有成员函数，能够被外部的类对象代码访问
public:

    //构造函数，不同的应用场景对应不同的构造函数，或者说提供不同初始化的方式
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s), units_sold(0), revenue(0.0){}
    Sales_data(const std::string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n){}
    Sales_data(std::istream &);

    //成员函数
    std::string isbn() const { return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
private:
    std::string bookNo;
    unsigned int units_sold = 0;
    double revenue = 0.0;
};

Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);


