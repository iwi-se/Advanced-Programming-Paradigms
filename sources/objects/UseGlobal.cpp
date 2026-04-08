// UseGlobal.cpp by Ulrich Eisenecker, February 9, 2023

/* Global.cpp and UseGlobal.cpp belong together.
 * Both programs must be compiled separately and then linked, 
 * for example:
 * g++ -std=c++20 -c Global.cpp -o main.o
 * g++ -std=c++20 -c UseGlobal.cpp -o global.o
 * g++ -std=c++20 main.o global.o -o demo
*/

#include <iostream>
using namespace std;

extern int global;

class Global
{
   public:
      Global()
      {
          cout << "Global::Global()" << endl;
      }
      ~Global()
      {
         cout << "global: " << global << endl;
         cout << "Global::~Global()" << endl;
      }
} globalObject;

void useGlobal()
{
   cout << "UseGlobal.cpp - global: " << global << endl;
   ++global;
}
