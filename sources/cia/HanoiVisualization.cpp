// HanoiVisualization.cpp by Ulrich Eisenecker, July 12, 2025

#include <algorithm> // Because of std::max<>().
#include <iostream>
#include <stack>
#include <string>

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

void display(Peg a,Peg b,Peg c,NaturalNumber d = 0)
{
   auto prepareLine { [](size_t disks,size_t maxHeight,Peg& p)
                      {
                         string s { };
                         if (p.size() < maxHeight)
                         {
                            if (maxHeight > 1)
                            {
                               s += string(disks * 2 + 1,' ');
                            }
                            else
                            {
                               s += string(disks * 2,'_');
                               s += ' ';
                            }
                        }
                        else
                        {
                           s += string((disks - p.top()),' ');
                           s += string(p.top() * 2,'X');
                           s += string((disks - p.top()) + 1,' ');
                           p.pop();
                        }
                        return s;
                      }
                    };
   auto disks { a.size() + b.size() + c.size() };
   auto maxHeight { max({ a.size(),b.size(),c.size() }) };
   while (maxHeight)
   {
      cout << prepareLine(disks,maxHeight,a)
           << prepareLine(disks,maxHeight,b)
           << prepareLine(disks,maxHeight,c)
           << endl;
      --maxHeight;
   }
   if (d)
   {
      cout << "\nMoving disk " << d << ':' << std::endl;
   }
}

void move(Peg& left,Peg& middle,Peg& right)
{
   auto impl { [&](NaturalNumber count,Peg& l,Peg& m,Peg& r,auto&& impl) -> void
               {
                  if (count > 0)
                  {
                     impl(count - 1,l,r,m,impl);
                     display(left,middle,right,l.top());
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
   display(left,middle,right);
}
