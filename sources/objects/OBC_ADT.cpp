// OBC_ADT.cpp by Ulrich Eisenecker, January 5, 2023

#include <iostream>
using namespace std;

class OBC
{
   public:
      OBC(): m_fuel { 0.0 }
      {}
      double fuel() const
      {
         return m_fuel;
      }
      void addFuel(double fuel)
      {
         m_fuel += fuel;
      }
      void consumeFuel(double fuel)
      {
         m_fuel -= fuel;
      }
   private:
      double m_fuel;
};

int main()
{
   OBC obc;
   cout << "Fuel: " << obc.fuel() << endl;
   obc.addFuel(42.0);
   cout << "Fuel: " << obc.fuel() << endl;
   obc.consumeFuel(12.0);
   cout << "Fuel: " << obc.fuel() << endl;
}
