#include "18_TextQuery.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void runQueries(ifstream &infile);
std::ostream &print(std::ostream &os, const QueryResult &qr);

int main(int argc, char const *argv[])
{
    ifstream infile;

    if (argc < 2 || !(infile.open(argv[1]), infile))
    {
        cerr << "No such file." << endl;
        return EXIT_FAILURE;
    }
    runQueries(infile);
    return 0;
}

void runQueries(ifstream &infile)
{
    TextQuery tq(infile);

    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " << ((qr.lines->size() > 1) ? "times" : "time")
       << std::endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}