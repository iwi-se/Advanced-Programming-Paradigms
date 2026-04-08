// HOFasReturnValue.cpp by Ulrich Eisenecker, March 31, 2026

#include <iostream>
#include <map>
#include <utility> // Because of make_pair<>()

double add(double a,double b)
{
   return a + b;
}

double subtract(double a,double b)
{
   return a - b;
}

double multiply(double a,double b)
{
   return a * b;
}

double divide(double a,double b)
{
   return a / b;
}

double unknown(double a,double b)
{
   return { };
}

auto classify(double a,double b,double result)
{
   if (add(a,b) == result)
   {
      return add;
   }
   if (subtract(a,b) == result)
   {
      return subtract;
   }
   if (multiply(a,b) == result)
   {
      return multiply;
   }
   if (divide(a,b) == result)
   {
      return divide;
   }
   return unknown;
}

using namespace std;

int main()
{
   map f2n { make_pair(add,"add"),
             make_pair(subtract,"subtract"),
             make_pair(multiply,"multiply"),
             make_pair(divide,"divide"),
             make_pair(unknown,"unknown")
           };
   cout << f2n[classify(17.0,4.0,21.0)] << endl;
   cout << f2n[classify(1.1,2.2,0.0)] << endl;
}
