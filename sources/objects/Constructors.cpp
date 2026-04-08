// Constructors.cpp by Ulrich Eisenecker, February 9, 2023

/* This program requires rational_number.hpp and all associated files.
 * It is assumed that these files are located in a subdirectory named
 * rational_number. These files are part of the companion material to
 * Eisenecker, U. W. (2022). Basic programming paradigms (1.3).
 * University of Leipzig. https://www.wifa.uni-leipzig.de/institut-
 * fuer-wirtschaftsinformatik/professuren/professur-insbesondere-
 * softwareentwicklung/studium/lehrveranstaltungen/bpp
 * There they are located in the subdirectory sources/RatNumValSemOp.
 * Then, the program can be compiled to a.out like this:
 * g++ -std=c++20 Constructors.cpp rational_number/rational_number.cpp
 * rational_number/math_helper.cpp
 */

#include <iostream>
using namespace std;

#include "rational_number/rational_number.hpp"
using namespace rational_number;

void f(RationalNumber rn)
{
   rn.output(cout);
   cout << endl;
}

int main()
{
   {
      // Calling constructors with list initialization
      RationalNumber a { };
      RationalNumber b { 2 };
      RationalNumber c { 3,2 };
   }
   {
      // Creating temporary objects with list initialization
      f({ });
      f({ 2 });
      f({ 3,2 });
   }
   {
      // Calling constructors with classical syntax
      RationalNumber a;
      RationalNumber b1(2);
      RationalNumber b2 = { 3,1 };
      f(b2);
      RationalNumber c(3,2);
   }

   {
      // Creating temporary objects with classical syntax
      //f(); // Not legal
      f(42);
      //f(3,2) // Not legal
   }
}
