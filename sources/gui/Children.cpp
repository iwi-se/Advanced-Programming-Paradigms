// Children.cpp by Ulrich Eisenecker, March 11, 2024

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>

class Leaf: public Fl_Widget
{
   public:
      // The constructor must be defined and explicitly call 
      // the constructor of the base class, as the constructor
      // of the base class is declared as protected.
      Leaf(int x, int y, int w, int h, const char* label = nullptr,
            Fl_Color c = FL_BLACK):Fl_Widget { x,y,w,h,label },m_color { c }
      {
      }
      void draw() override
      {
         draw_box(FL_FLAT_BOX,m_color);
         draw_label();
      }
   private:
      Fl_Color m_color;
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
