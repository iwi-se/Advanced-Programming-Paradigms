// CRV.cpp by Ulrich Eisenecker, March 16, 2026

#include <algorithm>
#include <ranges>
#include <print>
#include <vector>

using namespace std;

int main()
{
   vector c { 1,2,3 };
   println("container: {}",c);

   transform(begin(c),end(c),begin(c),[](auto e) { return e * e; });
   println("container + transform: {}",c);

   ranges::range auto& r { c };
   ranges::transform(r,begin(r),[](auto e) { return e + 1; });
   println("range + transform: {}",r);

   auto v1 { views::transform(c,[](auto e) { return -e; }) };
   println("view(c) + transform: {}",v1);

   auto v2 { views::transform(r,[](auto e) { return e / 2; }) };
   println("view(r) + transform: {}",v2);

   auto v3 { views::transform(r,[](auto e)
                                { print("{} ",e);return 10 * e; }) };
   println("before outputting v3");
   println("views are lazy: {}",v3);

   println("container: {}",c);
}
