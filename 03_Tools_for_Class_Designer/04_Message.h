#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <set>
#include <string>

class Folder;

class Message
{
    friend class Folder;

  public:
    // folders被隐式初始化为空集合
    explicit Message(const std::string &str = "") : contents(str)
    {
    }
    // 拷贝控制成员，用来管理指向本Message的指针
    Message(const Message &);            // 拷贝构造函数
    Message &operator=(const Message &); // 拷贝赋值运算符
    ~Message();                          // 析构函数
    // 从给定的Folder集合中添加/删除本Message
    void save(Folder &);
    void remove(Folder &);
    void swap(Message &lhs, Message &rhs);
    void Print(std::ostream &);
    void addFolder(Folder *); // 添加给定Folder
    void remFolder(Folder *); // 删除给定Folder

  private:
    std::string contents;       // 实际消息文本
    std::set<Folder *> folders; // 包含本Message的Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    void add_to_Folders(const Message &);
    // 从folders中的每个Folder中删除本Message
    void remove_from_Folders();
};

class Folder
{
    friend class Message;

  public:
    Folder(){};
    Folder(const Folder &);
    Folder &operator=(const Folder &);
    ~Folder();
    void addMsg(Message *);
    void remMsg(Message *);
    void Print(std::ostream &);

  private:
    std::set<Message *> messages;
    void add_to_Messages(const Folder &f);
    void remove_from_Messages();
};

void Message::save(Folder &f)
{
    folders.insert(&f); // 将给定Folder添加到Folder列表中
    f.addMsg(this);     // 将本Message添加到f的Message集合中
}

void Message::remove(Folder &f)
{
    folders.erase(&f); // 将给定Folder从Folder列表中删除
    f.remMsg(this);    // 将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders) // 对每个包含m的Folder
        f->addMsg(this);     // 向该Folder添加一个指向本Message的指针
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m); // 将本Message添加到指向m的Folder中
}

void Message::remove_from_Folders()
{
    for (auto f : folders) // 对folders中每个指针
        f->remMsg(this);   // 从该Folder中删除本Message
}

Message::~Message()
{
    remove_from_Folders();
}

Message &Message::operator=(const Message &rhs)
{
    // 通过先删除指针再插入它们来处理自赋值情况
    remove_from_Folders(); // 更新已有Folder
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs); // 将本Message添加到哪些Folder中
    return *this;
}

void Message::swap(Message &lhs, Message &rhs)
{
    using std::swap;
    // 将每个消息的指针从它原来所在的Folder中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    // 交换contents和Folder指针set
    swap(lhs.folders, rhs.folders);   // 使用swap(set&, set&)
    swap(lhs.contents, rhs.contents); // 使用swap(string&, string&)
    // 将每个Message的指针添加到它的新Folder中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

void Message::Print(std::ostream &os)
{
    os << "Message contents: " << contents << std::endl;
    os << "Belong to " << folders.size() << " folders." << std::endl;
}

void Message::addFolder(Folder *f)
{
    folders.insert(f);
}

void Message::remFolder(Folder *f)
{
    folders.erase(f);
}

void Folder::addMsg(Message *m)
{
    messages.insert(m);
}

void Folder::remMsg(Message *m)
{
    messages.erase(m);
}

void Folder::add_to_Messages(const Folder &f)
{
    for (auto m : f.messages) // 对目标Folder包含的每个Message
        m->addFolder(this);   // 将消息存入本Folder中
}

Folder::Folder(const Folder &f) : messages(f.messages)
{
    add_to_Messages(f);
}

void Folder::remove_from_Messages()
{
    for (auto m : messages) // 对messages中的每个指针
        m->remove(*this);   // 从本Folder中移除该Message
}

Folder::~Folder()
{
    remove_from_Messages();
}

Folder &Folder::operator=(const Folder &rhs)
{
    remove_from_Messages();
    messages = rhs.messages;
    add_to_Messages(rhs);
    return *this;
}

void Folder::Print(std::ostream &os)
{
    os << "This Folder has " << messages.size() << " messages." << std::endl;
    for (auto beg = messages.begin(), end = messages.end(); beg != end; ++beg)
    {
        (*beg)->Print(os);
        os << std::endl;
    }
}

#endif