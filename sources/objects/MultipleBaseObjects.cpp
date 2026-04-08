// MultipleBaseObjects.cpp by Ulrich Eisenecker, March 8, 2023

#include <iostream>
using namespace std;

class Z
{
   public:
      Z()
      {
         cout << "Z";
      }
      virtual ~Z()
      {
         cout << "~Z" << endl;
      }
};

class D: public Z
{
   public:
      D()
      {
         cout << "D" << endl;
      }
      virtual ~D()
      {
         cout << "~D";
      }
};

class E: public Z
{
   public:
      E()
      {
         cout << "E" << endl;
      }
      virtual ~E()
      {
         cout << "~E";
      }
};

class F: public D, public E
{
   public:
      F()
      {
         cout << "F" << endl;
      }
      virtual ~F()
      {
         cout << "~F" << endl;
      }
};

class G: public F
{
   public:
      G()
      {
         cout << "G" << endl;
      }
      virtual ~G()
      {
         cout << "~G" << endl;
      }
};

int main()
{
   G g;
}
