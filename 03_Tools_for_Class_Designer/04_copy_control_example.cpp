#include "04_Message.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    Message msg1("Hello");
    Message msg2("World");
    Folder folder1;
    Folder folder2;
    folder1.addMsg(&msg1);
    folder1.addMsg(&msg2);
    msg1.save(folder2);

    ostream &os = cout;
    folder1.Print(os);
    folder2.Print(os);

    return 0;
}