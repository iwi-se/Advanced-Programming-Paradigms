// FR.cpp by Ulrich Eisenecker, September 11, 2025

unsigned long long int factorial1(unsigned long long int n)
{
   if (n > 0)
   {
      return n * factorial1(n - 1);
   }
   return 1;
}

int main()
{
   return factorial1(10);
}
