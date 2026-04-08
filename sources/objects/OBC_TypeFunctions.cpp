// OBC_TypeFunctions.cpp by Ulrich Eisenecker, January 5, 2023

#include <iostream>
using namespace std;

struct OBC
{
   double m_fuel;
};

OBC createOBC()
{
   return OBC { 0.0 };
}

double fuel(const OBC& obc)
{
   return obc.m_fuel;
}

void addFuel(OBC& obc,double fuel)
{
   obc.m_fuel += fuel;
}

void consumeFuel(OBC& obc,double fuel)
{
   obc.m_fuel -= fuel;
}

int main()
{
   auto obc { createOBC() };
   cout << "Fuel: " << fuel(obc) << endl;
   addFuel(obc,42.0);
   cout << "Fuel: " << fuel(obc) << endl;
   consumeFuel(obc,12.0);
   cout << "Fuel: " << fuel(obc) << endl;
}
