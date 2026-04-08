// TerminalOutput.cpp by Ulrich Eisenecker, February 16, 2024

#include <iostream>
#include <string>

using namespace std;

int main()
{
   string s;
   while (cin)
   {
      getline(cin,s);
      if (cin)
      {
         cout << s << endl;
      }   
   }
}
