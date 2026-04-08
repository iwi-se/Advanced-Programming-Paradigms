// HanoiStack.cpp by Ulrich Eisenecker, July 11, 2025

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

void move(NaturalNumber disks,Peg& left,Peg& middle,Peg& right)
{
   if (disks > 0)
   {
      move(disks - 1,left,right,middle);
      cout << "Moving disk " << left.top();
      if (right.size())
      {
         cout << " on top of disk "
              << right.top()
              << '.' << endl;
      }
      else
      {
         cout << " on empty peg." << endl;
      }
      right.push(left.top());
      left.pop();
      move(disks - 1,middle,left,right);
   }
}

int main()
{
   NaturalNumber disks;
   cout << "Number of disks: ";
   cin >> disks;
   Peg left { init(disks) },
       middle,
       right;
   move(disks,left,middle,right);
   cout << "Right peg (in reverse order):";
   while (right.size())
   {
      cout << ' ' << right.top();
      right.pop();
   }
   cout << endl;
}
