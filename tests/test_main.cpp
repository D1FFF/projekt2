#include <cassert>
#include <string>
#include <iostream>
#include <queue>
#include "funkcja.hpp"
#include <vector>
#include <sstream>
using namespace std;

int main() {
    auto input="10 1 * 23 +";
    auto ONP = wyrnaonp("10*10+23");
    assert(ONP.front()=="10");
    ONP.pop();
    assert(ONP.front()=="10");
    ONP.pop();
    assert(ONP.front()=="*");
    ONP.pop();
    assert(ONP.front()=="23");
    ONP.pop();
    assert(ONP.front()=="+");
    ONP.pop();
    return 0;
}