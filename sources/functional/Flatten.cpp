// Flatten.cpp by Ulrich Eisenecker, February 16, 2026

#include <print>
#include <ranges>
#include <string>
#include <vector>

using namespace std;

int main()
{
   vector names { "Turi"s,"Uria"s,"Rubio"s,"Nipka"s,"Isa"s,"Peeves"s };
   println("names: {}",names);
   auto initials { names | views::transform([](const auto& n)
                                            { return n | views::take(1);
                                            }
                                           )
                 };
   println("initials: {}",initials);
   auto flattened { initials | views::join };
   println("flattened: {}",flattened);
   auto acronym { flattened | ranges::to<string>() };
   println("acronym: {}",acronym);
}
