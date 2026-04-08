// StringSerialization.cpp by Ulrich Eisenecker, June 25, 2025

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Writer
{
   public:
      Writer(std::ostream& o):m_o { o }
      {}
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
      template <typename T>
      Reader& operator>>(T& o)
      {
         m_i.read(reinterpret_cast<char*>(&o),sizeof(o));
         return *this;
      }

   private:
      std::istream& m_i;
};

template <>
Writer& Writer::operator<< <std::string>(const std::string& s)
{
   *this << s.length();
   m_o.write(s.c_str(),s.length());
   return *this;
}

template <>
Reader& Reader::operator>> <std::string>(std::string& s)
{
   decltype(s.length()) l;
   *this >> l;
   char * cs { new char[l] };
   m_i.read(cs,l);
   s.assign(cs,l);
   delete[] cs;
   return *this;
}

int main()
{
   string s1 { " Serializing and deserializing std::string." };
   s1.at(0) = '\0';
   cout << "s1 = " << s1 << endl
        << "sl1.length() = " << s1.length() << endl;
   {
       ofstream o { "string.data" };
       Writer w { o };
       w << s1;
   }

   string s2;
   {
      ifstream i { "string.data" };
      Reader r { i };
      r >> s2;
   }
   cout << "s2 = " << s2 << endl
        << "s2.length() = " << s2.length() << endl;
}
