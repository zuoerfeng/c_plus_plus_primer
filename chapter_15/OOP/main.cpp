#include <iostream>
#include <iostream>

using namespace std;

void testVfunc(void);

int main(int argc, char *argv[])
{
   // testVfunc();
    return 0;
}

//首先定义一个基类
class Quote{

public:
    Quote() = default;
    Quote(const std::string &book, double salesPrice):
        bookNo(book), price(salesPrice) { }

    std::string isbn() const { return bookNo;}

    //设置虚函数
    virtual double netPrice(std::size_t n) const{
        return n*price;
    }
    //设置虚析构哈函数
    virtual ~Quote() = default;

private:
    std::string bookNo;
protected:
    double price = 0.0;

};


//定义一个派生类，继承上面的基类
class Bulk_quote : public Quote{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p,
               std::size_t qty, double disc):
    Quote(book,p), min_qty(qty), discount(disc) {}

    //继承覆盖虚函数
    double netPrice(std::size_t) const override; // override 显示注明覆盖虚函数，并且形参要和基类里面虚函数保持一样

private:
    std::size_t min_qty = 0;  // 适用折扣政策的最低购买量
    double discount = 0.0;    // 以小数表示的折扣额
};


// 如果达到了购买书籍的某个最低限量值， 就可以享受折扣价格了
double Bulk_quote::netPrice(size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}


void printTotal(ostream &os, const Quote &item, size_t n)
{
    //动态绑定，只有是类的引用还是指针有效，
    // 根据 item 的对象类型调用 netPrice

    double ret = item.netPrice(n);      //netprice调用的不一致
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
}


// 动态绑定
void testRunTimeBinding(void)
{
    Quote basic;
    Bulk_quote bulk;
    printTotal(cout, basic, 20); // Quote 的 netPrice
    printTotal(cout, bulk, 20); // Bulk_quote 的 netPrice
}

/**********************************************************************************/

//派生类的声明
//class Bulk_quote : public Quote;   // 错误 派生列表不能出现在这里
//class Bulk_quote;                  // 正确

// class Quote;         // 声明但未定义
// 错误 Quote 必须被定义
//class Bulk_quote : public Quote { };
// 禁止继承,必须继承已经定义的基类

class NoDerived final { };  // 不能作为基类

// override 好处，使得程序员的意图更加清晰的同时让编译器可以为我们发现一些错误
// 派生类如果定义了一个函数与基类中虚函数的名字相同但是形参列表不同，编译器将认为
// 新定义的这个函数和基类的虚函数是相互独立的，也就是覆盖失败
struct B {
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};

struct D1 : B {
    void f1(int) const override;    // 正确
//    void f2(int) override;          // 错误 B没有形如f2(int)的函数
//    void f3() override;             // 错误 f3不是虚函数
//    void f4() override;             // 错误 B没有名为f4的函数
};

struct D2 : B {
    void f1(int) const final;       // 不允许后续的其他类覆盖f1(int)
};
struct D3 : D2 {
    void f2();                      // 正确 覆盖从间接基类B继承而来的f2
//    void f1(int) const;             // 错误 final不能覆盖
};


// 回避虚函数的机制
void avoidVfunc(void)
{
    // 强行调用基类中定义的函数版本 而不管baseP的动态类型
    // 编译时完成解析
//    double undiscounted = baseP->Quote::netPrice(42);
}

//对于一个抽象的基类，我们采用纯虚函数，纯虚函数并没有实际操作，只是用来继承，
//含有纯虚函数的类是抽象基类，抽象基类是不能创建对象的
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
               std::size_t qty, double disc):
        Quote(book, price), quantity(qty), discount(disc) { }
    double netPrice(std::size_t n) const = 0;
    // 抽象基类不能实例化
    // 纯虚函数可以提供定义，不过必须在类外部，定义的时候不能有 = 0
private:
    std::size_t quantity = 0;
    double discount = 0.0;
};

// 当同一书籍的销售量超过某个值
class Bulk_quote2 : public Disc_quote {
public:
    Bulk_quote2() = default;
    Bulk_quote2(const std::string& book, double price,
                std:: size_t qty, double disc):
        Disc_quote(book, price, qty, disc) { }
    double netPrice(std::size_t) const override;
};

// 友元
class Base {
    friend class Pal;
public:
    std::size_t size() const { return n; }
    int memfcn() { }
protected:
    int protMem;
    std::size_t n;
};

class Sneaky : public Base {
    friend void clobber(Sneaky&);   // 能访问Sneaky::protMem
    friend void clobber(Base&);     // 不能访问Base::protMem,因为不是base的友元
    int j;  // 默认 private
};

// 友元关系不能继承
class Pal {
    int f(Base &b) { return b.protMem; }    // Pal 是 Base 的友元
//    int f2(Sneaky &s) { return s.j; }       // Pal 不是 Sneaky 的友元
    int f3(Sneaky &s) { return s.protMem; } // Pal 是 Base 的友元
};

// using 改变访问级别
class Derived : private Base {
public:
    using Base::size;
    int memfcn(int) { }         //  隐藏基类的 memfcn
protected:
    using Base::n;
};


// 虚函数与作用域
class Base2 {
public:
    Base2() = default;
    virtual ~Base2() = default;
    virtual int fcn() { cout << "Base2 " << __FUNCTION__ << endl; }
};
class D_1 : public Base2 {
public:
    D_1() = default;
    virtual ~D_1() = default;
    // 隐藏基类的fcn，这个fcn不是虚函数
    // D_1 继承了Base2::fcn() 的定义
    int fcn(int)  { cout << "D_1 " << __FUNCTION__ << endl; }
    virtual void f2() { cout << "D_1 " << __FUNCTION__ << endl; }
};
class D_2 : public D_1 {
public:
    D_2() = default;
    ~D_2() = default;

    // 非虚函数，隐藏了D_1::fcn(int)
    int fcn(int) { cout << "D_2 " << __FUNCTION__ << endl; }
    // 覆盖了Base 的虚函数fcn
    int fcn() { cout << "D_2 " << __FUNCTION__ << endl; }
    // 覆盖 f2
    void f2() { cout << "D_2 " << __FUNCTION__ << endl; }
};
// 通过基类调用隐藏的虚函数
void testVfunc(void)
{
//    return ;
    Base2 bobj;
    D_1 d1obj;
    D_2 d2obj;

    Base2 *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
    bp1->fcn(); // base2
    bp2->fcn(); // base2
    bp3->fcn(); // D_2

    D_1 *d1p = &d1obj;
    D_2 *d2p = &d2obj;
//    bp2->f2();  // 错误 Base2 没有 f2
    d1p->f2();
    d2p->f2();
}



