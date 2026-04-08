// Global.cpp by Ulrich Eisenecker, February 9, 2023

/* Global.cpp and UseGlobal.cpp belong together.
 * Both programs must be compiled separately and then linked, 
 * for example:
 * g++ -std=c++20 -c Global.cpp -o main.o
 * g++ -std=c++20 -c UseGlobal.cpp -o global.o
 * g++ -std=c++20 main.o global.o -o demo
*/

#include <iostream>
using namespace std;

int global;

void useGlobal();

int main()
{
   cout << "Global.cpp - global: " << global << endl;
   ++global;
   useGlobal();
   cout << "Global.cpp - global: " << global << endl;
}
