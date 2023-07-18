#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H

#include <vector>
#include <string>
#include "26_Screen.h"

class Window_mgr
{
public:
    // 实际中类型名的定义尽量放在类的前面
    using ScreenIndex = std::vector<Screen>::size_type;

    void clear(ScreenIndex);

    ScreenIndex addScreen(const Screen &);

private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    // 由于指定了友元关系，Window_mgr可以访问Screen的私有成员
    s.contents = std::string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

#endif