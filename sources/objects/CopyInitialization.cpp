// CopyInitialization.cpp by Ulrich Eisenecker, February 13, 2023

/* This program requires rational_number.hpp and all associated files. 
 * It is assumed that these files are located in a subdirectory named 
 * rational_number. These files are part of the companion material to
 * Eisenecker, U. W. (2022). Basic programming paradigms (1.3). 
 * University of Leipzig. https://www.wifa.uni-leipzig.de/institut-
 * fuer-wirtschaftsinformatik/professuren/professur-insbesondere-
 * softwareentwicklung/studium/lehrveranstaltungen/bpp
 * There they are located in the subdirectory sources/RatNumValSemOp.
 * Then, the program can be compiled to a.out like this
 * g++ -std=c++20 Constructors.cpp rational_number/rational_number.cpp
 * rational_number/math_helper.cpp rational_number_operators.cpp
 */

#include <iostream>
using namespace std;

#include "rational_number/rational_number.hpp"
#include "rational_number/rational_number_operators.hpp"
using namespace rational_number;

void f(RationalNumber rn)
{
   rn.output(cout);
   cout << endl;
}

int main()
{
   {
      // Calling constructors with copy initialization
      RationalNumber a = { };
      RationalNumber b = { 2 };
      RationalNumber c = { 3,2 };
      cout << a << '\t' << b << '\t' << c << endl;
   }
}
