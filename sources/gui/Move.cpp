// Move.cpp by Ulrich Eisenecker, May 28, 2024

#include <ncurses.h>

const char quit { 27 };
const char symbol { '*' };
const char space { ' ' };
const char left { 'h' };
const char right { 'l' };
const char up { 'j' };
const char down { 'k' };

// Get a (keyboard) event.
char getEvent()
{
   char e;
   bool invalid { true };
   do
   {
      e = getch();
      if ((e == quit) || (e == left) || (e == right) || (e == up) || (e == down))
      { 
         invalid = false;
      }
      else
      {
         beep();
      }
   } while (invalid);
   return e;
}

// Execution of code that is specific to an event.
void processEvent(char e)
{
   static int x { getmaxx(stdscr) / 2 - 1 };
   static int y { getmaxy(stdscr) / 2 - 1 };
   
   mvaddch(y,x,space);
   if (e == left)
   {
      if (x > 0)
      {
         --x;
      }
      else
      {
         flash();
      };
   }
   if (e == right)
   {
      if (x < getmaxx(stdscr) - 1)
      {
         ++x;      
      }
      else
      {
         flash();
      }
   }
   if (e == up)
   {
      if (y > 0)
      {
         --y;
      }
      else
      {
         flash();
      }
   }
   if (e == down)
   {
      if (y < getmaxy(stdscr) - 1)
      {
         ++y;
      }
      else
      {
         flash();
      }
   }
   mvaddch(y,x,symbol);
}

int main()
{
   initscr(); // Initialize Ncurses.
   noecho(); // Disable echoing of an entered character.
   curs_set(0); // Make the cursor transparent.
   bool execute { true };
   processEvent(0); // Calling processEvent() to initialize static variables.
   do // Start the event loop.
   {
      auto event { getEvent() };
      if (event == quit) 
      {
         execute = false;
      }
      else
      {
         processEvent(event);
      }
   } while (execute);
   curs_set(1); // Restore the normal appearance of the cursor.
   endwin(); // Stop using Ncurses; restore the normal 
}            // behavior of the terminal window.
