// ExceptionCorrectUse.cpp by Ulrich Eisenecker, August 21, 2023

#include <iostream>
#include <stdexcept>

using namespace std;

double division(int n,int d)
{
  if (d == 0)
  {
     throw overflow_error { "Division by zero" };
  }
  return static_cast<double>(n) / d;
}

int main()
{
   int numerator { }, denominator { };
   cout << "Numerator: ";
   cin >> numerator;
   double value;
   do
   {
      cout << "Denominator: ";
      cin >> denominator;
      if (denominator == 0)
      {
         cout << "Denominator must not be equal to 0."
              << "\nPlease retry." << endl;
      }
   } while (denominator == 0);
   value = division(numerator,denominator);
   cout << "Value = " << value << endl;
}
