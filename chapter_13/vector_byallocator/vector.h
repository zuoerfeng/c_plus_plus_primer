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
        //使用初始值列表的构造函数，记住initializer_list里面全是常量，且初始值列表含有begin()和end(),可以使用范围for
        StrVec(const std::initializer_list<std::string>&il);
        StrVec(const StrVec &sv);
        StrVec(StrVec &&sv)noexcept; //移动拷贝
        StrVec& operator=(const StrVec &sv);
        StrVec& operator=(StrVec &&sv)noexcept; //移动赋值
        StrVec& operator=(const std::initializer_list<std::string>&il); //重载赋值运算符。
        ~StrVec();
        void push_back(const std::string &s);
        std::size_t size()const { return first_free - elements; }// const StrVec* const this
        std::size_t capacity()const { return cap - elements; }
        std::string* begin()const { return elements; }
        std::string* end()const { return first_free; }
        void reserve(std::size_t n);
        void resize(std::size_t n);

    private:
        //工具函数
        //设置为static很巧妙，只初始化一次，且在对象分配前就初始化，所有对象共用一个。
        static std::allocator<std::string> alloc;//分配元素
        void chk_n_alloc()
        { if(size() == capacity()) reallocate(); }
        std::pair<std::string*, std::string*>alloc_n_copy
            (const std::string*b, const std::string*e);
        void free();
        void reallocate();

        std::string *elements;     //首元素
        std::string *first_free;   //末元素的下一个位置
        std::string *cap;          //分配的内存末尾之后的位置
};


#endif
