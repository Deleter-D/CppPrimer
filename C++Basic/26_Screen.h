#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>
#include "26_Window_mgr.h"

class Screen
{
    // 类之间的友元关系
    // Window_mgr整个类现在可以直接访问Screen的私有成员
    friend class Window_mgr;
    // 也可以只针对某个函数开放
    // 注意：涉及到重载函数时，必须非常明确，重载函数是不同的函数
    // 但这样做要注意声明与定义的顺序问题
    friend void Window_mgr::clear(ScreenIndex);
    // 1、定义Window_mgr类，声明clear函数，但不能定义它
    // 2、定义Screen类，包括对于clear的友元声明
    // 3、定义clear，此时才能使用Screen的成员

public:
    // Screen的用户不需要知道Screen使用了一个string对象来存放它的数据，pos隐藏了细节
    using pos = std::string::size_type; // typedef std::string::size_type pos;

    Screen() = default;
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}

    // 成员函数也支持重载
    char get() const { return contents[cursor]; } // 隐式内联
    inline char get(pos ht, pos wd) const;        // 显式内联
    Screen &move(pos r, pos c);                   // 能在之后被设为内联

    void some_member() const;

    // 返回*this的成员函数
    Screen &set(char);
    Screen &set(pos, pos, char);

    //从const成员函数返回*this
    Screen &display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }

    const Screen &display(std::ostream &os) const
    {
        do_display(os);
        return *this;
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    // 可变数据成员
    mutable size_t access_ctr; // 即使在一个const对象内也能被修改

    void do_display(std::ostream &os) const { os << contents; }
};

inline Screen &Screen::move(pos r, pos c)
{
    pos row = r * width; // 计算行的位置
    cursor = row + c;    // 计算行内偏移
    return *this;
}

char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}

void Screen::some_member() const
{
    ++access_ctr; // 记录成员函数被调用的次数
    // TODO
}

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char c)
{
    contents[r * width + col] = c;
    return *this;
}

#endif