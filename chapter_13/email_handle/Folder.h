
#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <iostream>
#include <set>
#include <string>

class Folder;
class Message;

class Folder
{
    friend std::istream& read(std::istream &in, Message &msg);
    friend std::ostream& print(std::ostream &os, Message &msg);
    friend class Message;
    public:
        Folder(const std::string &s = " "):
            fold_name(s) { }
        ~Folder() { }
        void addMsg(Message *msg); //ɾ��message
        void rmMsg(Message *msg);  //���message

    private:
        std::set<Message*>_fold;   //����message��flod
        std::string fold_name;
};

#endif
