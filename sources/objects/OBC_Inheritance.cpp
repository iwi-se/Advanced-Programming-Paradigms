// OBC_Inheritance.cpp by Ulrich Eisenecker, April 8, 2024

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

class OBCA: public OBC
{
   public:
      OBCA(): OBC { }, m_mileage { 0.0 }
      {}
      double mileage() const
      {
         return m_mileage;
      }
      void addMileage(double distance)
      {
         m_mileage += distance;
      }
   private:
      double m_mileage;
};

void testFuel(OBC& obc)
{
   cout << "Fuel: " << obc.fuel() << endl;
   obc.addFuel(42.0);
   cout << "Fuel: " << obc.fuel() << endl;
   obc.consumeFuel(12.0);
   cout << "Fuel: " << obc.fuel() << endl;
}

int main()
{
   OBC obc;
   testFuel(obc);

   OBCA obca;
   testFuel(obca);
   cout << "Mileage: " << obca.mileage() << endl;
   obca.addMileage(200.0);
   cout << "Mileage: " <<obca.mileage() << endl;
}
