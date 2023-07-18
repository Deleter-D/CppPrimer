#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> ivec;
    // size应为0，capacity依赖于具体实现
    cout << "ivec size: " << ivec.size() << ". capacity: " << ivec.capacity() << endl;
    for (vector<int>::size_type ix = 0; ix != 24; ++ix)
    {
        ivec.push_back(ix);
    }
    // size应为24，capacity应大于等于24，具体值依赖于标准库的实现
    cout << "ivec size: " << ivec.size() << ". capacity: " << ivec.capacity() << endl;

    ivec.reserve(50);
    // size应为24，capacity应大于等于50，具体值依赖于标准库的实现
    cout << "ivec size: " << ivec.size() << ". capacity: " << ivec.capacity() << endl;

    while (ivec.size() != ivec.capacity())
    {
        ivec.push_back(0);
    }
    ivec.push_back(42);
    // size应为51，capacity应大于等于51，具体值依赖于标准库的实现
    cout << "ivec size: " << ivec.size() << ". capacity: " << ivec.capacity() << endl;

    ivec.shrink_to_fit();
    // size应为51，capacity有可能是51，请求缩减到实际大小，但标准库并不保证退还内存
    cout << "ivec size: " << ivec.size() << ". capacity: " << ivec.capacity() << endl;
    return 0;
}

/*
                           容器大小管理操作
    —————————————————————————————————————————————————————————————
    shrink_to_fit只适用于vector、string和deque
    capacity和reserve只适用于vector和string
    —————————————————————————————————————————————————————————————
    c.shrink_to_fit() | 将capacity()减少为与size()相同的大小
    c.capacity()      | 不重新分配内存空间的情况下，c可以保存多少元素
    c.reserve(n)      | 分配至少能容纳n个元素的内存空间
    —————————————————————————————————————————————————————————————
    reserve并不改变容器中元素的数量，仅影响vector预分配的内存空间大小
*/