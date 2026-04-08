// OBC_TypeFunctionsAdvanced.cpp by Ulrich Eisenecker, January 5, 2023

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

struct OBCA
{
   double m_mileage,
          m_fuel;
};

OBCA createOBCA()
{
   return OBCA { 0.0, 0.0 };
}

double fuel(const OBCA& obc)
{
   return obc.m_fuel;
}

void addFuel(OBCA& obc,double fuel)
{
   obc.m_fuel += fuel;
}

void consumeFuel(OBCA& obc,double fuel)
{
   obc.m_fuel -= fuel;
}

double mileage(const OBCA& obc)
{
   return obc.m_mileage;
}

void addMileage(OBCA& obc,double distance)
{
   obc.m_mileage += distance;
}

int main()
{
   auto obc { createOBC() };
   cout << "Fuel: " << fuel(obc) << endl;
   addFuel(obc,42.0);
   cout << "Fuel: " << fuel(obc) << endl;
   consumeFuel(obc,12.0);
   cout << "Fuel: " << fuel(obc) << endl;

   auto obca { createOBCA() };
   cout << "Fuel: " << fuel(obca) << endl;
   cout << "Mileage: " << mileage(obca) << endl;
   addFuel(obca,42.0);
   cout << "Fuel: " << fuel(obca) << endl;
   addMileage(obca,200.0);
   consumeFuel(obca,12.0);
   cout << "Fuel: " << fuel(obca) << endl;
   cout << "Mileage: " << mileage(obca) << endl;
}
