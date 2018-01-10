#include <iostream>
#include <string>
#include <set>
#include <memory>

using namespace std;

//�������
class quote
{
    friend double print_total(std::ostream &os, quote &q, std::size_t sz);
    public:
        quote() = default;
        quote(const std::string &book, double p):
            bookNo(book), price(p) { }
        quote(const quote &q):
            bookNo(q.bookNo), price(q.price) { }
        quote(quote &&q):             //һ����ֵ����
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
        //ע�⶯̬�ڴ�������⣬�������������ڴ��С��ͬ
        //��������д�˸����亯�����ұ��붨��Ϊ�麯����Ϊ��ʵ�ֺ���Ķ�̬����
        //������ų�Ա�޶���˵����������ֵ������ֵ
        virtual quote* clone()const&
        { return new quote(*this); }
        virtual quote* clone() &&                   //��ֵ�汾
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

//������࣬��Ϊ��������಻ͬ�Ĵ�ʩ����������discount��disc_num
//����˵�������һ����׼��discount��disc_num �Ϳ���˵��һ����׼��
class disc_quote : public quote
{
    public:
        disc_quote() = default;
        disc_quote(const std::string &book, double p, double disc, std::size_t num):
            quote(book, p), discount(disc), disc_num(num) { }
        double net_price(std::size_t sz)const = 0;   //���麯��

    protected:
        double discount;
        std::size_t disc_num;

    private:
};

//��һ�ִ��۷�ʽ
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
        //�Ե�һ�ִ�����ʵ�ֶ�̬����
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

//�������࣬ÿһ����Ľ�����Ϣ����������
class basket
{
    public:
        //������Ա��������һ����ɽ�������״�ŵ������У��ڶ�����ӡ�嵥���������ܼ۸�
        void add_item(const quote &sale){
            items.insert(std::shared_ptr<quote>(sale.clone()));
        }

        void add_item(quote && sale){
            items.insert(std::shared_ptr<quote>(std::move(sale).clone()));
        }

        double total_receipt(std::ostream &os)const;

    protected:

    private:
        //�Զ���ȽϺ���
        static bool compare(const std::shared_ptr<quote> &lhs, const std::shared_ptr<quote> &rhs)
        {
            return lhs->isbn() < rhs->isbn();
        }
        //˽�б������������ϣ���������
        std::multiset<std::shared_ptr<quote>, decltype(compare)*> items{compare};//decltype�����ƶϳ�ָ�������
};

//��ӡ���������嵥���������ܼ۸�
double basket::total_receipt(std::ostream &os) const
{
    double sum = 0.0;
    //ע����upper_bound������
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
