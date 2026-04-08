#include <iostream>
#include <string>

using namespace std;

namespace quiet
{
  template<int n = 0, int ...pack>
  auto sum1()
  {
    if constexpr(n == 0) {
      return 0;
    } else /* constexpr */ {
      return operator+(n, sum1<pack... >());
    } 
    
  }
  
}

namespace verbose
{
  template<int n = 0, int ...pack>
  auto sum1()
  {
    std::operator<<(std::operator<<(std::operator<<(std::cout, "sum1<").operator<<(n), ">()").operator<<(std::endl), "no of parameters: ").operator<<(sizeof...(pack)).operator<<(std::endl);
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
    std::operator<<(std::operator<<(std::operator<<(std::cout, "sum1<").operator<<(0), ">()").operator<<(std::endl), "no of parameters: ").operator<<(0).operator<<(std::endl);
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
    std::operator<<(std::operator<<(std::operator<<(std::cout, "sum1<").operator<<(3), ">()").operator<<(std::endl), "no of parameters: ").operator<<(2).operator<<(std::endl);
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
    std::operator<<(std::operator<<(std::operator<<(std::cout, "sum1<").operator<<(5), ">()").operator<<(std::endl), "no of parameters: ").operator<<(1).operator<<(std::endl);
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
    std::operator<<(std::operator<<(std::operator<<(std::cout, "sum1<").operator<<(1), ">()").operator<<(std::endl), "no of parameters: ").operator<<(0).operator<<(std::endl);
    if constexpr(false) {
    } else /* constexpr */ {
      return 1 + sum1();
    } 
    
  }
  #endif
  
  
}

namespace quiet
{
  template<int ...pack>
  auto sum2()
  {
    return (0 + ... + pack);
  }
  
}

namespace verbose
{
  template<typename T, typename S>
  auto repeated(const T & n, S remaining)
  {
    operator<<(std::cout, n);
    if(operator>(remaining, 0)) {
      return std::operator""s(",", 1UL);
    } else {
      return std::operator""s("", 0UL);
    } 
    
  }
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > repeated<int, unsigned long>(const int & n, unsigned long remaining)
  {
    std::cout.operator<<(n);
    if(remaining > 0) {
      return std::operator""s(",", 1UL);
    } else {
      return std::operator""s("", 0UL);
    } 
    
  }
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > repeated<float, unsigned long>(const float & n, unsigned long remaining)
  {
    std::cout.operator<<(n);
    if(remaining > 0) {
      return std::operator""s(",", 1UL);
    } else {
      return std::operator""s("", 0UL);
    } 
    
  }
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > repeated<double, unsigned long>(const double & n, unsigned long remaining)
  {
    std::cout.operator<<(n);
    if(remaining > 0) {
      return std::operator""s(",", 1UL);
    } else {
      return std::operator""s("", 0UL);
    } 
    
  }
  #endif
  
  template<int ...pack>
  auto sum2()
  {
    unsigned long remaining = {sizeof...(pack)};
    std::operator<<(std::cout, "sum2<");
    operator<<(operator<<(operator<<(operator<<(operator<<(((std::operator<<(std::cout, '*')) << ... << repeated(pack, --remaining)), ">()"), endl), "no of parameters: "), sizeof...(pack)), endl);
    return (0 + ... + pack);
  }
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  int sum2<>()
  {
    unsigned long remaining = {0};
    std::operator<<(std::cout, "sum2<");
    std::operator<<(std::operator<<((std::operator<<(std::cout, '*')), ">()").operator<<(std::endl), "no of parameters: ").operator<<(0).operator<<(std::endl);
    return 0;
  }
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  int sum2<3, 5, 1>()
  {
    unsigned long remaining = {3};
    std::operator<<(std::cout, "sum2<");
    std::operator<<(std::operator<<(std::operator<<(std::operator<<(std::operator<<((std::operator<<(std::cout, '*')), repeated(3, --remaining)), repeated(5, --remaining)), repeated(1, --remaining)), ">()").operator<<(std::endl), "no of parameters: ").operator<<(3).operator<<(std::endl);
    return ((0 + 3) + 5) + 1;
  }
  #endif
  
  
}

namespace quiet
{
  template<typename T = double, typename ... Pack>
  auto sum3(const T & n, const Pack &... pack)
  {
    if constexpr(sizeof...(pack) == 0) {
      return n;
    } else /* constexpr */ {
      return operator+(n, sum3(pack... ));
    } 
    
  }
  
}

namespace verbose
{
  template<bool once = true, typename T = double, typename ... Pack>
  auto sum3(T n, const Pack &... pack)
  {
    if constexpr(once) {
      std::operator<<(std::cout, "sum3(");
    } 
    
    operator<<(std::cout, n);
    if constexpr(sizeof...(pack) == 0) {
      std::operator<<(std::cout, ')').operator<<(std::endl);
      return static_cast<type_parameter_0_1 &&>(n);
    } else /* constexpr */ {
      std::operator<<(std::cout, ',');
      return operator+(n, sum3<false>(pack... ));
    } 
    
  }
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double sum3<true, double>(double n)
  {
    if constexpr(true) {
      std::operator<<(std::cout, "sum3(");
    } 
    
    std::cout.operator<<(n);
    if constexpr(true) {
      std::operator<<(std::cout, ')').operator<<(std::endl);
      return static_cast<double &&>(n);
    } else /* constexpr */ {
    } 
    
  }
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double sum3<true, int, float, double>(int n, const float & __pack1, const double & __pack2)
  {
    if constexpr(true) {
      std::operator<<(std::cout, "sum3(");
    } 
    
    std::cout.operator<<(n);
    if constexpr(false) {
    } else /* constexpr */ {
      std::operator<<(std::cout, ',');
      return static_cast<double>(n) + sum3<false>(__pack1, __pack2);
    } 
    
  }
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double sum3<false, float, double>(float n, const double & __pack1)
  {
    if constexpr(false) {
    } 
    
    std::cout.operator<<(n);
    if constexpr(false) {
    } else /* constexpr */ {
      std::operator<<(std::cout, ',');
      return static_cast<double>(n) + sum3<false>(__pack1);
    } 
    
  }
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double sum3<false, double>(double n)
  {
    if constexpr(false) {
    } 
    
    std::cout.operator<<(n);
    if constexpr(true) {
      std::operator<<(std::cout, ')').operator<<(std::endl);
      return static_cast<double &&>(n);
    } else /* constexpr */ {
    } 
    
  }
  #endif
  
  
}

namespace quiet
{
  template<typename ... Pack>
  auto sum4(const Pack &... pack)
  {
    return (0.0 + ... + pack);
  }
  
}

namespace verbose
{
  template<typename ... Pack>
  auto sum4(const Pack &... pack)
  {
    unsigned long remaining = {sizeof...(pack)};
    std::operator<<(std::cout, "sum4(");
    operator<<(operator<<(((std::operator<<(std::cout, '*')) << ... << repeated(pack, --remaining)), ')'), endl);
    return (0.0 + ... + pack);
  }
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double sum4<>()
  {
    unsigned long remaining = {0};
    std::operator<<(std::cout, "sum4(");
    std::operator<<((std::operator<<(std::cout, '*')), ')').operator<<(std::endl);
    return 0.0;
  }
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double sum4<int, float, double>(const int & __pack0, const float & __pack1, const double & __pack2)
  {
    unsigned long remaining = {3};
    std::operator<<(std::cout, "sum4(");
    std::operator<<(std::operator<<(std::operator<<(std::operator<<((std::operator<<(std::cout, '*')), repeated(__pack0, --remaining)), repeated(__pack1, --remaining)), repeated(__pack2, --remaining)), ')').operator<<(std::endl);
    return ((0.0 + static_cast<double>(__pack0)) + static_cast<double>(__pack1)) + __pack2;
  }
  #endif
  
  
}

using namespace verbose;

int main()
{
  std::operator<<(std::cout, "sum1<>():\n").operator<<(verbose::sum1()).operator<<(std::endl);
  std::operator<<(std::cout, "sum1<3,5,1>():\n").operator<<(verbose::sum1<3, 5, 1>()).operator<<(std::endl);
  std::operator<<(std::cout, "======").operator<<(std::endl);
  std::operator<<(std::cout, "sum2<>(): ").operator<<(verbose::sum2()).operator<<(std::endl);
  std::operator<<(std::cout, "sum2<3,5,1>(): ").operator<<(verbose::sum2<3, 5, 1>()).operator<<(std::endl);
  std::operator<<(std::cout, "======").operator<<(std::endl);
  std::operator<<(std::cout, "sum3():\n").operator<<(verbose::sum3(double{})).operator<<(std::endl);
  std::operator<<(std::cout, "sum3(99,1.5f,-0.001):\n").operator<<(verbose::sum3(99, 1.5F, -0.001)).operator<<(std::endl);
  std::operator<<(std::cout, "======").operator<<(std::endl);
  std::operator<<(std::cout, "sum4():\n").operator<<(verbose::sum4()).operator<<(std::endl);
  std::operator<<(std::cout, "sum4(99,1.5f,-0.001):\n").operator<<(verbose::sum4(99, 1.5F, -0.001)).operator<<(std::endl);
  return 0;
}
