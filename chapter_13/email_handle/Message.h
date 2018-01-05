
/*
 * Message�ࣺ
 * ��Ϣ�࣬���Դ洢��ɾ��
 * һ��Message�������ڶ��Floder
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
        //��ʽ��ʼ��Ϊ�գ��ұ�����ʽת��
        explicit Message(const std::string &s =  " "):
            contents(s) { }
        Message(const Message &msg);           //��ֵ�βΣ�add
        Message(Message &&msg);                //�ƶ�����
        Message& operator=(const Message &msg);//ɾ����ֵmessage����ֵ��ֵadd     �����������Ƴ�Ա���н�����������Զ���private
        Message& operator=(Message &&msg);     //�ƶ���ֵ
        ~Message();                            //ɾ��message                      ���ߺ�����������������ظ������Ч��
        //������Ա��������floders�����ɾ��message
        void save(Folder &f);
        void remove(Folder &f);

    private:
        std::string contents;        //message text
        std::set<Folder*>folders;   //message from floders  ÿ��message�������ָ��floders��ָ�룬ָ����������Щfloders
        void add_to_Folders(const Message &msg);
        void remove_from_Folders();
};


#endif
