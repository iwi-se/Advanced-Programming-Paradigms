// NonTypeTemplateParameter.cpp by Ulrich Eisenecker, October 1, 2024

#include <iostream>
using namespace std;

template <auto D>
struct S
{
   static const inline decltype(D) d { D };
};

int main()
{
   S<42.3> s;
   cout << s.d << endl;
}
