// MoreAboutDrawing.cpp by Ulrich Eisenecker, March 6, 2024

#include <FL/Fl.H> // Must be included by each FLTK-program
#include <FL/Fl_Window.H> // Because of Fl_Window
#include <FL/Enumerations.H> // Because of FL_BLACK, FL_Escape, etc.
#include <FL/fl_draw.H> // Because of fl_... functions
#include <FL/fl_ask.H> // Because of FL_BEEP_DEFAULT
#include <FL/Fl_Image.H> // Because of ERR_FILE_ACCESS, etc.
#include <FL/Fl_PNG_Image.H> // Because of Fl_PNG_Image
#include <iostream>

class MyWindow: public Fl_Window
{
   public:
      MyWindow(int w,int h): Fl_Window { w,h },
                             m_image { "./psychedelic.png" }
      {
         m_image_error = m_image.fail();
         switch (m_image_error)
         {
            case Fl_Image::ERR_FILE_ACCESS:
                    std::cerr << "ERR_FILE_ACCESS" << std::endl;
                 break;
            case Fl_Image::ERR_FORMAT:
                    std::cerr << "ERR_FORMAT" << std::endl;
                 break;
            case Fl_Image::ERR_NO_IMAGE:
                    std::cerr << "ERR_NO_IMAGE" << std::endl;
                 break;
         }
      }
      void draw() override
      {
         Fl_Window::draw();
         fl_color(FL_BLACK);

         // FL_ALIGN_BOTTOM_RIGHT
         fl_font(FL_COURIER,12);
         fl_color(FL_BLACK);
         fl_draw("FL_ALIGN_BOTTOM_RIGHT",
                 0,0, w(), h(),
                 FL_ALIGN_BOTTOM_RIGHT,nullptr,false);

         // FL_ALIGN_TOP_RIGHT with image
         if (!m_image_error)
         {
            fl_font(FL_HELVETICA_BOLD,12);

            fl_draw("FL_ALIGN_TOP_RIGHT",0,0,w(),h(),
                    FL_ALIGN_TOP_RIGHT,&m_image,false);
         }

         // FL_ALIGN_BOTTOM_LEFT with symbol
         fl_font(FL_SCREEN,12);
         fl_draw("With symbol @refresh",0,0,w(),h(),
                 FL_ALIGN_BOTTOM_LEFT,nullptr,true);

         // Variations of FL_ALIGN ...
         fl_font(FL_TIMES,40);
         const char* text { "Text" };
         int dx,dy,width,height;
         fl_text_extents(text,dx,dy,width,height);
         auto x { (w() - width) / 2 };
         auto y { (h() - height) / 2 };
         fl_rect(x + dx,y + dy + height,width,height,FL_RED);
         fl_color(FL_BLACK);
         fl_draw(text,x,y,width,height,
                 FL_ALIGN_CENTER,nullptr,false);
         fl_color(FL_MAGENTA);
         fl_font(FL_TIMES,76);
         fl_draw(text,x - (width * 1/3),y - (height * 1/3),
                 width + (width * 2/3),height + (height * 2/3),
                 FL_ALIGN_CENTER | FL_ALIGN_CLIP,nullptr,false);

         // Rotated text
         // Selecting FL_SCREEN in the next line,
         // disables rotation under MS Windows.
         fl_font(FL_HELVETICA,18);
         fl_color(FL_BLACK);
         fl_draw(315,"Rotated",5,10);
      }
   private:
      Fl_PNG_Image m_image;
      int m_image_error;
};

int main(int argc,char* argv[])
{
   MyWindow window { 320,240 };
   window.end();
   window.resizable(window);
   window.show(argc,argv);
   return Fl::run();
}
