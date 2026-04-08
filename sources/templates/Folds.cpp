// Folds.cpp by Ulrich Eisenecker, June 29, 2023

#include <iostream>
using namespace std;

template <typename ... Pack>
auto subtractionUnaryRightFold(const Pack& ... pack)
{
   return (pack - ...);
}

template <typename ... Pack>
auto subtractionUnaryLeftFold(const Pack& ... pack)
{
   return (... - pack);
}

template <typename ... Pack>
auto subtractionBinaryRightFold(const Pack& ... pack)
{
   return (pack - ... - 0);
}

template <typename ... Pack>
auto subtractionBinaryLeftFold(const Pack& ... pack)
{
   return (0 - ... - pack);
}

int main()
{
   // cout << subtractionUnaryRightFold() << endl; // error
   cout << subtractionUnaryRightFold(10,5,2) << endl; // gives 7
   cout << subtractionUnaryLeftFold(10,5,2) << endl; // gives 3
   cout << subtractionBinaryRightFold() << endl; // gives 0
   cout << subtractionBinaryRightFold(10,5,2) << endl; // gives 7
   cout << subtractionBinaryLeftFold() << endl; // gives 0
   cout << subtractionBinaryLeftFold(10,5,2) << endl; // gives -17
}
