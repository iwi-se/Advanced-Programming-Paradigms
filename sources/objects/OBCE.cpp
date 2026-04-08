// OBCE.cpp by Ulrich Eisenecker, April 9, 2024

#include <iostream>
using namespace std;

class OBCE
{
   public:
      OBCE(const double efficiency): m_capacity { 0.0 },m_mileage { 0.0 },
                                      m_efficiency { efficiency }
      {}
      [[nodiscard]] double capacity() const
      {
         return m_capacity;
      }
      void charge(double amount)
      {
         m_capacity += amount;
      }
      double drive(double distance)
      {
         auto requiredCapacity { distance / 100.0 * m_efficiency };
         if (requiredCapacity > m_capacity)
         {
            distance = m_capacity * 100.0 / m_efficiency;
            requiredCapacity = m_capacity;
         } 
         m_capacity -= requiredCapacity;
         m_mileage += distance;
         return distance;
      }
      [[nodiscard]] double remainingRange() const
      {
         return m_capacity * 100.0 / m_efficiency;
      }
      [[nodiscard]] double mileage() const
      {
         return m_mileage;
      }
   private:
      double m_capacity, // kWh
             m_mileage; // km or miles
      const double m_efficiency; // kWh per 100 km or miles
};

int main()
{
   OBCE obce { 19.3 };
   obce.charge(58.0);
   cout << "remaining range: " << obce.remainingRange() << endl;
   auto coveredDistance { obce.drive(150.0) };
   cout << "covered distance: " << coveredDistance << endl;
   cout << "odometer reading: " << obce.mileage() << endl;
   cout << "remaining range: " << obce.remainingRange() << endl;
   coveredDistance = obce.drive(400);
   cout << "covered distance: " << coveredDistance << endl;
   cout << "odometer reading: " << obce.mileage() << endl;
   cout << "remaining range: " << obce.remainingRange() << endl;
}
