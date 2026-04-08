// ExceptionBasics.cpp by Ulrich Eisenecker, May 21, 2024

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
   cout << "Denominator: ";
   cin >> denominator;
   double value;
   bool exceptionCaught { false };
   try
   {
      value = division(numerator,denominator);
   }
   catch (const out_of_range& e)
   {
      cerr << "Caught out_of_range exception: " << e.what() << endl;
      exceptionCaught = true;
   }
   catch (const overflow_error& e)
   {
      cout << "Caught overflow_error exception: " << e.what() << endl;
      exceptionCaught = true;
   }
   if (!exceptionCaught)
   {
      cout << "Value = " << value << endl;
   }     
}
