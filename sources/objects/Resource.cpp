// Resource.cpp by Ulrich Eisenecker, March 1, 2023

#include <iostream>
#include <string>

using namespace std;

class Resource
{
   public:
      Resource():m_myId { ++m_nextId }
      {
         report("standard constructor");
      }
      Resource(const Resource&):m_myId { ++m_nextId }
      {
         report("copy constructor");
      }
      Resource(Resource&&):m_myId { ++m_nextId }
      {
         report("move constructor");
      }
      virtual ~Resource()
      {
         report("destructor");
      }
      Resource& operator=(const Resource&)
      {
         report("assignment");
         return *this;
      }
      Resource& operator=(Resource&&)
      {
         report("move assignment");
         return *this;
      }
   private:
      void report(const string& mf) const
      {
         std::cout << m_myId
                   << '\t' << mf
                   << std::endl;
      }
      int m_myId;
      inline static int m_nextId { };
};

class NoDynamicResource final
{
   private:
      Resource m_resource;
};

class Wrong final
{
   public:
      Wrong():m_dynamic { new Resource }
      {}
      ~Wrong()
      {
         delete m_dynamic;
         m_dynamic = nullptr;
      }
   private:
      Resource* m_dynamic;
};

class Big3 final
{
   public:
      Big3():m_dynamic { new Resource }
      {}
      Big3(const Big3& big3)
         :m_dynamic { new Resource { *big3.m_dynamic } }
      {}
      Big3& operator=(const Big3& big3)
      {
         if (this != &big3)
         {
            Resource* newResource { new Resource { *big3.m_dynamic } };
            delete m_dynamic;
            m_dynamic = newResource;
         }
         return *this;
      }
      ~Big3()
      {
         delete m_dynamic;
         m_dynamic = nullptr;
      }
   private:
      Resource* m_dynamic;
};

class Big5 final
{
   public:
      Big5():m_dynamic { new Resource }
      {}
      Big5(const Big5& big5)
         :m_dynamic { new Resource { *big5.m_dynamic } }
      {}
      Big5(Big5&& big5)
         :m_dynamic { big5.m_dynamic }
      {
         big5.m_dynamic = nullptr;
         cout << "Big5 move constructor" << endl;
      }
      Big5& operator=(const Big5& big5)
      {
         if (this != &big5)
         {
            Resource* newResource { new Resource { *big5.m_dynamic } };
            delete m_dynamic;
            m_dynamic = newResource;
         }
         return *this;
      }
      Big5& operator=(Big5&& big5)
      {
         cout << "Big5 move assignment" << endl;
         if (this != &big5)
         {
            delete m_dynamic;
            m_dynamic = big5.m_dynamic;
            big5.m_dynamic = nullptr;
         }
         return *this;
      }
      ~Big5()
      {
         delete m_dynamic;
         m_dynamic = nullptr;
      }
   private:
      Resource* m_dynamic;
};

class Big5Deleted
{
   public:
      Big5Deleted():m_dynamic { new Resource }
      {}
      virtual ~Big5Deleted()
      {
         delete m_dynamic;
      }
      Big5Deleted(const Big5Deleted&) = delete;
      Big5Deleted(Big5Deleted&&) = delete;
      Big5Deleted& operator=(const Big5Deleted&) = delete;
      Big5Deleted& operator=(Big5Deleted&&) = delete;
   private:
      Resource* m_dynamic;
};

using Class = NoDynamicResource;

Class test(Class o)
{
   o = Class { };
   return o;
}

int main()
{
   Class a;
   Class b { a };
   a = b;
   auto c { test(Class { }) };
}
