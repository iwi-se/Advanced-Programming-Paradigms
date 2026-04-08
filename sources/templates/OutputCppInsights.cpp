#include <iostream>
#include <string>

using namespace std;

template<int n = 0, int ...pack>
auto sum1()
{
  if constexpr(n == 0) {
    return 0;
  } else /* constexpr */ {
    return operator+(n, sum1<pack... >());
  } 
  
}

#ifdef INSIGHTS_USE_TEMPLATE
template<>
int sum1<0>()
{
  if constexpr(true) {
    return 0;
  } else /* constexpr */ {
  } 
  
}
#endif


#ifdef INSIGHTS_USE_TEMPLATE
template<>
int sum1<3, 5, 1>()
{
  if constexpr(false) {
  } else /* constexpr */ {
    return 3 + sum1<5, 1>();
  } 
  
}
#endif


#ifdef INSIGHTS_USE_TEMPLATE
template<>
int sum1<5, 1>()
{
  if constexpr(false) {
  } else /* constexpr */ {
    return 5 + sum1<1>();
  } 
  
}
#endif


#ifdef INSIGHTS_USE_TEMPLATE
template<>
int sum1<1>()
{
  if constexpr(false) {
  } else /* constexpr */ {
    return 1 + sum1();
  } 
  
}
#endif


int main()
{
  std::operator<<(std::cout, "sum1<>():\n").operator<<(sum1()).operator<<(std::endl);
  std::operator<<(std::cout, "sum1<3,5,1>():\n").operator<<(sum1<3, 5, 1>()).operator<<(std::endl);
  std::operator<<(std::cout, "======").operator<<(std::endl);
  return 0;
}
