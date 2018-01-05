#include "Folder.h"

 void Folder::addMsg(Message *msg)
 {
    _fold.insert(msg);
 }

 void Folder::rmMsg(Message *msg)
 {
    _fold.erase(msg);
 }
