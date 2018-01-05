
/*
 * Message类：
 * 消息类，可以存储或删除
 * 一个Message可以属于多个Floder
 */

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <iostream>
#include <set>
#include <memory>
#include <string>
#include "Folder.h"

class Message;
class Folder;

class Message
{
    friend void swap(Message &lhs, Message &rhs);
    friend std::istream& read(std::istream &in, Message &msg);
    friend std::ostream& print(std::ostream &os, Message &msg);
    friend class Folder;
    public:
        //隐式初始化为空，且避免隐式转换
        explicit Message(const std::string &s =  " "):
            contents(s) { }
        Message(const Message &msg);           //赋值形参，add
        Message(Message &&msg);                //移动拷贝
        Message& operator=(const Message &msg);//删除左值message，赋值右值add     三个拷贝控制成员都有交叉操作，所以定义private
        Message& operator=(Message &&msg);     //移动赋值
        ~Message();                            //删除message                      工具函数来处理，避免代码重复。提高效率
        //两个成员函数，从floders保存和删除message
        void save(Folder &f);
        void remove(Folder &f);

    private:
        std::string contents;        //message text
        std::set<Folder*>folders;   //message from floders  每个message包含多个指向floders的指针，指明它属于哪些floders
        void add_to_Folders(const Message &msg);
        void remove_from_Folders();
};


#endif
