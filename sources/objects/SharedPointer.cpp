// Discussion.cpp by Ulrich Eisenecker, May 31, 2025

#include <iostream>
#include <memory>
#include <string>
using namespace std;

void info(string msg,shared_ptr<string>& sp)
{
   cout << msg << '\t'
        << "use count: " << sp.use_count()
        << ", ";
   if (sp)
   {
      cout << '\"' << *sp << '\"';
   }
   else
   {
      cout << "nullptr";
   }
   cout << endl;
}

int main()
{
   cout << "Two shared pointers that share the same object." << endl;
   auto sp1 { make_shared<string>("ok?") };
   info("sp1 = make_shared<string>(\"ok?i\"s)",sp1);
   auto sp2 { sp1 };
   info("sp2 { sp1 };                      ",sp2);
   *sp1 = "OK!";
   info("*sp1 = \"OK!\";                     ",sp1);
   info("sp2                               ",sp2);
   cout << "Stop sharing now." << endl;
   sp1.reset();
   info("sp1.reset();                      ",sp1);
   info("sp2                               ",sp2);

   cout << "\nTwo shared pointers that do not share the same object." << endl;
   shared_ptr<string> sp3 { };
   info("shared_ptr<string> sp3 { };       ",sp3);
   auto sp4 { sp3 };
   info("auto sp4 { sp3 } ;                ",sp4);
   sp3 = make_shared<string>("?!"s);
   info("sp3 = make_shared<string>(\?!i\"s); ",sp3);
   info("sp4                               ",sp4);
   cout << "Start sharing now." << endl;
   sp4 = sp3;
   info("sp4 = sp3;sp4                       ",sp4);
}
