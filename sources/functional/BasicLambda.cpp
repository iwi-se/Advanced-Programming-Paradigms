// BasicLambda.cpp by Ulrich Eisenecker, November 14, 2025

#include <iostream>
#include <string>

using namespace std;

int main()
{
   cout << [](int i) { return i % 2 == 0 ? "even"s : "odd"s; } (42) << endl;
}
