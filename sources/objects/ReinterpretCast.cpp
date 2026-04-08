// ReinterpretCast.cpp by Ulrich Eisenecker, March 28, 2023

#include <iostream>
#include <climits>

using namespace std;

using uint_t = unsigned int;

static_assert(sizeof(float) == sizeof(uint_t));

constexpr uint_t one { 1 };

int main()
{
   float f { };
   cout << "Float: ";
   cin >> f;
   uint_t& i { reinterpret_cast<uint_t&>(f) };
   uint_t loop { sizeof(uint_t) * CHAR_BIT };
   while (loop > 0)
   {
     cout << (i & one << (loop - 1) ? '1' : '0' );
     --loop;
   };
   cout << endl;
}
