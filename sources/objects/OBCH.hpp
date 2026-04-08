// OBCH.hpp by Ulrich Eisenecker, April 9, 2024

#ifndef OBCH_HPP
#define OBCH_HPP

class OBC
{
   public:
      OBC(): m_mileage { 0.0 }
      {}
      [[nodiscard]] double mileage() const
      {
         return m_mileage;
      }
      virtual double drive(double distance) = 0;
      [[nodiscard]] virtual double remainingRange() const = 0;
      virtual ~OBC()
      {}
   protected:
      double m_mileage; // km or miles
};

class OBCC: public OBC
{
   public:
      OBCC(const double consumption): OBC { },
                                      m_fuel { 0.0 },
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
      double drive(double distance) override
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
      [[nodiscard]] double remainingRange() const override
      {
         return m_fuel * 100.0 / m_consumption;
      }
   private:
      double m_fuel; // km or miles
      const double m_consumption; // liter or gallons per 100 km or miles
};

class OBCE: public OBC
{
   public:
      OBCE(const double efficiency): OBC { },
                                     m_capacity { 0.0 },
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
      double drive(double distance) override
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
      [[nodiscard]] double remainingRange() const override
      {
         return m_capacity * 100.0 / m_efficiency;
      }
   private:
      double m_capacity; // kWh
      const double m_efficiency; // kWh per 100 km or miles
};

#endif // OBCH_HPP
