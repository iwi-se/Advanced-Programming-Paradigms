// OBC_Override.cpp by Ulrich Eisenecker, January 13, 2023

#include <iostream>
#include <string>
#include <fstream> // because of file streams
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
      virtual void output(ostream& os) const
      {
         os << m_fuel << endl;
      }
      virtual void input(istream& is)
      {
         is >> m_fuel;
      }
   private:
      double m_fuel;
};

ostream& operator<<(ostream& os,const OBC& o)
{
   o.output(os);
   return os;
}

istream& operator>>(istream& is,OBC& o)
{
   o.input(is);
   return is;
}

class OBCA: public OBC
{
   public:
      OBCA(): OBC(), m_mileage { 0.0 }
      {}
      double mileage() const
      {
         return m_mileage;
      }
      void addMileage(double distance)
      {
         m_mileage += distance;
      }
      void output(ostream& os) const override
      {
         os << m_mileage << '\t';
         OBC::output(os);
      }
      void input(istream& is) override
      {
         is >> m_mileage;
         OBC::input(is);
      }
   private:
      double m_mileage;
};

int main()
{
   const string filename1 { "obc1.csv" };
   const string filename2 { "obc2.csv" };

   { 
      ofstream out { filename1 };
      OBC obc;
      obc.addFuel(42.0);
      obc.output(out);
      OBCA obca;
      obca.addFuel(30.0);
      obca.addMileage(150.0);
      obca.output(out);
   }
   {
      ifstream in { filename1 };
      OBC obc;
      obc.input(in);
      cout << obc.fuel() << endl;
      OBCA obca;
      obca.input(in);
      cout << obca.fuel() << endl;
      cout << obca.mileage() << endl;
   }

   { 
      ofstream out { filename2 };
      OBC obc;
      obc.addFuel(42.0);
      out << obc;
      OBCA obca;
      obca.addFuel(30.0);
      obca.addMileage(150.0);
      out << obca;
   }
   {
      ifstream in { filename2 };
      OBC obc;
      in >> obc;
      cout << obc.fuel() << endl;
      OBCA obca;
      in >> obca;
      cout << obca.fuel() << endl;
      cout << obca.mileage() << endl;
   }
}

