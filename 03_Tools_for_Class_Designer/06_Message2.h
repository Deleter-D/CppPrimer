#ifndef MESSAGE2_H
#define MESSAGE2_H

#include <iostream>
#include <set>
#include <string>

class Folder;

class Message {
  friend class Folder;

public:
  explicit Message(const std::string &str = "") : contents(str) {}
  Message(const Message &);
  // 添加移动构造函数
  Message(Message &&m) : contents(std::move(m.contents)) { move_Folders(&m); }
  Message &operator=(const Message &);
  // 添加移动赋值运算符
  Message &operator=(Message &&);
  ~Message();
  void save(Folder &);
  void remove(Folder &);
  void swap(Message &lhs, Message &rhs);
  void Print(std::ostream &);
  void addFolder(Folder *);
  void remFolder(Folder *);

private:
  std::string contents;
  std::set<Folder *> folders;

  void add_to_Folders(const Message &);

  void remove_from_Folders();
  // 从本Message移动Folder指针
  void move_Folders(Message *m);
};

void Message::move_Folders(Message *m) {
  folders = std::move(m->folders); // 使用set的移动赋值运算符
  for (auto f : folders) {
    f->remMsg(m);    // 从Folder中删除旧Message
    f->addMsg(this); // 将本Message添加到Folder中
  }
  m->folders.clear(); // 确保销毁m是无害的
}

Message &Message::operator=(Message &&rhs) {
  if (this != &rhs) {
    remove_from_Folders();
    contents = std::move(rhs.contents); // 移动赋值运算符
    move_Folders(&rhs);                 // 重置Folders指向本Message
  }
  return *this;
}

class Folder {
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

void Message::save(Folder &f) {
  folders.insert(&f);
  f.addMsg(this);
}

void Message::remove(Folder &f) {
  folders.erase(&f);
  f.remMsg(this);
}

void Message::add_to_Folders(const Message &m) {
  for (auto f : m.folders)
    f->addMsg(this);
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
  add_to_Folders(m);
}

void Message::remove_from_Folders() {
  for (auto f : folders)
    f->remMsg(this);
}

Message::~Message() { remove_from_Folders(); }

Message &Message::operator=(const Message &rhs) {

  remove_from_Folders();
  contents = rhs.contents;
  folders = rhs.folders;
  add_to_Folders(rhs);
  return *this;
}

void Message::swap(Message &lhs, Message &rhs) {
  using std::swap;

  for (auto f : lhs.folders)
    f->remMsg(&lhs);
  for (auto f : rhs.folders)
    f->remMsg(&rhs);

  swap(lhs.folders, rhs.folders);
  swap(lhs.contents, rhs.contents);

  for (auto f : lhs.folders)
    f->addMsg(&lhs);
  for (auto f : rhs.folders)
    f->addMsg(&rhs);
}

void Message::Print(std::ostream &os) {
  os << "Message contents: " << contents << std::endl;
  os << "Belong to " << folders.size() << " folders." << std::endl;
}

void Message::addFolder(Folder *f) { folders.insert(f); }

void Message::remFolder(Folder *f) { folders.erase(f); }

void Folder::addMsg(Message *m) { messages.insert(m); }

void Folder::remMsg(Message *m) { messages.erase(m); }

void Folder::add_to_Messages(const Folder &f) {
  for (auto m : f.messages)
    m->addFolder(this);
}

Folder::Folder(const Folder &f) : messages(f.messages) { add_to_Messages(f); }

void Folder::remove_from_Messages() {
  for (auto m : messages)
    m->remove(*this);
}

Folder::~Folder() { remove_from_Messages(); }

Folder &Folder::operator=(const Folder &rhs) {
  remove_from_Messages();
  messages = rhs.messages;
  add_to_Messages(rhs);
  return *this;
}

void Folder::Print(std::ostream &os) {
  os << "This Folder has " << messages.size() << " messages." << std::endl;
  for (auto beg = messages.begin(), end = messages.end(); beg != end; ++beg) {
    (*beg)->Print(os);
    os << std::endl;
  }
}

#endif