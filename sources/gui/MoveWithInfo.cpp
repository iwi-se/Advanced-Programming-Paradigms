// MoveWithInfo.cpp by Ulrich Eisenecker, January 22, 2024

#include <ncurses.h>
#include <string>
using namespace std;

const char quit { 27 };
const char symbol { '*' };
const char space { ' ' };
const char left { 'h' };
const char right { 'l' };
const char up { 'j' };
const char down { 'k' };

void printInformation()
{
   // Set color for information
   if (has_colors())
   {
      start_color();
      init_color(COLOR_BLUE,0,0,1000);
      init_color(COLOR_WHITE,1000,1000,1000);
      init_pair(1,COLOR_BLUE,COLOR_WHITE);
      init_pair(2,COLOR_BLACK,COLOR_WHITE);
      attron(COLOR_PAIR(1));
   }
   // Output information
   mvprintw(0,0,"0|0");
   auto yMax { getmaxy(stdscr) };
   auto xMax { getmaxx(stdscr) };
   string maxY { to_string(yMax - 1) };
   mvprintw(yMax - 1,0,(maxY + "|0").c_str());
   string maxX { to_string(xMax - 1) };
   mvprintw(0,xMax - ("0|" + maxX).length(),
              ("0|" + maxX).c_str());
   string maxYX { maxY + "|" + maxX };
   mvprintw(yMax - 1,
            xMax - maxYX.length(),
            maxYX.c_str());
   string info { left + " moves left "s };
   mvprintw(yMax / 2 - 1, xMax / 2 - info.length() - 2,info.c_str());
   info = " "s + right + " moves right"s;
   mvprintw(yMax / 2 - 1, xMax / 2 + 1,info.c_str());
   info = up + " moves up"s;
   mvprintw(yMax / 2 - 3,xMax / 2 - 1 - info.length() / 2,info.c_str());
   info = down + " moves down"s;
   mvprintw(yMax / 2 + 1,xMax / 2 - 1 - info.length() / 2,info.c_str());
   // Rest standard colors
   if(has_colors())
   {
      attron(COLOR_PAIR(2));
      use_default_colors();
   }
}

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
      if (x < getmaxx(stdscr) -1)
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
   initscr();
   noecho();
   curs_set(0);
   bool execute { true };
   printInformation();
   processEvent(0);
   do
   {
      auto event = getEvent();
      if (event == quit) 
      {
         execute = false;
      }
      else
      {
         processEvent(event);
      }
   } while (execute);
   curs_set(1);
   endwin();
}
