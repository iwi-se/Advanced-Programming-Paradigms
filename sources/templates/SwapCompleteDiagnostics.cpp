// SwapCompleteDiagnostics.cpp by Ulrich Eisenecker, July 8, 2025
// Warning: Program does not compile!

#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
concept CanBeSwapped = requires
{
   requires is_destructible_v<T>;
   requires is_copy_constructible_v<T>;
   requires is_assignable_v<T&,T>;
};

void swapVariables(CanBeSwapped auto& a,CanBeSwapped auto& b)
   requires is_same_v<decltype(a),decltype(b)>
{
   CanBeSwapped auto temp { a };
   a = b;
   b = temp;
}

class AllRequirementsMissing
{
   public:
      AllRequirementsMissing() = default;
      AllRequirementsMissing(const AllRequirementsMissing&) = delete;
      AllRequirementsMissing& operator=(const AllRequirementsMissing&) = delete;
      ~AllRequirementsMissing() = delete;
};

int main()
{
   AllRequirementsMissing * p1 { new AllRequirementsMissing },
                          * p2 { new AllRequirementsMissing };
   swapVariables (*p1,*p2);
}
