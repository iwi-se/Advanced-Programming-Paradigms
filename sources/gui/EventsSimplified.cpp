// EventsSimplified.cpp by Ulrich Eisenecker, April 12, 2024

#include <FL/Fl.H> // Must be included by each FLTK-program
#include <FL/Fl_Window.H> // Because of Fl_Window
#include <FL/names.h> // Because of fl_eventnames
#include <iostream>

// Events can also be handled in a free event handler function.
int printAndForwardEvents(int event,Fl_Window* window)
{
   static unsigned long long c { 0 };
   std::cout << c++ << '\t' << fl_eventnames[event];
   if (event == FL_KEYBOARD)
   {
      std::cout << '\t' << Fl::event_key() << '\t' << Fl::event_text();
   }
   std::cout << std::endl;
   return Fl::handle_(event,window);
}

int main()
{
   // Setting the free event handler function.
   Fl::event_dispatch(printAndForwardEvents);
   const auto width { 320 };
   const auto height { 240 };
   Fl_Window window { (Fl::w() - width) / 2,
                      (Fl::h() - height) / 2,
                      width,height };
   window.end();
   window.resizable(window);
   window.show();
   return Fl::run();
}
