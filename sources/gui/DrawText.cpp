// DrawText.cpp by Ulrich Eisenecker, March 6, 2024

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <iostream>

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
      void drawText(const char* s,int hSpace,int vSpace)
      {
         fl_font(FL_TIMES,24);
         int dx,dy,width,height;
         fl_text_extents(s,dx,dy,width,height);
         using namespace std;
         cout << s << '\t' << fl_font() << '\t' << fl_height() << '\t'
              << dx << '\t' << dy << '\t'
              << width << '\t' << height << '\t'
              << endl;
         // Draw line for assessing vertical alignment
         fl_line_style(FL_SOLID);
         fl_color(FL_WHITE);
         fl_line(0,vSpace,w() - 1,vSpace - 1);
         // Draw rectangle with upper left corner at x|y and
         // text with lower left corner at x|y.
         fl_rect(hSpace - 1,vSpace - 1,width,height,FL_RED);
         fl_color(FL_BLACK);
         fl_draw(s,hSpace - 1,vSpace - 1);
         // Draw rectangle with upper left corner at x + dx|y + dy and
         // text with lower left corner at x|y.
         fl_rect(hSpace * 3 - 1 + dx,vSpace - 1 + dy,width,height,FL_YELLOW);
         fl_color(FL_BLACK);         
         fl_draw(s,hSpace * 3 - 1,vSpace - 1);
         // Draw rectangle with upper left corner at x|y and
         // text with upper left corner at x - dx|y - dy.
         fl_rect(hSpace * 5 - 1,vSpace - 1,width,height,FL_GREEN);
         fl_color(FL_BLACK);         
         fl_draw(s,hSpace * 5 - 1 - dx,vSpace - 1 - dy);
         // Draw rectangle with lower left corner at x|y and
         // text with lower left corner at x|y.
         fl_rect(hSpace * 7 - 1,vSpace - 1 - height,width,height,FL_MAGENTA);
         fl_color(FL_BLACK);         
         fl_draw(s,hSpace * 7 - 1 - dx,vSpace - 1 - height - dy);
      }
      void draw() override
      {
         const char* text1 { "---" };
         const char* text2 { "Ä|Ü" };
         const char* text3 { "gyq" };
         const char* text4 { "_/M" };

         Fl_Window::draw();
         drawGrid(25);
         drawText(text1,25,25);
         drawText(text2,25,75);
         drawText(text3,25,125);
         drawText(text4,25,175);
      }
};

int main(int argc,char * argv[])
{
   TextWindow window { 250,225,"Draw Text" };
   window.end();
   window.resizable(&window);
   window.show();
   using namespace std;
   cout << "Text" << "\tFont" "\tSize "
        << "\tDx" << "\tDy "
        << "\tWidth" << "\tHeight"
        << endl;
   return Fl::run();
}
