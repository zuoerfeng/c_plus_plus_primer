#include "Message.h"

void Message::save(Folder &f)
{
    folders.insert(&f);    //message保存到flod,message的floder添加f
    f.addMsg(this);        //floder里面要add message
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.rmMsg(this);
}

//添加信息message,要对于每个包含message的添加message
void Message::add_to_Folders(const Message &msg)
{
    for(auto  &f : msg.folders)
        f->addMsg(this);
}

void Message::remove_from_Folders()
{
    //自己保存的每个floder删除自己
    for(auto  &f : folders)
        f->rmMsg(this);
}

//拷贝构造函数
Message::Message(const Message &msg):contents(msg.contents),folders(msg.folders)
{
    add_to_Folders(msg);
}

//赋值操作符
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

Message::Message(Message &&msg)                         //这两个函数可以有很多共有操作，可以换成一个私密函数来简化
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
