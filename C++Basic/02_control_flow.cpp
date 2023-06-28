#include <iostream>

int main()
{
    // while循环
    int sum = 0, val = 1;
    while (val <= 10)
    {
        sum += val;
        ++val;
    }

    // for循环
    int sum = 0;
    for (int val = 1; val <= 10; val++)
    {
        sum += val;
    }

    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;

    // if语句
    int currVal = 0, val = 0;
    // 统计某个数连续出现多少次
    if (std::cin >> currVal) // 读取第一个数，确保有数据可处理
    {
        int count = 1; // 保存当前数的个数
        while (std::cin >> val)
        {
            if (val == currVal) // 若值相同则数量加1
            {
                ++count;
            }
            else
            {
                std::cout << currVal << " occurs " << count << " times" << std::endl;
                currVal = val;
                count = 1;
            }
        }
        std::cout << currVal << " occurs " << count << " times" << std::endl;
    }

    return 0;
}