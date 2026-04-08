// OBCC.cpp by Ulrich Eisenecker, April 9, 2024

#include <iostream>
using namespace std;

class OBCC
{
   public:
      OBCC(const double consumption): m_fuel { 0.0 }, m_mileage { 0.0 },
                                      m_consumption { consumption }
      {}
      [[nodiscard]] double fuel() const
      {
         return m_fuel;
      }
      void addFuel(double fuel)
      {
         m_fuel += fuel;
      }
      double drive(double distance)
      {
         auto requiredFuel { distance / 100.0 * m_consumption };
         if (requiredFuel > m_fuel)
         {
            distance = m_fuel * 100.0 / m_consumption;
            requiredFuel = m_fuel;
         } 
         m_fuel -= requiredFuel;
         m_mileage += distance;
         return distance;
      }
      [[nodiscard]] double remainingRange() const
      {
         return m_fuel * 100.0 / m_consumption;
      }
      [[nodiscard]] double mileage() const
      {
         return m_mileage;
      }
   private:
      double m_fuel, // liter or gallons
             m_mileage; // km or miles
      const double m_consumption; // liter or gallons per 100 km or miles
};

int main()
{
   OBCC obcc { 7.5 };
   obcc.addFuel(35.0);
   cout << "remaining range: " << obcc.remainingRange() << endl;
   auto coveredDistance { obcc.drive(150.0) };
   cout << "covered distance: " << coveredDistance << endl;
   cout << "odometer reading: " << obcc.mileage() << endl;
   cout << "remaining range: " << obcc.remainingRange() << endl;
   coveredDistance = obcc.drive(400);
   cout << "covered distance: " << coveredDistance << endl;
   cout << "odometer reading: " << obcc.mileage() << endl;
   cout << "remaining range: " << obcc.remainingRange() << endl;
}
