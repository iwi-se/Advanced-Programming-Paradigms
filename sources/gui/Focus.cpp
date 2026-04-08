// Focus.cpp by Ulrich Eisenecker, July 9, 2025

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Color_Chooser.H> // Because of fl_color_chooser()
#include <string>

using namespace std;

class Leaf: public Fl_Widget
{
   public:
      Leaf(int x, int y, int w, int h, const char* label = nullptr,
           Fl_Color c = FL_BLACK):Fl_Widget { x,y,w,h,label },
           m_color { c }, m_boxtype { FL_UP_BOX }
      {}
      void changeColor()
      {
         uchar r,g,b;
         Fl::get_color(m_color,r,g,b);
         auto result { fl_color_chooser("Select color",r,g,b) };
         if (result == 1)
         {
            m_color = fl_rgb_color(r,g,b);
            redraw();
         }
      }
      void changeLabel()
      {
         auto newLabel { fl_input("New label: ",label()) };
         if (newLabel)
         {
            copy_label(newLabel);
            redraw();
         }
      }
      void changeResizable()
      {
         if (parent()->resizable() == this)
         {
            return;
         }
         using namespace std;
         string question { "Make "s + label() + " the resizable widget?" };
         // The following switch statement could easily be
         // converted into an if statement.
         switch (fl_choice("%s","Yes","No",0,question.c_str()))
         {
            case 0: parent()->resizable(this);
                    parent()->init_sizes();
                    break;
            case 1: break; // could be deleted
         }
      }
      void draw() override
      {
         color(m_color);
         box(m_boxtype);
         draw_box();
         draw_label();
      }
      int handle(int event) override
      {
         switch (event)
         {
            case FL_PUSH:
                 take_focus();
                 return 1;
            case FL_FOCUS:
                 m_boxtype = FL_DOWN_BOX;
                 redraw();
                 return 1;
            case FL_KEYBOARD:
                 {
                    auto key { Fl::event_key() };
                    switch (key)
                    {
                       case 'c':
                            changeColor();
                            return 1;
                       case 'l':
                            changeLabel();
                            return 1;
                       case 'r':
                            changeResizable();
                            return 1;
                    };
                 }
                 break;
            case FL_UNFOCUS:
                 m_boxtype = FL_UP_BOX;
                 redraw();
                 return 1;
         }
         return Fl_Widget::handle(event);
      }
   private:
      Fl_Color m_color;
      Fl_Boxtype m_boxtype;
};

int main()
{
   // window //////////////////////////
   Fl_Window window { 320,240,"Parent" };

   // Some computations ///////////////
   auto wHalf { window.w() / 2 };
   auto hHalf { window.h() / 2 };

   Leaf green { 0,0,wHalf,hHalf,"Green",FL_GREEN };
   Leaf magenta { wHalf - 1,0,wHalf,hHalf,"Magenta",FL_MAGENTA };
   Leaf cyan { 0,hHalf - 1,wHalf,hHalf,"Cyan",FL_CYAN };
   Leaf yellow { wHalf - 1,hHalf - 1,wHalf,hHalf,"Yellow",FL_YELLOW };
   // window end //////////////////////
   window.end();
   window.resizable(green);
   window.show();
   return Fl::run();
}
