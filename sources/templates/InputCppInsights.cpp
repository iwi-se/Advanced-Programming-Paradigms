#include <iostream>
#include <string>

using namespace std;

template <int n = 0,int...pack> // no whitespace around ...
auto sum1()
{
   if constexpr (n == 0)
   {
      return 0;
   }
   else
   {
      return n + sum1<pack ...>();
   }
}

int main()
{
   cout << "sum1<>():\n" 
        << sum1<>() << endl;
   cout << "sum1<3,5,1>():\n" 
        << sum1<3,5,1>() << endl;
   cout << "======" << endl;
}
