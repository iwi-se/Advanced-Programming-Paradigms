// LifeSimple.cpp by Ulrich Eisenecker, March 19, 2026
// Inspired by
// https://strangeleaflet.com/conways-game-of-life-a-functional-approach/

#include <iostream>
#include <map>
#include <print>
#include <set>
#include <utility>

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

int main()
{
   Cells ng { { 1,0 },{ 1,1 },{ 1,2 } },
         og;
   unsigned long long int round { };
   do
   {
      println("Round {}: {}",round++,ng);
      og = ng;
      ng = next(og);
   } while (ng != og);
}
