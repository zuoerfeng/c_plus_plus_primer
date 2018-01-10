#include <iostream>
#include <iostream>

using namespace std;

void testVfunc(void);

int main(int argc, char *argv[])
{
   // testVfunc();
    return 0;
}

//���ȶ���һ������
class Quote{

public:
    Quote() = default;
    Quote(const std::string &book, double salesPrice):
        bookNo(book), price(salesPrice) { }

    std::string isbn() const { return bookNo;}

    //�����麯��
    virtual double netPrice(std::size_t n) const{
        return n*price;
    }
    //����������������
    virtual ~Quote() = default;

private:
    std::string bookNo;
protected:
    double price = 0.0;

};


//����һ�������࣬�̳�����Ļ���
class Bulk_quote : public Quote{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p,
               std::size_t qty, double disc):
    Quote(book,p), min_qty(qty), discount(disc) {}

    //�̳и����麯��
    double netPrice(std::size_t) const override; // override ��ʾע�������麯���������β�Ҫ�ͻ��������麯������һ��

private:
    std::size_t min_qty = 0;  // �����ۿ����ߵ���͹�����
    double discount = 0.0;    // ��С����ʾ���ۿ۶�
};


// ����ﵽ�˹����鼮��ĳ���������ֵ�� �Ϳ��������ۿۼ۸���
double Bulk_quote::netPrice(size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}


void printTotal(ostream &os, const Quote &item, size_t n)
{
    //��̬�󶨣�ֻ����������û���ָ����Ч��
    // ���� item �Ķ������͵��� netPrice

    double ret = item.netPrice(n);      //netprice���õĲ�һ��
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
}


// ��̬��
void testRunTimeBinding(void)
{
    Quote basic;
    Bulk_quote bulk;
    printTotal(cout, basic, 20); // Quote �� netPrice
    printTotal(cout, bulk, 20); // Bulk_quote �� netPrice
}

/**********************************************************************************/

//�����������
//class Bulk_quote : public Quote;   // ���� �����б��ܳ���������
//class Bulk_quote;                  // ��ȷ

// class Quote;         // ������δ����
// ���� Quote ���뱻����
//class Bulk_quote : public Quote { };
// ��ֹ�̳�,����̳��Ѿ�����Ļ���

class NoDerived final { };  // ������Ϊ����

// override �ô���ʹ�ó���Ա����ͼ����������ͬʱ�ñ���������Ϊ���Ƿ���һЩ����
// ���������������һ��������������麯����������ͬ�����β��б�ͬ������������Ϊ
// �¶������������ͻ�����麯�����໥�����ģ�Ҳ���Ǹ���ʧ��
struct B {
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};

struct D1 : B {
    void f1(int) const override;    // ��ȷ
//    void f2(int) override;          // ���� Bû������f2(int)�ĺ���
//    void f3() override;             // ���� f3�����麯��
//    void f4() override;             // ���� Bû����Ϊf4�ĺ���
};

struct D2 : B {
    void f1(int) const final;       // ����������������า��f1(int)
};
struct D3 : D2 {
    void f2();                      // ��ȷ ���ǴӼ�ӻ���B�̳ж�����f2
//    void f1(int) const;             // ���� final���ܸ���
};


// �ر��麯���Ļ���
void avoidVfunc(void)
{
    // ǿ�е��û����ж���ĺ����汾 ������baseP�Ķ�̬����
    // ����ʱ��ɽ���
//    double undiscounted = baseP->Quote::netPrice(42);
}

//����һ������Ļ��࣬���ǲ��ô��麯�������麯����û��ʵ�ʲ�����ֻ�������̳У�
//���д��麯�������ǳ�����࣬��������ǲ��ܴ��������
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
               std::size_t qty, double disc):
        Quote(book, price), quantity(qty), discount(disc) { }
    double netPrice(std::size_t n) const = 0;
    // ������಻��ʵ����
    // ���麯�������ṩ���壬�������������ⲿ�������ʱ������ = 0
private:
    std::size_t quantity = 0;
    double discount = 0.0;
};

// ��ͬһ�鼮������������ĳ��ֵ
class Bulk_quote2 : public Disc_quote {
public:
    Bulk_quote2() = default;
    Bulk_quote2(const std::string& book, double price,
                std:: size_t qty, double disc):
        Disc_quote(book, price, qty, disc) { }
    double netPrice(std::size_t) const override;
};

// ��Ԫ
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
    friend void clobber(Sneaky&);   // �ܷ���Sneaky::protMem
    friend void clobber(Base&);     // ���ܷ���Base::protMem,��Ϊ����base����Ԫ
    int j;  // Ĭ�� private
};

// ��Ԫ��ϵ���ܼ̳�
class Pal {
    int f(Base &b) { return b.protMem; }    // Pal �� Base ����Ԫ
//    int f2(Sneaky &s) { return s.j; }       // Pal ���� Sneaky ����Ԫ
    int f3(Sneaky &s) { return s.protMem; } // Pal �� Base ����Ԫ
};

// using �ı���ʼ���
class Derived : private Base {
public:
    using Base::size;
    int memfcn(int) { }         //  ���ػ���� memfcn
protected:
    using Base::n;
};


// �麯����������
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
    // ���ػ����fcn�����fcn�����麯��
    // D_1 �̳���Base2::fcn() �Ķ���
    int fcn(int)  { cout << "D_1 " << __FUNCTION__ << endl; }
    virtual void f2() { cout << "D_1 " << __FUNCTION__ << endl; }
};
class D_2 : public D_1 {
public:
    D_2() = default;
    ~D_2() = default;

    // ���麯����������D_1::fcn(int)
    int fcn(int) { cout << "D_2 " << __FUNCTION__ << endl; }
    // ������Base ���麯��fcn
    int fcn() { cout << "D_2 " << __FUNCTION__ << endl; }
    // ���� f2
    void f2() { cout << "D_2 " << __FUNCTION__ << endl; }
};
// ͨ������������ص��麯��
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
//    bp2->f2();  // ���� Base2 û�� f2
    d1p->f2();
    d2p->f2();
}



