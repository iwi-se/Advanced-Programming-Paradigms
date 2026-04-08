// Observer.cpp by Ulrich Eisenecker, June 17, 2024

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Enumerations.H> 
#include <FL/fl_draw.H> 
#include <FL/fl_ask.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Color_Chooser.H>
#include <cstring> // Because of strlen()
#include <vector>
#include <algorithm>

class Observer; // Pending declaration

class Subject
{
   public:
      Subject()
      {}
      bool attach(Observer* observer);
      bool detach(Observer* observer);
      void notify() const;
      virtual ~Subject();
      Subject& operator=(const Subject&) = delete;
      Subject(const Subject&) = delete;
   private:
      std::vector<Observer*> m_observers { };
};

class Observer
{
   public:
      Observer(Subject* subject = nullptr): m_subject { subject }
      {
         if (m_subject)
         {
            m_subject->attach(this);
         }
      }
      void subject(Subject* s = nullptr)
      {
         if (m_subject)
         {
            m_subject->detach(this);
         }
         m_subject = s;
         if (m_subject)
         {
            m_subject->attach(this);
            update();
         }
      }
      virtual void update() = 0;
      virtual ~Observer()
      { 
         if (m_subject)
         {
           m_subject->detach(this);
         }
      }
      Observer(const Observer&) = delete;
      Observer& operator=(const Observer&) = delete;
   protected:
      Subject* m_subject;
};

bool Subject::attach(Observer* observer)
{
   if (observer != nullptr)
   {
      auto result { std::find(m_observers.begin(),m_observers.end(),observer) };
      if (result == m_observers.end())
      {
         m_observers.push_back(observer);
         observer->subject(this);
         return true;
      }
   }
   return false;
}

bool Subject::detach(Observer* observer)
{
   auto result { std::find(m_observers.begin(),m_observers.end(),observer) };
   if (result == m_observers.end())
   {
      return false;
   }
   m_observers.erase(result);
   return true;
}

void Subject::notify() const
{
   for (const auto& observer : m_observers)
   {
      observer->update();

   }
}

Subject::~Subject()
{
   for (auto& observer : m_observers)
   {
      observer->subject(); // Remove subject from observer.
   }
}

class Star: public Subject
{
   public:
      Star(char symbol = '*',Fl_Font font = FL_SCREEN,
           Fl_Fontsize size = FL_NORMAL_SIZE,
           Fl_Color color = FL_BLACK):m_symbol { symbol },
                                      m_font { font },
                                      m_size { size },
                                      m_color { color }
      {}
      void symbol(char symbol)
      {
         m_symbol = symbol;
         notify();
      }
      void font(Fl_Font f)
      {
         m_font = f;
         notify();
      }
      void size(Fl_Fontsize s)
      {
         m_size = s;
         notify();
      }
      void color(Fl_Color c)
      {
         m_color = c;
         notify();
      }
      char symbol() const
      {
         return m_symbol;
      }
      Fl_Font font() const
      {
         return m_font;
      }
      Fl_Fontsize size() const
      {
         return m_size;
      }
      Fl_Color color() const
      {
         return m_color;
      }
   private:
      char m_symbol;
      Fl_Font m_font;
      Fl_Fontsize m_size;
      Fl_Color m_color;
};

class StarWindow: public Fl_Window,public Observer
{
   public:
      StarWindow(int width,int height,const char* title,Star* star = nullptr)
         : Fl_Window { width,height,title },Observer { star },
           m_menu { 0,0,w(),30,"MenuBar" }
      {
         m_x = w() / 2;
         m_y = (h() - m_menu.h()) / 2 + m_menu.h();
         m_menu.add("&Star/_&About",FL_CTRL + 'a',
                    [](Fl_Widget*,void*)
                    { fl_message("Star Application"); });
         m_menu.add("&Star/&Quit",FL_CTRL + 'q',
                    [](Fl_Widget*,void*)
                    { if (fl_choice("Really quit?","Ok","Cancel",0) == 0)
                      exit(0); });
         m_menu.add("&Edit/&Symbol",FL_CTRL + 's',
                    cbMenu,reinterpret_cast<void*>(1ul));
         m_menu.add("&Edit/_&Color",FL_CTRL + 's',
                    cbMenu,reinterpret_cast<void*>(2ul));
         m_menu.add("&Edit/&Font/&Helvetica",0,
                    cbMenu,reinterpret_cast<void*>(3ul));
         m_menu.add("&Edit/&Font/&Times",0,
                    cbMenu,reinterpret_cast<void*>(4ul));
         m_menu.add("&Edit/&Font/&Courier",0,
                    cbMenu,reinterpret_cast<void*>(5ul));
         m_menu.add("&Edit/&Font/&Default",0,
                    cbMenu,reinterpret_cast<void*>(6ul));
         m_menu.add("&Edit/&Size/&8",0,
                    cbMenu,reinterpret_cast<void*>(7ul));
         m_menu.add("&Edit/&Size/1&2",0,
                    cbMenu,reinterpret_cast<void*>(8ul));
         m_menu.add("&Edit/&Size/2&4",0,
                    cbMenu,reinterpret_cast<void*>(9ul));
         m_menu.add("&Edit/&Size/&Default",0,
                    cbMenu,reinterpret_cast<void*>(10ul));
      }
      void update() override
      {
         if (m_subject)
         {
            auto star { dynamic_cast<Star*>(m_subject) };
            if (star)
            {
               m_symbol[0] = star->symbol();
               m_font = star->font();
               m_size = star->size();
               m_color = star->color();
               redraw();
            }
         }
      }
      void draw() override
      {
         if (m_subject)
         {
            Fl_Window::draw(); // Must call Fl_Window::draw() beforehand for the 
            fl_font(m_font,m_size); // font and font size setting to take effect
            fl_text_extents(m_symbol,m_dx,m_dy,m_width,m_height);
            fl_color(m_color);
            fl_draw(m_symbol,m_x + m_dx - m_width / 2 + 1,
                             m_y - m_dy / 2 - m_height / 2);
         }
      }
      void flash()
      {
         auto oldColor { color() };
         color(FL_RED);
         redraw();
         Fl::wait(0.25);
         color(oldColor);
         redraw();
      }
      static void cbMenu(Fl_Widget* w,void* data)
      {
         auto window { dynamic_cast<StarWindow*>(w->parent()) };
         Star* star { nullptr };
         if (window)
         {
            star = dynamic_cast<Star*>(window->m_subject);
         }
         if (window && star)
         {
            auto menuId { reinterpret_cast<unsigned long>(data) };
            switch (menuId)
            {
               case 1:
                  {
                     bool again { false };
                     do
                     {
                        auto newLabel { fl_input("New symbol: ",
                                        window->m_symbol) };
                        if (newLabel == nullptr)
                        {
                          break;
                        }
                        again = (strlen(newLabel) != 1);
                        if (again)
                        {
                           fl_alert("Symbol must have only 1 char, "
                                    "please retry.");
                        }
                        else
                        {
                           window->m_symbol[0] = newLabel[0];
                        }
                     } while (again);
                     star->symbol(window->m_symbol[0]);
                  }
                  break;
               case 2:
                  uchar r,g,b;
                  Fl::get_color(window->m_color,r,g,b);
                  if (fl_color_chooser("Select color",r,g,b) == 1)
                  {
                     window->m_color = fl_rgb_color(r,g,b);
                     star->color(window->m_color);
                  }
                  break; 
               case 3:
                  window->m_font = FL_HELVETICA;
                  star->font(window->m_font);
                  break;
               case 4:
                  window->m_font = FL_TIMES;
                  star->font(window->m_font);
                  break;
               case 5:
                  window->m_font = FL_COURIER;
                  star->font(window->m_font);
                  break;
               case 6:
                  window->m_font = FL_SCREEN;
                  star->font(window->m_font);
                  break;
               case 7:
                  window->m_size = 8;
                  star->size(window->m_size);
                  break;
               case 8:
                  window->m_size = 12;
                  star->size(window->m_size);
                  break;
               case 9:
                  window->m_size = 24;
                  star->size(window->m_size);
                  break;
               case 10:
                  window->m_size = FL_NORMAL_SIZE;
                  star->size(window->m_size);
                  break;
               default: fl_alert("Unknown menu id: %lu",menuId);break;
            }
         }
      }
      static void cbLeft(Fl_Widget* w,void*)
      {
         auto window { dynamic_cast<StarWindow*>(w) };
         if (window)
         {
            window->m_x -= window->m_width;
            if (window->m_x < window->m_dx + 1)
            {
               window->m_x = -window->m_dx + 1;
               window->flash();
            }
         }
         window->redraw();
      }
      static void cbRight(Fl_Widget* w,void*)
      {
         auto window { dynamic_cast<StarWindow*>(w) };
         if (window)
         {
            window->m_x += window->m_width;
            if (window->m_x > window->w() - window->m_width - window->m_dx + 1)
            {
               window->m_x = window->w() - window->m_width - window->m_dx + 1;
               window->flash();
            }
         }
         window->redraw();
      }
      static void cbUp(Fl_Widget* w,void *)
      {
         auto window { dynamic_cast<StarWindow*>(w) };
         if (window)
         {
            window->m_y -= window->m_height;
            if (window->m_y < -window->m_dy + window->m_menu.h() - 1)
            {
               window->m_y = -window->m_dy + window->m_menu.h() - 1;
               window->flash();
            }
         }
         window->redraw();
      }
      static void cbDown(Fl_Widget* w,void*)
      {
         auto window { dynamic_cast<StarWindow*>(w) };
         if (window)
         {
            window->m_y += window->m_height;
            if (window->m_y > window->h() - 2 * 
                window->m_height - window->m_dy - 1)
            {
               window->m_y = window->h() - window->m_height - window->m_dy - 1;
               window->flash();
            }
         }
         window->redraw();
      }
   private:
      char m_symbol[2] { " " };
      Fl_Font m_font { FL_SCREEN };
      Fl_Fontsize m_size { FL_NORMAL_SIZE };
      Fl_Color m_color { FL_BLACK };
      int m_x { },
          m_y { },
          m_width { },
          m_height { },
          m_dx { },
          m_dy { };
      Fl_Menu_Bar m_menu;
};

int eventHandler(int event,Fl_Window* w)
{ 
   auto window { dynamic_cast<StarWindow*>(w) };
   if (window)
   {
      if (event == FL_KEYBOARD)
      {
         auto key { Fl::event_key() };
         switch (key)
         {
            case FL_Right: StarWindow::cbRight(window,nullptr); return 1;
            case FL_Left:  StarWindow::cbLeft(window,nullptr);  return 1;
            case FL_Up:    StarWindow::cbUp(window,nullptr);    return 1;
            case FL_Down:  StarWindow::cbDown(window,nullptr);  return 1;
         }
      }
   }
   return Fl::handle_(event,w);
}

int main()
{
   Fl::event_dispatch(eventHandler);
   Star star1 { '*' };
   StarWindow window1 { 320,240,"Window 1" };
   window1.end();
   star1.attach(&window1);
   window1.show();
   StarWindow window2 { 160,120," Window 2" };
   window2.end();
   star1.attach(&window2);
   window2.show();
   StarWindow window3 { 640,480," Window 3" };
   window3.end();
   Star star2 { '+' };
   star2.attach(&window3);
   window3.show();
   return Fl::run();
}
