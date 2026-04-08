// Explicit.cpp by Ulrich Eisenecker, February 13, 2023

#include "OBCHE.hpp"
#include <iostream>

using namespace std;

void printInfos(const OBCE& o)
{
   cout << "mileage: " << o.mileage() << endl
        << "remaining capacity: " << o.capacity() << endl
        << "remaining range: " << o.remainingRange() << endl;
}

int main()
{
   OBCE anOBCE { 15.0 };
   anOBCE.charge(45.0);
   anOBCE.drive(75.0);
   printInfos(anOBCE); // That's fine!
   printInfos(99.9); // No longer possible.
   printInfos('*'); // No longer possible.
   printInfos(false); // No longer possible.
}
