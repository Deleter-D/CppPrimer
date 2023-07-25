#include "12_AndQuery.h"
#include "12_NotQuery.h"
#include "12_OrQuery.h"
#include "12_Query.h"
#include "12_TextQuery.h"
#include "12_WordQuery.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void runQueries(ifstream &infile);
std::ostream &print(std::ostream &os, const QueryResult &qr);

int main(int argc, char const *argv[]) {
  /*
  ifstream infile;

  if (argc < 2 || !(infile.open(argv[1]), infile)) {
    cerr << "No such file." << endl;
    return EXIT_FAILURE;
  }
  runQueries(infile);
  */

  ifstream infile;
  infile.open("./12_test.txt");
  TextQuery tq(infile);
  // Query q("the");
  // Query q = Query("Alice") | Query("the") | Query("she");
  // Query q = ~Query("Alice") & Query("her") | Query("alive");
  Query q(~Query("Alice"));
  auto res = q.eval(tq);
  print(cout, res);

  return 0;
}

void runQueries(ifstream &infile) {
  TextQuery tq(infile);

  while (true) {
    cout << "enter word to look for, or q to quit: ";
    string s;
    if (!(cin >> s) || s == "q")
      break;
    print(cout, tq.query(s)) << endl;
  }
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
  os << qr.sought << " occurs " << qr.lines->size() << " "
     << ((qr.lines->size() > 1) ? "times" : "time") << std::endl;
  for (auto num : *qr.lines)
    os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num)
       << std::endl;
  return os;
}