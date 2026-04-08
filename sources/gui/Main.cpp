// Main.cpp by Ulrich Eisenecker, February 5, 2024

#include <iostream>
using namespace std;

int main(int argc,char* argv[])
{
   for (int index { 0 };index < argc; ++index)
   {
      cout << index << '\t' << argv[index] << endl;
   }
   return argc;
}
