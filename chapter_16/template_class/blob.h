#ifndef _BLOB_H_
#define _BLOB_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <stdexcept>
//#include "strblob.h"

//必须声明
template<typename T> class blobptr;
template<typename T> class blob;
template<typename T>
    bool operator==(const blob<T>&, const blob<T>&);

template <typename T>
class blob
{
        friend class blobptr<T>;
        friend bool operator==<T>(const blob<T>&, const blob<T>&);
    public:
        typedef T value_type;
        //加上typename 是因为T是一个模板类型，编译器不知道std::vector<T>::size_type 是什么,加上typename就是告诉编译器是一个type
        typedef typename std::vector<T>::size_type size_type;

        blob();
        blob(std::initializer_list<T> il);

        size_type size()const { return data->size(); }
        bool empty()const { return data->empty(); }
        void push_back(const T&t) { return data->push_back(t); }
        void push_back(T &&t) { return data->push_back(std::move(t)); }
        void pop_back();


        T& back();
        T& front();
        T& operator[] (size_type i);
        const T& operator[](size_type i)const;

    private:
        void check(size_type i, const std::string &s)const;
        std::shared_ptr<std::vector<T>> data;
};

//类模板的成员函数必须具有和模板相同的模板参数
template<typename T>
blob<T>::blob():data(std::make_shared<std::vector<T>>()) { }

template<typename T>
blob<T>::blob(std::initializer_list<T> il):
    data(std::make_shared<std::vector<T>>(il)) { }


template<typename T>
void blob<T>::check(size_type i, const std::string &s)const
{
    if(i >= data->size())
        throw std::out_of_range(s);
}

template<typename T>
void blob<T>::pop_back()
{
    check(0, "pop_back on empty blob");
    data->pop_back();
}

template<typename T>
T& blob<T>::front()
{
    check(0, "back on empty blob");
    return data->front();
}

template<typename T>
T& blob<T>::back()
{
    check(0, "back on empty blob");
    return data->back();
}

template<typename T>
T& blob<T>::operator[](blob<T>::size_type i)
{
    check(i, "subscript out of range");
    return static_cast<T>(const_cast<const blob<T>>(*this)[i]);
}

template<typename T>
const T& blob<T>::operator[](blob<T>::size_type i)const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

#endif
