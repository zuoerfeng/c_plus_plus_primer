#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <initializer_list>
#include <algorithm>


class StrVec
{
    friend bool operator==(const StrVec &lhs, const StrVec &rhs);
    friend bool operator!=(const StrVec &lhs, const StrVec &rhs);
    friend bool operator<(const StrVec &lhs, const StrVec &rhs);
    public:
        StrVec():elements(nullptr), first_free(nullptr), cap(nullptr) { }
        //ʹ�ó�ʼֵ�б�Ĺ��캯������סinitializer_list����ȫ�ǳ������ҳ�ʼֵ�б���begin()��end(),����ʹ�÷�Χfor
        StrVec(const std::initializer_list<std::string>&il);
        StrVec(const StrVec &sv);
        StrVec(StrVec &&sv)noexcept; //�ƶ�����
        StrVec& operator=(const StrVec &sv);
        StrVec& operator=(StrVec &&sv)noexcept; //�ƶ���ֵ
        StrVec& operator=(const std::initializer_list<std::string>&il); //���ظ�ֵ�������
        ~StrVec();
        void push_back(const std::string &s);
        std::size_t size()const { return first_free - elements; }// const StrVec* const this
        std::size_t capacity()const { return cap - elements; }
        std::string* begin()const { return elements; }
        std::string* end()const { return first_free; }
        void reserve(std::size_t n);
        void resize(std::size_t n);

    private:
        //���ߺ���
        //����Ϊstatic�����ֻ��ʼ��һ�Σ����ڶ������ǰ�ͳ�ʼ�������ж�����һ����
        static std::allocator<std::string> alloc;//����Ԫ��
        void chk_n_alloc()
        { if(size() == capacity()) reallocate(); }
        std::pair<std::string*, std::string*>alloc_n_copy
            (const std::string*b, const std::string*e);
        void free();
        void reallocate();

        std::string *elements;     //��Ԫ��
        std::string *first_free;   //ĩԪ�ص���һ��λ��
        std::string *cap;          //������ڴ�ĩβ֮���λ��
};


#endif
