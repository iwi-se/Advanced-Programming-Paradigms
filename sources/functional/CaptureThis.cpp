// CaptureThis.cpp by Ulrich Eisenecker, November 27, 2025

#include <iostream>
#include <limits>
#include <ranges>
#include <stdexcept>
#include <vector>

constexpr auto verbose { true };

class Winsorizer
{
   public:
      Winsorizer(double lowerLimit = std::numeric_limits<double>::lowest(),
                 double upperLimit = std::numeric_limits<double>::max() ):
         m_lower { lowerLimit },
         m_upper { upperLimit }
      {
         if (m_lower >= m_upper)
         {
            throw std::invalid_argument("Error: m_lower >= m_upper");
         }
         if constexpr(verbose)
         {
            std::cout << "Winsorizer::Winsorizer("
                      << m_lower << ',' << m_upper
                      << ')' << std::endl;
         }
      }
      Winsorizer(const Winsorizer& w):m_lower(w.m_lower),
                                      m_upper(w.m_upper)
      {
         if constexpr(verbose)
         {
            std::cout << "Winsorizer::Winsorizer(const Winsorizer&)"
                      << std::endl;
         }
      }
      Winsorizer(Winsorizer&& w):m_lower(w.m_lower),
                                 m_upper(w.m_upper)
      {
         if constexpr(verbose)
         {
            std::cout << "Winsorizer::Winsorizer(Winsorizer&&)"
                      << std::endl;
         }
      }
      ~Winsorizer()
      {
         if constexpr(verbose)
         {
            std::cout << "Winsorizer::~Winsorizer("
                      << m_lower << ',' << m_upper
                      << ')' << std::endl;
         }
      }
      Winsorizer& limits(double l = std::numeric_limits<double>::lowest(),
                         double u = std::numeric_limits<double>::max())
      {
         if (l >= u)
         {
            throw std::invalid_argument("Error: l >= u");
         }
         m_lower = l;
         m_upper = u;
         return *this;
      }
      [[nodiscard]] auto winsorize(auto& data)
      {
         return data | std::views::transform(
            [this] (double v)
            {
               if (v < m_lower) return m_lower;
               if (v > m_upper) return m_upper;
               return v;
            } );
      }
      [[nodiscard]] auto winsorize2(auto& data)
      {
         return data | std::views::transform(
            [*this] (double v)
            {
               if (v < m_lower) return m_lower;
               if (v > m_upper) return m_upper;
               return v;
            } );
      }
   private:
      double m_upper { };
      double m_lower { };
};

void output (const std::string& message,
             const std::ranges::forward_range auto& v,
             std::ostream& os = std::cout)
{
   os << message;
   for (auto e : v)
   {
     os << ' ' << e;
   }
   os << std::endl;
}

using namespace std;

int main()
{
   {
      cout << "Capturing this" << endl;
      vector d { -2.5, 4.0, 1.1 };
      output("original:",d);
      Winsorizer w { -2.0, 2.0 };
      auto wd { w.winsorize(d) };
      output("winsorized [-2.0,2.0]:",wd);
      w.limits();
      output("not winsorized:",wd);
   }
   {
      cout << "\nCapturing *this" << endl;
      vector d { -2.5, 4.0, 1.1 };
      output("original:",d);
      Winsorizer w { -2.0, 2.0 };
      auto wd { w.winsorize2(d) };
      output("winsorized [-2.0,2.0]:",wd);
      w.limits();
      output("still winsorized:",wd);
   }
}
