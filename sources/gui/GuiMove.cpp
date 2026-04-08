// GuiMove.cpp by Ulrich Eisenecker, February 13, 2025

#include <FL/Fl.H> // Must be included by each FLTK-program
#include <FL/Fl_Window.H> // Because of Fl_Window
#include <FL/Enumerations.H> // Because of FL_BLACK, FL_Escape, etc.
#include <FL/fl_draw.H> // Because of fl_... functions
#include <FL/fl_ask.H> // Because of FL_BEEP_DEFAULT

const char symbol[] { "*" };
const char left { 'h' };
const char right { 'l' };
const char up { 'j' };
const char down { 'k' };

// MyWindow is a su bclass that offers special drawing and
// event handling as well as additional functionality.
class MyWindow: public Fl_Window
{
   public:
      // The member variables that manage the cursor position
      // of the symbol to be drawn are initialized in the constructor.
      MyWindow(int w,int h): Fl_Window { w,h }
      {
         fl_font(FL_HELVETICA,18);
         fl_text_extents(symbol,m_dx,m_dy,m_width,m_height);
         m_x = (w - m_width) / 2 - m_dx;
         m_y = (h - m_height) / 2 - m_dy;
      }
      // Overriding and extending the member function draw().
      void draw() override
      {
         Fl_Window::draw();
         fl_color(FL_BLACK);
         fl_draw(symbol,m_x,m_y);
      }
      // Provision of the flashing of a window as a member function.
      void flash()
      {
         auto oldColor { color() };
         color(FL_RED);
         redraw();
         Fl::wait(0.25);
         color(oldColor);
         redraw();
      }
      // Handling of the key events for the movement of the symbol.
      int handle(int event) override
      {
         switch (event)
         {
            case FL_KEYBOARD:
            {
               auto key { Fl::event_key() };
               // Unknown keys should be
               // handled with Fl_Window::handle().
               if ((key != left) && (key != right) &&
                   (key != up) && (key != down))
               {
                  fl_beep(FL_BEEP_DEFAULT);
                  return Fl_Window::handle(event);
               }
               // Handle known keys now.
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
               // A known key has been handled.
               // Therefore, redraw() is called
               // and 1 is returned 1 to indicate
               // that the event has been consumed.
               redraw();
               return 1;
            }
         }
         // All other events should be handled by Fl_Window::handle().
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
   window.show(argc,argv);
   return Fl::run(); // Start the FLTK event loop.
}
