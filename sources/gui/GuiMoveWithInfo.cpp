// GuiMoveWithInfo.cpp by Ulrich Eisenecker, February 13, 2025

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H> // Because of FL_BEEP_DEFAULT
#include <string>

const char symbol[] { "*" };
const char left { 'h' };
const char right { 'l' };
const char up { 'j' };
const char down { 'k' };

class MyWindow: public Fl_Window
{
   public:
      MyWindow(int w,int h): Fl_Window { w,h }
      {
         fl_font(FL_HELVETICA,18);
         fl_text_extents(symbol,m_dx,m_dy,m_width,m_height);
         m_x = (w - m_width) / 2 - m_dx;
         m_y = (h - m_height) / 2 - m_dy;
      }
      void drawInfo()
      {
         using namespace std;
         string info { };
         int ldx,
             ldy,
             lwidth,
             lheight;
         using namespace std;
         string s;
         fl_color(FL_BLUE);
         for (auto left : { false, true })
         {
            for (auto bottom : { false, true })
            {
               if (left)
               {
                  s = "0|";
               }
               else
               {
                  s = to_string(w() - 1) + "|";;
               }
               if (bottom)
               {
                  s += "0";
               }
               else
               {
                  s += to_string(h() - 1);
               }
               fl_text_extents(s.c_str(),ldx,ldy,lwidth,lheight);
               int lx { left ? -ldx : w() - lwidth - ldx };
               int ly { bottom? -ldy : h() - lheight - ldy - 1 };
               fl_draw(s.c_str(),lx,ly);

            }
         }
         s = left + " moves left"s;
         fl_text_extents(s.c_str(),ldx,ldy,lwidth,lheight);
         fl_draw(s.c_str(),w() / 2 - lwidth - ldx - m_width / 2 - 20,
                           (h() - lheight) / 2 - ldy);

         s = right + " moves right"s;
         auto save { lheight };
         fl_text_extents(s.c_str(),ldx,ldy,lwidth,lheight);
         fl_draw(s.c_str(),w() / 2 - ldx + m_width / 2 + 20,
                           (h() - save) / 2 - ldy);

         s = up + " moves up"s;
         fl_text_extents(s.c_str(),ldx,ldy,lwidth,lheight);
         fl_draw(s.c_str(),(w() - lwidth) / 2 - ldx,
                           (h() - lheight) / 2 - ldy - 2 * fl_height());
         s = down + " moves down"s;
         fl_text_extents(s.c_str(),ldx,ldy,lwidth,lheight);
         fl_draw(s.c_str(),(w() - lwidth) / 2 - ldx,
                           (h() - lheight) / 2 - ldy + 2 * fl_height());
      }
      void draw()
      {
         Fl_Window::draw();
         drawInfo();
         fl_color(FL_BLACK);
         fl_draw(symbol,m_x,m_y);
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
      int handle(int event)
      {
         switch (event)
         {
            case FL_KEYBOARD:
            {
               auto key { Fl::event_key() };
               if (key == left)
               {
                  m_x -= m_width;
                  if (m_x < m_dx)
                  {
                     m_x = -m_dx;
                     flash();
                  }
               }
               if (key == right)
               {
                  m_x += m_width;
                  if (m_x > w() - m_width - m_dx - 1)
                  {
                     m_x = w() - m_width - m_dx;
                     flash();
                  }
               }
               if (key == up)
               {
                  m_y -= m_height;
                  if (m_y < -m_dy)
                  {
                     m_y = -m_dy;
                     flash();
                  }
               }
               if (key == down)
               {
                  m_y += m_height;
                  if (m_y > h() - 2 * m_height - m_dy)
                  {
                     m_y = h() - m_height - m_dy - 1;
                     flash();
                  }
               }
               if ((key != left) && (key != right) &&
                   (key != up) && (key != down))
               {
                  fl_beep(FL_BEEP_DEFAULT);
               }
               else
               {
                  redraw();
               }
            }
         }
         return Fl_Window::handle(event);
      }
   private:
      int m_dx,
          m_dy,
          m_width,
          m_height,
          m_x,
          m_y;
};

int main(int argc,char* argv[])
{
   MyWindow window { 320,240 };
   window.end();
   window.resizable(&window);
   window.show(argc,argv);
   return Fl::run();
}
