#include "list.h"
#include <iostream>
using namespace std;

int main() {
  List<int> list;
  for (unsigned i = 0; i < 3; i++) { list.insertFront(i); }
  list.reverse();
  cout<<list<<endl;
  return 0;
}
