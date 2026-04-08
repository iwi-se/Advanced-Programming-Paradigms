// VariadicTemplates.cpp by Ulrich Eisenecker, June 22, 2023

#include <iostream>
#include <string>

using namespace std;

namespace quiet
{
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
}

namespace verbose
{
   template <int n = 0,int... pack> // whitespace after ...
   auto sum1()
   {
      cout << "sum1<" << n << ">()" << endl
           << "no of parameters: " << sizeof...(pack) << endl;
      if constexpr (n == 0)
      {
         return 0;
      }
      else
      {
         return n + sum1<pack ...>();
      }
   }
}

namespace quiet
{
   template <int ...pack> // whitespace before ...
   auto sum2()
   {
      return (0 + ... + pack);
   }
}

namespace verbose
{
   template <typename T,typename S>
   auto repeated(const T& n,S remaining) // helper function
   {
      cout << n;
      if (remaining > 0)
      {
         return ","s;
      }
      else
      {
         return ""s;
      }
   }

   template <int ... pack> // whitespace around ...
   auto sum2()
   {
      auto remaining { sizeof...(pack) };
      cout << "sum2<";
      ((cout << '*') << ... << repeated(pack,--remaining))
             << ">()" << endl
             << "no of parameters: " << sizeof...(pack) << endl;
      return (0 + ... + pack);
   }
}

namespace quiet
{
   template <typename T = double,typename... Pack>
   auto sum3(const T& n = T { },const Pack& ... pack)
   {
      if constexpr (sizeof...(pack) == 0)
      {
         return n;
      }
      else
      {
         return n + sum3(pack...);
      }
   }
}

namespace verbose
{
   template <bool once = true,typename T = double,typename... Pack>
   auto sum3(T n = T { },const Pack& ... pack)
   {
      if constexpr (once)
      {
         cout << "sum3(";
      }
      cout << n;
      if constexpr (sizeof...(pack) == 0)
      {
         cout << ')' << endl;
         return n;
      }
      else
      {
         cout << ',';
         return n + sum3<false>(pack...);
      }
   }
}

namespace quiet
{
   template <typename... Pack>
   auto sum4(const Pack& ... pack)
   {
      return (0.0 + ... + pack);
   }
}

namespace verbose
{
   template <typename... Pack>
   auto sum4(const Pack& ... pack)
   {
      auto remaining { sizeof...(pack) };
      cout << "sum4(";
      ((cout << '*') << ... << repeated(pack,--remaining))
             << ')' << endl;
      return (0.0 + ... + pack);
   }
}

using namespace verbose;

int main()
{
   cout << "sum1<>():\n"
        << sum1<>() << endl;
   cout << "sum1<3,5,1>():\n"
        << sum1<3,5,1>() << endl;
   cout << "======" << endl;

   cout << "sum2<>(): "
        << sum2<>() << endl;
   cout << "sum2<3,5,1>(): "
        << sum2<3,5,1>() << endl;
   cout << "======" << endl;

   cout << "sum3():\n"
        << sum3() << endl;
   cout << "sum3(99,1.5f,-0.001):\n"
        << sum3(99,1.5f,-0.001) << endl;
   cout << "======" << endl;

   cout << "sum4():\n"
        << sum4() << endl;
   cout << "sum4(99,1.5f,-0.001):\n"
        << sum4(99,1.5f,-0.001) << endl;
}
