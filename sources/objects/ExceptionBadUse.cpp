// ExceptionBadUse.cpp by Ulrich Eisenecker, August 21, 2023

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
   bool exceptionCaught { false };
   do
   {
      cout << "Denominator: ";
      cin >> denominator;
      exceptionCaught = false;
      try
      {
         value = division(numerator,denominator);
      }
      catch (const overflow_error& e)
      {
         cout << "Caught overflow_error exception: " << e.what()
              << "\nPlease retry." << endl;
         exceptionCaught = true;
      }
   } while (exceptionCaught);
   cout << "Value = " << value << endl;
}

