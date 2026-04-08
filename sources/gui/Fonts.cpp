// Fonts.cpp by Ulrich Eisenecker, March 6, 2024

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <FL/names.h> // Because of fl_fontnames.
#include <string>

class TextWindow: public Fl_Window
{
   public:
      using Fl_Window::Fl_Window; // Make constructors of base class available
      void drawGrid(int size = 25)
      {
         fl_color(FL_BLUE);
         fl_line_style(FL_DOT,1);
         // Draw lines
         for (int i { size - 1 }; i <= h(); i+= size)
         {
            fl_line(0,i,w() - 1,i);
         }
         // Draw columns
         for (int i { size - 1 }; i <= w(); i+= size)
         {
            fl_line(i,0,i,h() - 1);
         }
      }
      void drawSample(std::string s,Fl_Font face,Fl_Fontsize size,int x,int y)
      {
         fl_font(face,size);
         fl_color(FL_BLACK);
         s += s + fl_fontnames[face];
         fl_draw(s.c_str(),x,y);
      }
      void draw() override
      {
         const std::string s { "`.-|_Ü " }; 
         Fl_Window::draw();
         drawGrid(25);
         drawSample(s,FL_HELVETICA,18,4,24);
         drawSample(s,FL_COURIER,18,4,49);
         drawSample(s,FL_TIMES,18,4,74);
         drawSample(s,FL_SYMBOL,18,4,99);
         drawSample(s,FL_SCREEN,18,4,124);
         drawSample(s,FL_ZAPF_DINGBATS,18,4,149);
      }
};

int main(int argc,char * argv[])
{
   TextWindow window { 300,175,"Fonts" };
   window.end();
   window.resizable(&window);
   window.show();
   return Fl::run();
}
