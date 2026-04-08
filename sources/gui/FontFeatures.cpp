// FontFeatures.cpp by Ulrich Eisenecker, March 6, 2024

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
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
         fl_draw(s.c_str(),x,y);
      }
      void draw() override
      {
         const std::string baseline { "\'q\' and \'y\' extend "
                                      "below the baseline." };
         const std::string descender { "The part of the character below "
                                       "the baseline is its descender." };
         const std::string dX { "\' horizontal shift." };
         const std::string dY { "| vertical shift" };
         const std::string positiveDY { "^^^" };
         auto font { FL_TIMES };
         Fl_Fontsize size { 24 };

         Fl_Window::draw();
         drawGrid(25);

         fl_color(FL_RED);
         fl_line_style(FL_DASH,2);
         fl_font(font,size);
         fl_line(4,24,fl_width(baseline.c_str()) + 4,24);
         drawSample(baseline.c_str(),font,size,4,24);

         fl_color(FL_YELLOW);
         fl_line_style(FL_SOLID,1);
         fl_rectf(4,50,fl_width(descender.c_str()),fl_descent());
         drawSample(descender.c_str(),font,size,4,49);

         int dx,dy,width,height;
         fl_text_extents(dX.c_str(),dx,dy,width,height);
         fl_color(FL_GREEN);
         fl_rectf(4,49 + fl_descent(),dx,25 - fl_descent());
         drawSample(dX.c_str(),font,size,4,74);

         fl_text_extents(dY.c_str(),dx,dy,width,height);
         fl_color(FL_WHITE);
         fl_rectf(4,100,width + dx,dy + height);
         drawSample(dY.c_str(),font,size,4,99);

         fl_text_extents(positiveDY.c_str(),dx,dy,width,height);
         fl_color(FL_WHITE);
         // Under MS Windows, the following line does not give
         // the expected result, as the height is calculated
         // incorrectly for characters that do not extend to
         // the baseline.
         fl_rectf(4,125 + dy + height,width + dx,-dy - height);
         drawSample(positiveDY.c_str(),font,size,4,124);  
         drawSample("vertical shift.",font,size,10 + width,124);
      }
};

int main(int argc,char * argv[])
{
   TextWindow window { 600,150,"FontFeatures" };
   window.end();
   window.resizable(&window);
   window.show();
   return Fl::run();
}
