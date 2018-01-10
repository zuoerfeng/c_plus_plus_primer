#include <iostream>
#include <string>
#include <set>
#include <memory>

using namespace std;

//买书的类
class quote
{
    friend double print_total(std::ostream &os, quote &q, std::size_t sz);
    public:
        quote() = default;
        quote(const std::string &book, double p):
            bookNo(book), price(p) { }
        quote(const quote &q):
            bookNo(q.bookNo), price(q.price) { }
        quote(quote &&q):             //一个右值拷贝
            bookNo(q.bookNo), price(q.price) { }
        quote& operator=(const quote &q)
        {
            bookNo = q.bookNo;
            price = q.price;
            return *this;
        }

        virtual double net_price(std::size_t sz)const
        {
            return price * sz;
        }
        const std::string& isbn()const
        {
            return bookNo;
        }
        //注意动态内存分配问题，基类和派生类的内存大小不同
        //所以我们写了个分配函数，且必须定义为虚函数。为了实现后面的动态分配
        //后面跟着成员限定符说明是用作左值还是右值
        virtual quote* clone()const&
        { return new quote(*this); }
        virtual quote* clone() &&                   //右值版本
        { return new quote(std::move(*this)); }

    protected:
        double price;

    private:
        std::string bookNo;
};

double print_total(std::ostream &os, quote &q, std::size_t sz)
{
    double ret = q.net_price(sz);
    os << q.isbn() << " " << q.price << " " << ret << "\n";
    return ret;
}

//抽象基类，因为打折有许多不同的措施，但都基于discount和disc_num
//简单来说抽象出来一个标准，discount和disc_num 就可以说是一个标准。
class disc_quote : public quote
{
    public:
        disc_quote() = default;
        disc_quote(const std::string &book, double p, double disc, std::size_t num):
            quote(book, p), discount(disc), disc_num(num) { }
        double net_price(std::size_t sz)const = 0;   //纯虚函数

    protected:
        double discount;
        std::size_t disc_num;

    private:
};

//第一种打折方式
class one_bulk_quote : public disc_quote
{
    public:
        using disc_quote::disc_quote;
        double net_price(std::size_t sz)const override
        {
            if(sz > disc_num)
            {
                return sz * price * discount;
            }
            else
            {
                return sz * price;
            }
        }
        //对第一种打折类实现动态分配
        one_bulk_quote* clone()const &
        {
            return new one_bulk_quote(*this);
        }
        one_bulk_quote* clone() &&
        {
            return new one_bulk_quote(std::move(*this));
        }

    protected:

    private:
};

class two_bulk_quote : public disc_quote
{
    public:
        using disc_quote::disc_quote;
        double net_price(std::size_t sz)
        {
            if(sz > disc_num)
            {
                return (sz-disc_num) * price * discount + disc_num * price;
            }
            else
            {
                return sz * price;
            }
        }

    protected:

    private:
};

//购物篮类，每一本书的交易信息都保存起来
class basket
{
    public:
        //两个成员函数，第一个完成将这个交易存放到集合中，第二个打印清单，并返回总价格
        void add_item(const quote &sale){
            items.insert(std::shared_ptr<quote>(sale.clone()));
        }

        void add_item(quote && sale){
            items.insert(std::shared_ptr<quote>(std::move(sale).clone()));
        }

        double total_receipt(std::ostream &os)const;

    protected:

    private:
        //自定义比较函数
        static bool compare(const std::shared_ptr<quote> &lhs, const std::shared_ptr<quote> &rhs)
        {
            return lhs->isbn() < rhs->isbn();
        }
        //私有变量，几个集合，代表篮子
        std::multiset<std::shared_ptr<quote>, decltype(compare)*> items{compare};//decltype不能推断出指针和引用
};

//打印购物篮的清单，并返回总价格
double basket::total_receipt(std::ostream &os) const
{
    double sum = 0.0;
    //注意下upper_bound的作用
    for(auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
    {
        sum += print_total(std::cout, **iter, items.count(*iter));
    }
    os << "total Sale: " << sum << std::endl;
    return sum;
}

int main()
{
    cout << "Hello world!" << endl;
    basket bsk;
    quote a("123",45);
    one_bulk_quote b("345",45,3,.15);

    bsk.add_item(a);
    bsk.add_item(b);
    bsk.total_receipt(cout);

    return 0;
}
