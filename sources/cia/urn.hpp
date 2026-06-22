// urn.hpp by Ulrich Eisenecker, March 10, 2023

#ifndef URN_HPP
#define URN_HPP

#include <vector>
#include <iostream> // Because of cerr
#include <cstdlib> // Because of exit()

namespace urn
{
   using uint = unsigned int;
   using Draw = std::vector<uint>;

   class UrnOR
   {
      public:
         explicit UrnOR(uint n,uint k,uint check = 1):m_n { n },
                                                      m_k { k },
                                                      m_balls(k,0)
         { 
            if (check == 1 && m_n == 0 && m_k > 0)
            {
               std::cerr << "UrnOR with n = 0 and k > 0 is not valid, "
                            "program aborted" << std::endl;
               std::exit(check);
            }
         }
         uint n() const
         {
            return m_n;
         }
         uint k() const
         {
            return m_k;
         }
         uint at(uint index) const
         {
            return m_balls.at(index);
         }
         uint operator[](uint index) const
         {
            return m_balls[index];
         }
         [[nodiscard]] virtual bool next()
         {
            for (uint down { m_k }; down > 0; --down)
            {
               if (m_balls[down - 1] < m_n - 1)
               {
                  ++m_balls[down - 1];
                  for (uint up { down }; up < m_k; ++up)
                  {
                     m_balls[up] = 0;
                  }
                  return true;
               }
            }
            return false;
         }
         virtual ~UrnOR() = default;
      protected:
         const uint m_n,
                    m_k;
         Draw m_balls;
   };

   class UrnO: public virtual UrnOR
   {
      public:
         explicit UrnO(uint n,uint k,uint check = 2):UrnOR { n,k,check }
         { 
            if (check == 2 && m_k > m_n)
            {
               std::cerr << "UrnO with k > n is not valid, "
                            "program aborted" << std::endl;
               std::exit(check);
            }
            for (uint i { 1 }; i < m_k; ++i)
            {
               m_balls[i] = i;
            }
         }
         [[nodiscard]] bool next() override
         {
            while (UrnOR::next())
            {
               if (!repetitions())
               {
                  return true;
               };
            }
            return false;
         }
      protected:
         bool repetitions() const
         {
            for (uint i { 0 };i < m_k - 1; ++i)
            {
               for (uint j { i + 1 }; j < m_k; ++j)
               {
                  if (m_balls[i] == m_balls[j])
                  {
                     return true;
                  }
               }
            }
            return false;
         }
   };

   class UrnR: virtual public UrnOR
   {
      public:
         explicit UrnR(uint n,uint k,uint check = 3):UrnOR { n,k,check }
         { 
            if (check == 3 && m_n == 0)
            {
               std::cerr << "UrnR with n = 0 is not valid, "
                            "program aborted" << std::endl;
               std::exit(check);
            }
         }
         [[nodiscard]] bool next() override
         {
            while (UrnOR::next())
            {
               if (!unsorted())
               {
                  return true;
               };
            }
            return false;
         }
      protected:
         bool unsorted() const
         {
            for (uint i { 0 };i < m_k - 1; ++i)
            {
               if (m_balls[i] > m_balls[i + 1])
               {
                  return true;
               }
            }
            return false;
         }
   };
   
   class Urn: public UrnO, public UrnR
   {
      public: 
         explicit Urn(uint n,uint k):UrnOR { n,k },
                                     UrnO { n,k,1 },
                                     UrnR { n,k,1 }
         { 
            for (uint i { 1 }; i < m_k; ++i)
            {
               m_balls[i] = i;
            }
         }
         [[nodiscard]] bool next() override
         {
            while (UrnOR::next())
            {
               if (!unsorted() && !repetitions())
               {
                  return true;
               };
            }
            return false;
         }
   };
}
#endif // URN_HPP
