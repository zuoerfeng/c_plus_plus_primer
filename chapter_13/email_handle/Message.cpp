#include "Message.h"

void Message::save(Folder &f)
{
    folders.insert(&f);    //message���浽flod,message��floder���f
    f.addMsg(this);        //floder����Ҫadd message
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.rmMsg(this);
}

//�����Ϣmessage,Ҫ����ÿ������message�����message
void Message::add_to_Folders(const Message &msg)
{
    for(auto  &f : msg.folders)
        f->addMsg(this);
}

void Message::remove_from_Folders()
{
    //�Լ������ÿ��floderɾ���Լ�
    for(auto  &f : folders)
        f->rmMsg(this);
}

//�������캯��
Message::Message(const Message &msg):contents(msg.contents),folders(msg.folders)
{
    add_to_Folders(msg);
}

//��ֵ������
Message& Message::operator=(const Message &msg)
{
    remove_from_Folders();
    contents = msg.contents;
    folders = msg.folders;
    add_to_Folders(msg);
    return *this;
}

Message::~Message()
{
    remove_from_Folders();
}

std::istream& read(std::istream &in, Message &msg)
{
    in >> msg.contents;
    return in;
}

std::ostream& print(std::ostream &os, Message &msg)
{
    os << "Message:" << msg.contents << "\n";
    os << "Folders:";
    for(auto f : msg.folders)
        os << f->fold_name << " ";
    os << "\n";
    return os;
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap;

    for(auto f : lhs.folders)
        f->rmMsg(&lhs);
    for(auto f : rhs.folders)
        f->rmMsg(&rhs);
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for(auto f : lhs.folders)
        f->addMsg(&lhs);
    for(auto f : rhs.folders)
        f->addMsg(&rhs);
}

Message::Message(Message &&msg)                         //���������������кܶ๲�в��������Ի���һ��˽�ܺ�������
{
    contents = std::move(msg.contents);
    folders = std::move(msg.folders);
    for(auto f : folders)
    {
        f->rmMsg(&msg);
        f->addMsg(this);
    }
    msg.folders.clear();
}

Message& Message::operator=(Message &&msg)
{
    if(this != &msg)
    {
        remove_from_Folders();
        contents = std::move(msg.contents);
        folders = std::move(msg.folders);
        for(auto f : folders)
        {
            f->rmMsg(&msg);
            f->addMsg(this);
        }
        msg.folders.clear();
    }

    return *this;
}
