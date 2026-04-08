// Butterfly.cpp by Ulrich Eisenecker, May 27, 2025

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
using namespace std;

// If verbose is initialized to true, the program will report
// information about which member function has been called,
// as well as additional bookkeeping information in the terminal
// window.
constexpr bool verbose { false };

// Abstract base class for Egg, Caterpillar, Chrysalis, and Imago.
// It serves as an interface that abstracts from the
// specific development stage of a Butterfly exemplar.
// It must be defined before Butterfly, as Butterfly::whatAmI()
// calls the member function with the same name for the Stage
// pointer m_stage.
class Stage
{
   public:
      Stage()
      { if constexpr (verbose)
        {
           cout << "After construction = " << ++m_n << endl;
        }
      }
      virtual ~Stage()
      { if constexpr(verbose)
        {
           cout << "After destruction = " << --m_n << endl;
        }
      }
      virtual unique_ptr<Stage> next() const = 0;
      virtual string whatAmI() const = 0;
   private:
      static inline size_t m_n { 0 };
};

// This is the class to be instantiated by the client programmer.
// It internally manages a stage pointer that refers to the specific
// development stage of a butterfly and thus enables stage-specific behavior.
class Butterfly
{
   public:
      Butterfly();
      bool next();
      string whatAmI() const
      {
         return m_stage->whatAmI();
      }
   private:
      unique_ptr<Stage> m_stage;
};

class Egg: public Stage
{
   public:
      unique_ptr<Stage> next() const override;
      string whatAmI() const override
      {
         return "Egg"s;
      }
};

class Caterpillar: public Stage
{
   public:
      unique_ptr<Stage> next() const override;
      string whatAmI() const override
      {
         return "Caterpillar"s;
      }
};

class Chrysalis: public Stage
{
   public:
      unique_ptr<Stage> next() const override;
      string whatAmI() const override
      {
         return "Chrysalis"s;
      }
};

class Imago: public Stage
{
   public:
      unique_ptr<Stage> next() const override;
      string whatAmI() const override
      {
         return "Imago"s;
      }
};

// The Butterfly constructor must be defined after the
// definition of Egg, as it creates a dynamic Egg exemplar.
Butterfly::Butterfly(): m_stage { make_unique<Egg>() }
{
}

// Butterfly::next() must be defined after the
// definition of Imago, as it uses the complete
// type of Imago.
bool Butterfly::next()
{
   auto& stage { *m_stage }; // To avoid a warning in the next line.
   if (typeid(stage) != typeid(Imago))
   {
      m_stage = m_stage->next();
      return true;
   }
   return false;
}

// The following member functions must be defined after the
// definition of the classes representing the different stages,
// as each of these member functions uses a particular subclass
// of Stage.

unique_ptr<Stage> Egg::next() const
{
   return make_unique<Caterpillar>();
}

unique_ptr<Stage> Caterpillar::next() const
{
   return make_unique<Chrysalis>();
}

unique_ptr<Stage> Chrysalis::next() const
{
   return make_unique<Imago>();
}

unique_ptr<Stage> Imago::next() const
{
   return nullptr;
}

int main()
{
   Butterfly bf;
   cout << bf.whatAmI() << endl;
   cout << bf.next() << endl;
   cout << bf.whatAmI() << endl;
   cout << bf.next() << endl;
   cout << bf.whatAmI() << endl;
   cout << bf.next() << endl;
   cout << bf.whatAmI() << endl;
   cout << bf.next() << endl;
   cout << bf.whatAmI() << endl;
}
