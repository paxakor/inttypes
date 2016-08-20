#include <iostream>
#include <string>
#include <vector>
#include "../lib/inttypes.hpp"

using Type = pkr::uint56_t;
using std::cin;
using std::cout;
using std::endl;
using std::size_t;
using std::string;
using std::vector;

int main() {
  while (true) {
    Type a;
    size_t b;
    string cmd;
    cin >> a >> cmd >> b;
    if (cmd == "<<") {
      cout << (a << b) << endl;
    } else {
      cout << (a >> b) << endl;
    }
  }
  return 0;
}
