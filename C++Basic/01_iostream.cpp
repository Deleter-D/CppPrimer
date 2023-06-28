#include <iostream>

int main()
{
    // 输入数量固定的数据
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The sum of " << v1 << " and " << v2 << " is " << v1 + v2 << std::endl;

    // 输入数量不固定的数据
    std::cout << "Enter numbers, end with a # or press ctrl+Z" << std::endl;
    int sum = 0, value = 0;
    while (std::cin >> value)
    {
        sum += value;
    }
    std::cout << "Sum is " << sum << std::endl;

    return 0;
}