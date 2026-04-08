// Discussion.cpp by Ulrich Eisenecker, October 18, 2023

#include <string>
#include <iostream>
#include <memory>
using namespace std;

class Person;

class Discussion final
{
   public:
      explicit Discussion(const string& topic,const Person& p);
      ~Discussion()
      {
         cout << "Discussion about " << m_topic << " ends." << endl;
      }
      void leave(const Person& p);
      void join(const Person& p);
   private:
      string m_topic;
};

class Person final
{
   public:
      explicit Person(const string& name):m_name { name }
      {
      }
     auto& startDiscussion(const string& topic)
      {
         if (m_discussion)
         {
            m_discussion->leave(*this);
         }
         m_discussion = make_shared<Discussion>(topic,*this);
         return m_discussion;
      }
      void join(shared_ptr<Discussion>& discussion)
      {
         if (m_discussion != discussion)
         {
            if (m_discussion)
            {
               m_discussion->leave(*this);
            }
            m_discussion = discussion;
            m_discussion->join(*this);
         };
      }
       void leave()
      {
         if (m_discussion)
         {
            m_discussion->leave(*this);
            m_discussion = nullptr;
         }
      }
      const string& name() const
      {
         return m_name;
      }
      void report() const
      {
         cout << ", use count = " << m_discussion.use_count() << '.' << endl;
      }
   private:
      shared_ptr<Discussion> m_discussion;
      string m_name;
};

Discussion::Discussion(const string& topic,const Person& p):m_topic { topic }
{
   cout << p.name() << " starts a discussion about " << m_topic <<  '.' << endl;
}

void Discussion::join(const Person& p)
{
   cout << p.name() << " joins the discussion about " << m_topic; 
   p.report();
}

void Discussion::leave(const Person& p)
{
   cout << p.name() << " leaves the  discussion about " << m_topic;
   p.report();
}

int main()
{
   Person josh { "Josh"s },
          jude { "Jude"s },
          kyle { "Kyle"s };

   jude.join(josh.startDiscussion("Fishing"s));
   josh.leave();
   jude.leave();

   {
      auto farming { josh.startDiscussion("Farming"s) };
      josh.leave();
      cout << "*Use count of farming: " 
           << farming.use_count() << endl;
      jude.join(farming);
      kyle.join(farming);
      cout << "*Use count of farming: " 
           << farming.use_count() << endl;
      jude.startDiscussion("Gaming"s);
      jude.leave();
      kyle.leave();
      cout << "*Use count of farming: " 
           << farming.use_count() << endl;
   }
   auto programming { kyle.startDiscussion("Programming"s) };
   auto kylesClone { kyle };
   kyle.leave();
   cout << "*Use count of programming: " 
        << programming.use_count() << endl;
   kylesClone = jude;
   cout << "*Use count of programming: " 
        << programming.use_count() << endl;
   cout << "*End of main()" << endl;
}
