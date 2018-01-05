#include "vector.h"

void StrVec::push_back(const std::string &s)//������const�ķ������Ϊ��ʼֵ�б�Ĺ��캯�������
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    //���·���һ���ڴ�
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b,e,data)};
}

/*
void StrVec::free()
{
    if(elements)
    {
        for(auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}
*/

//���������free�ã����for_each()����ķ�Χ�ǵ���������������벻��������
void StrVec::free()
{
    if(elements)
    {
        std::for_each(elements, first_free, [](std::string &s) { alloc.destroy(&s); });
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec& sv)
{
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec& StrVec::operator=(const StrVec &sv)
{
    auto data = alloc_n_copy(sv.begin(), sv.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    //auto newcapacity = 2 * size();  error
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    //for(; elem != first_free;)      error
    //    *dest++ = *elem++;
    for(std::size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve(std::size_t n)
{
    if(n > capacity())
    {
        auto newcapacity = n;
        auto newdata = alloc.allocate(newcapacity);
        auto dest = newdata;
        auto elem = elements;
        for(std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + n;
    }
}

void StrVec::resize(std::size_t n)
{
    std::size_t t = n - size();
    if(n < size())
    {
        while(n--)
        {
            alloc.destroy(--first_free);
        }
    }
    else if(n > size() && n <= capacity())
    {
        for(std::size_t i = 0; i < t; ++i)
        {
            alloc.construct(first_free+i, " ");
        }
    }
    else if(n > capacity())
    {
        auto newcapacity = n;
        auto newdata = alloc.allocate(newcapacity);
        auto dest = newdata;
        auto elem = elements;
        for(std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        for(std::size_t i = size(); i <= capacity(); ++i)
            alloc.construct(dest++, " ");
        free();
        elements = newdata;
        first_free = newdata+n;
        cap = newdata+n;
    }
}

StrVec::StrVec(const std::initializer_list<std::string>&il):
    elements(nullptr), first_free(nullptr), cap(nullptr)
{

    for(const std::string p : il)
    {
        push_back(p);
    }
}

StrVec::StrVec(StrVec &&sv)noexcept
{
    elements = sv.elements;
    first_free = sv.first_free;
    cap = sv.cap;
    sv.elements = sv.first_free = sv.cap = nullptr;   //ȷ���ƶ�Դ���ڿ�����״̬
}

StrVec& StrVec::operator=(StrVec &&sv)noexcept
{
    if(this != &sv) //�ж��Ƿ��Ը�ֵ
    {
        free();
        elements = sv.elements;
        first_free = sv.first_free;
        cap = sv.cap;
        sv.elements = sv.first_free = sv.cap = nullptr;
    }
    return *this;
}

StrVec& StrVec::operator=(const std::initializer_list<std::string>&il)
{
    auto data = alloc_n_copy(il.begin(), il.end());    //����Ҫ�����Ը�ֵ
    free();
    elements = data.first;                             //data��pair
    first_free = cap = data.second;
    return *this;
}

bool operator==(const StrVec &lhs, const StrVec &rhs)
{
    return lhs.elements == rhs.elements &&
        lhs.first_free == rhs.first_free &&
        lhs.cap == rhs.cap;
}

bool operator!=(const StrVec &lhs, const StrVec &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const StrVec &lhs, const StrVec &rhs)
{
    auto lhs_address = lhs.elements;
    auto rhs_address = rhs.elements;
    while(lhs_address != lhs.first_free &&  rhs_address != rhs.first_free)
    {
        if(*lhs_address < *rhs_address)
        {
            return true;
        }
        else if(*lhs_address > *rhs_address)
        {
            return false;
        }
        lhs_address++;
        rhs_address++;
    }
    if(lhs_address != lhs.first_free)
    {
        return false;
    }
    else
    {
        return true;
    }
}
