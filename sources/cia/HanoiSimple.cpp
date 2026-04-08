// HanoiSimple.cpp by Ulrich Eisenecker, July 11, 2025

#include <iostream>

using namespace std;

using NaturalNumber = unsigned short int;

void move(NaturalNumber disks,char left,char middle,char right)
{
   if (disks > 0)
   {
      move(disks - 1,left,right,middle);
      cout << "Moving top disk from " << left << " to " << right << '.' << endl;
      move(disks - 1,middle,left,right);
   }
}

int main()
{
   NaturalNumber disks;
   cout << "Number of disks: ";
   cin >> disks;
   move(disks,'l','m','r');
}
