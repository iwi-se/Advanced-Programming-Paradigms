// Butterfly.cpp by Ulrich Eisenecker, February 26, 2026

#include <iostream>
#include <string>
#include <variant>

using namespace std;

using ulli_t = unsigned long long int;

class Id
{
   public:
      Id():m_id { ++s_id }
      { };
      string id() const
      {
         return to_string(m_id);
      }
   protected:
      ulli_t m_id;
      inline static ulli_t s_id { 0 };
};

class Egg;
class Caterpillar;
class Chrysalis;
class Imago;

using Butterfly = variant<Egg,Caterpillar,Chrysalis,Imago>;

class Egg
{
   public:
      Caterpillar hatch() const;
      string id() const
      {
         return m_id.id() + " Egg ";
      }
   private:
      Id m_id;
};

class Caterpillar
{
   public:
      Caterpillar(Id id):m_id { id }
      { };
      Chrysalis pupate() const;
      string id() const
      {
         return m_id.id() + " Caterpillar ";
      }
   private:
      Id m_id;
};

class Chrysalis
{
   public:
      Chrysalis(Id id):m_id { id }
      { };
      Imago emerge() const;
      string id() const
      {
         return m_id.id() + " Chrysalis ";
      }
   private:
      Id m_id;
};

class Imago
{
   public:
      Imago(Id id):m_id { id }
      { };
      Egg layEgg() const;
      string id() const
      {
         return m_id.id() + " Imago ";
      }
   private:
      Id m_id;
};

Caterpillar Egg::hatch() const
{
   return m_id;
}

Chrysalis Caterpillar::pupate() const
{
   return m_id;
}

Imago Chrysalis::emerge() const
{
   return m_id;
}

Egg Imago::layEgg() const
{
   return Egg { };
}

Butterfly nextStage(Butterfly b)
{
   switch (b.index())
   {
      case 0: return get<0>(b).hatch();
      case 1: return get<1>(b).pupate();
      case 2: return get<2>(b).emerge();
      case 3: return get<3>(b).layEgg();
   }
   return b;
}

int main()
{
   Butterfly b { Egg { } };
   ulli_t n { 10 };
   while (n--)
   {
      b.visit([](auto v) { cout << v.id() << endl; });
      b = nextStage(b);
   }
}
