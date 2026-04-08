// FI.cpp by Ulrich Eisenecker, September 11, 2025

unsigned long long int factorial3(unsigned long long int n)
{
   auto product { 1 };
   while (n > 0)
   {
      product *= n--;
   }
   return product;
}

int main()
{
   return factorial3(10);
}
