// HanoiSmarter.cpp by Ulrich Eisenecker, July 11, 2025

#include <iostream>
#include <stack>

using namespace std;

using NaturalNumber = unsigned short int;
using Peg = stack<NaturalNumber>;

Peg init(NaturalNumber numberOfValues)
{
   Peg result;
   while (numberOfValues)
   {
      result.push(numberOfValues--);
   }
   return result;
}

void move(Peg& left,Peg& middle,Peg& right)
{
   auto impl { [](NaturalNumber count,Peg& l,Peg& m,Peg& r,auto&& impl) -> void
               {
                  if (count > 0)
                  {
                     impl(count - 1,l,r,m,impl);
                     cout << "Moving disk " << l.top();
                     if (r.size())
                     {
                        cout << " on top of disk "
                             << r.top()
                             << '.' << endl;
                     }
                     else
                     {
                        cout << " on empty peg." << endl;
                     }
                     r.push(l.top());
                     l.pop();
                     impl(count - 1,m,l,r,impl);
                  }
               }
             };

   impl(left.size(),left,middle,right,impl);
}

int main()
{
   NaturalNumber disks;
   cout << "Number of disks: ";
   cin >> disks;
   Peg left { init(disks) },
       middle,
       right;
   move(left,middle,right);
   cout << "Right peg (in reverse order):";
   while (right.size())
   {
      cout << ' ' << right.top();
      right.pop();
   }
   cout << endl;
}
