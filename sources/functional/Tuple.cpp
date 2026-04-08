// Tuple.cpp by Ulrich Eisenecker, February 27, 2026

#include <print>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

struct Person
{
   string name;
   unsigned short int age;
};

bool operator<(const Person& p1,const Person& p2)
{
   return tie(p1.name,p1.age) < tie(p2.name,p2.age);
}

struct ExtendedPerson
{
   string name;
   unsigned short int age;
   double weight;
   vector<string> hobbies;
};

int main()
{
   Person p1 { "Pascale"s,90 };
   // println("{}",p); // not possible
   auto t1 { make_tuple(p1.name,p1.age) };
   println("{}",t1);

   Person p2 { "Torre"s,14 };
   println("(\"{}\", {}) < (\"{}\", {}) -> {}",
           p1.name,p1.age,p2.name,p2.age,p1 < p2);
   using PersonT = decltype(t1);
   PersonT t2 { p2.name,p2.age };
   println("{} > {} -> {}",t1,t2,t1 > t2);

   ExtendedPerson p3 { "Moonie"s,20,65.5,{ "Surfing"s,"Reading"s,"Math"s } };

   PersonT tPart { "Joao"s,24 };
   auto attributes { make_tuple(64.25,vector { "Tennis"s,"Magic"s }) };
   auto t3 { tuple_cat(tPart,attributes) };
   println("{}",t3);

   auto p4 { make_from_tuple<ExtendedPerson>(t3) };
   println("(\"{}\", {}, {}, {})",p4.name,p4.age,p4.weight,p4.hobbies);

   apply([](auto e1,auto e2)
         { println("(\"{}\", {})",e1,e2); },t2);
   apply([](auto e1,auto e2,auto e3,auto e4)
         { println("(\"{}\", {}, {}, {})",e1,e2,e3,e4); },t3);
   apply([]<typename ... E>(const E& ... e)
         { ((println("{}",e)), ...); },t3);
   ostringstream os;
   apply([&os]<typename ... E>(const E& ... e)
         { ((print(os,"{} ",e)), ...); },t3);
   println("{}",os.str());
}
