// LifeTUI.cpp by Ulrich Eisenecker, March 19, 2026
// Inspired by
// https://strangeleaflet.com/conways-game-of-life-a-functional-approach/

#include <iostream>
#include <map>
#include <ncurses.h>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Position = int;
using Frequency = int;
using Cell = pair<Position,Position>;
using Cells = set<Cell>;
using Frequencies = map<Cell,Frequency>;

auto neighbors(Cell cell)
{
   Cells result;
   for (Position x : { -1,0,1 })
      for (Position y : { -1,0,1 })
         if (!(x == 0 && y == 0))
            result.insert(make_pair(cell.first + x,cell.second + y));
   return result;
}

auto next(const Cells& cells)
{
   Frequencies f;
   for (auto cell : cells)
   {
      auto n { neighbors(cell) };
      for (auto e : n)
         f[e] += 1;
   }
   Cells result;
   for (auto e : f)
      if (cells.contains(e.first) && (e.second == 2 || e.second == 3))
         result.insert(e.first);
      else
         if (e.second == 3)
            result.insert(e.first);
   return result;
}

Cells seed()
{
   vector<pair<string,Cells>>
      seeds { { "block"s,{ {2,2},{2,3},{3,2},{3,3} } } ,
              { "beehive"s,{ {1,2},{2,1},{2,3},{3,1},{3,3},{4,2} } },
              { "blinker"s,{ {1,0},{1,1},{1,2} } },
              { "pentadecathlon"s,{ {3,5},{3,10},
                                    {4,3},{4,4},{4,6},
                                    {4,7},{4,8},{4,9},{4,11},{4,12},
                                    {5,5},{5,10} } },
              { "acorn"s,{ {5,6},{6,8},{8,5},{7,6},{7,9},{7,10},{7,11} } }
            };
   while (true)
   {
      for (int i { 0 };auto s : seeds)
         cout << ++i << " - " << s.first << endl;
      cout << "\nYour choice: ";
      uintmax_t answer;
      cin >> answer;
      if (answer >= 1 && answer <= size(seeds))
         return seeds[answer - 1].second;
      else
         cout << "Wrong selection, please try again.\n" << endl;
   }
   return { };
}

bool quit()
{
   return getch() == 27;
}

void display(const Cells& cells)
{
   static unsigned long long int round { 0 };
   for (auto cell : cells)
      mvaddch(cell.first,cell.second,'+');
   mvprintw(getmaxy(stdscr) - 1,1,
            ("Generation "s + to_string(round++)).c_str());
}

int main()
{
   Cells og,
         ng { seed() };

   initscr();    // Initialize Ncurses.
   noecho();     // Disable echoing of an entered character.
   curs_set(0);  // Make the cursor transparent.
   timeout(200); // Non-blocking input for 200 ms
   do
   {
      erase(); // Clear entire screen
      display(ng);
      og = ng;
      ng = next(og);
   } while (ng != og && !quit());

   timeout(-1); // Restore blocking input
   getch();     // Wait for key being pressed

   curs_set(1); // Restore the normal appearance of the cursor.
   endwin();    // Stop using Ncurses; restore the normal
}               // behavior of the terminal window.
