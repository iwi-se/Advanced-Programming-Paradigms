// Subobjects.cpp by Ulrich Eisenecker, March 7, 2023

#include <iostream>
using namespace std;

class A
{
   public:
      A()
      {
         cout << "A";
      }
      ~A()
      {
         cout << "~A" << endl;
      }
};

class B
{
   public:
      B()
      {
         cout << "B";
      }
      ~B()
      {
         cout << "~B";
      }
};

class C
{
   public:
      C()
      {
         cout << "C" << endl;
      }
      virtual ~C()
      {
         cout << "~C";
      }
   private:
      A a;
      B b;
};

class D
{
   public:
      D()
      {
         cout << "D";
      }
      virtual ~D()
      {
         cout << "~D" << endl;
      }
};

class E
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

class H
{
   public:
     H()
      {
         cout << "H";
      }
      ~H()
      {
         cout << "~H" << endl;
      }
};

class I
{
   public:
      I()
      {
         cout << "I" << endl;
      }
      virtual ~I()
      {
         cout << "~I";
      }
   private:
      H h;
};

class J
{
   public:
      J()
      {
         cout << "J";
      }
      ~J()
      {
         cout << "~J" << endl;
      }
};

class K: public I
{
   public:
      K()
      {
         cout << "K" << endl;
      }
      virtual ~K()
      {
         cout << "~K";
      }
   private:
      J j;
};

int main()
{
   C c;
   G g;
   K k;
}
