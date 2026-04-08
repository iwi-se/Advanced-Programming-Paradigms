// Access.cpp by Ulrich Eisenecker, January 20, 2023

/* All lines that are turned into a comment
 * should not compile when decommenting it.
 * It is possible to selectively decomment lines
 * to see the errors the compiler reports.
 */

class Base
{
   public:
      void pub()
      {}
   protected:
      void pro()
      {}
   private:
      void pri()
      {}
};

class PubChild: public Base
{
   public:
      void test()
      {
         Base::pub();
         Base::pro();
         // Base::pri(); // not possible
      }
};

class PubGrandChild: public PubChild
{
   public:
      void test()
      {
         Base::pub();
         Base::pro();
         // Base::pri(); // not possible
      }
};

class ProChild: protected Base
{
   public:
      void test()
      {
         Base::pub();
         Base::pro();         
         // Base::pri(); // not possible
      }
};

class ProGrandChild: protected ProChild
{
   public:
      void test()
      {
         Base::pub();
         Base::pro();
         // Base::pri();
      }
};

class PriChild: private Base
{
   public:
      void test()
      {
         Base::pub();
         Base::pro();
         // Base::pri(); // not possible
      }
};

class PriGrandChild: private PriChild
{
   public:
      void test()
      {
         // Base::pub(); // not possible
         // Base::pro(); // not possible
         // Base::pri(); // not possible
      }
};

int main()
{
   Base { }.pub();
   // Base { }.pro(); // not possible
   // Base { }.pri(); // not possible

   PubChild { }.pub();
   // PubChild { }.pro(); // not possible
   // PubChild { }.pri(); // not possible

   PubGrandChild { }.pub();
   // PubGrandChild { }.pro(); // not possible
   // PubGrandChild { }.pri(); // not possible

   // ProChild { }.pub(); // not possible
   // ProChild { }.pro(); // not possible
   // ProChild { }.pri(); // not possible

   // ProGrandChild { }.pub(); // not possible
   // ProGrandChild { }.pro(); // not possible
   // ProGrandChild { }.pri(); // not possible

   // PriChild { }.pub(); // not possible
   // PriChild { }.pro(); // not possible
   // PriChild { }.pri(); // not possible

   // PriGrandChild { }.pub(); // not possible
   // PriGrandChild { }.pro(); // not possible
   // PriGrandChild { }.pri(); // not possible
}
