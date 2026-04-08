// Events.cpp by Ulrich Eisenecker, April 12, 2024

#include <FL/Fl.H> // Must be included by each FLTK-program
#include <FL/Fl_Window.H> // Because of Fl_Window
#include <FL/names.h> // Because of fl_eventnames
#include <iostream>

class EventsWindow: public Fl_Window
{
   public:
      // Make all constructors of Fl_Window available for EventsWindow.
      using Fl_Window::Fl_Window;
      int handle(int event) override
      {
         static unsigned long long c { 0 };
         std::cout << c++ << '\t' << fl_eventnames[event];
         //if (event == FL_KEYBOARD)
         if (event == FL_KEYDOWN)
         {
            std::cout << '\t' << Fl::event_key() << '\t' << Fl::event_text();
         }
         std::cout << std::endl;
         return Fl_Window::handle(event);
      }
};

int main()
{
   const auto width { 320 };
   const auto height { 240 };
   EventsWindow window { (Fl::w() - width) / 2,
                         (Fl::h() - height) / 2,
                         width,height };
   window.end();
   window.resizable(window);
   window.show();
   return Fl::run();
}
