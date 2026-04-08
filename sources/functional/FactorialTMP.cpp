// FactorialTMP.cpp by Ulrich Eisenecker, August 21, 2025

#include <iostream>

template <unsigned long long int n>
struct factorial
{
   static constexpr auto value { n * factorial<n - 1>::value };
};

template <>
struct factorial<0ull>
{
   static constexpr auto value { 1ull };
};

template <unsigned long long int n>
constexpr auto factorial_v { factorial<n>::value };

/* The output<> TMP function calls factorial_v<> and
 * outputs the unsigned integer and its factorial to
 * standard output. To do this, it recursively nests
 * an instance of output<> as a data element.
 * Since the constructor of the aggregated exemplar
 * is executed first, the correct order of values
 * from 0 to limit is produced in the standard output.
 */
template <unsigned long long int limit>
struct output
{
   output()
   {
      std::cout << limit << "! = " << factorial_v<limit> << std::endl;
   }
   output<limit - 1> recurse;
};

/* This complete specialization of the output<>
 * TMP function ends the recursion. It does not
 * have any other data members.
 */
template <>
struct output<0ull>
{
   output()
   {
      std::cout << 0ull << "! " << factorial_v<0ull> << std::endl;
   }
};

/* The evaluate<> TMP function takes a TMP function
 * with an unsigned integer parameter as an argument.
 * It runs from start to stop and decreases the value
 * of stop by step, which is 1 by default. In its
 * constructor, it takes a lambda function as a
 * parameter, which expects an unsigned integer
 * value x and the result of calling the TMP function
 * for x. It also recursively nests a subobject of an
 * instantiation of evaluate<> and calls its
 * constructor with the lambda function as an argument.
 * Since the evaluate<> TMP function uses a TMP
 * function as its first parameter, it can also be
 * called for other TMP functions and not just for
 * factorial<>.
 * Attention: The values for start, stop, and step
 * are not checked! It is therefore the responsibility
 * of the caller to use only valid values.
 * Alternatively, suitable checks can of course also
 * be implemented.
 */
template <template <unsigned long long int> class func,
          unsigned long long int start,
          unsigned long long int stop,
          unsigned long long int step = 1,
          unsigned long long int terminate = stop - start>
struct evaluate
{
   evaluate(auto lambda):recurse(lambda)
   {
      lambda(stop,func<stop>::value);
   }
   evaluate<func,start,stop - step,step,stop - start> recurse;
};

/* The following partial specialization of the
 * TMP function evaluate<> terminates the recursion
 * as soon as stop - start yields 0. It has no
 * further data members, and its constructor
 * accepts the lambda function as an argument
 * but does not call it.
 * */
template <template <unsigned long long int> class func,
          unsigned long long int start,
          unsigned long long int stop,
          unsigned long long int step>
struct evaluate<func,start,stop,step,0ull>
{
   evaluate(auto lambda)
   {
   }
};

using namespace std;

int main()
{
   cout << factorial_v<5> << endl;
   cout << endl;
   output<10> { };

   evaluate<factorial,1,21,2> { [](auto x,auto f_x)
                                 {
                                    cout << x << "! = " << f_x << endl;
                                 }
                             };
}
