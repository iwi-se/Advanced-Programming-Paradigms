// GenericSerialization.cpp by Ulrich Eisenecker, April 12, 2024

#include <iostream>
#include <fstream>
using namespace std;

class Writer
{
   public:
      Writer(std::ostream& o):m_o { o }
      {}
      // Here is the member template.
      template <typename T>
      Writer& operator<<(const T& o)
      {
         m_o.write(reinterpret_cast<const char*>(&o),sizeof(o));
         return *this;
      }

   private:
      std::ostream& m_o;
};

class Reader 
{
   public:
      Reader(std::istream& i):m_i { i }
      {}
      // Here is the member template.
      template <typename T>
      Reader& operator>>(T& o)
      {
         m_i.read(reinterpret_cast<char*>(&o),sizeof(o));
         return *this;
      }
   private:
      std::istream& m_i;
};

template <typename T>
void checkingConsistency(T& a,T& b)
{
   cout << a << '\t' << b << '\t' << (a == b) << endl;
}

int main()
{
   // Binary serialization
   bool b1 { false };
   char c1 { 'X' };
   unsigned int ui1 { 42 };
   long double ld1 { 22l / 7 };
   {
      ofstream o { "binary.data" };
      Writer w { o };
      // In the next line, the member template is 
      // instantiated for different types.
      w << ld1 << ui1 << c1 << b1;
   }
   
   // Binary deserialization
   bool b2;
   char c2;
   unsigned int ui2;
   long double ld2;
   {
      ifstream i { "binary.data" };
      Reader r { i };
      // In the next line, the member template is 
      // instantiated for different types.
      r >> ld2 >> ui2 >> c2 >> b2;
   }

   // Checking consistency
   checkingConsistency(b1,b2);
   checkingConsistency(c1,c2);
   checkingConsistency(ui1,ui2);
   checkingConsistency(ld1,ld2);
}
