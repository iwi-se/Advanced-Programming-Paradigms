// RandomDevice.cpp by Ulrich Eisenecker, May 2, 2025

#include <iostream>
#include <random>

using namespace std;

int main()
{
   cout << "Directly using a (pseudo) random number device." << endl;
   random_device rnd_device;
   cout << "Entropy = \t" << rnd_device.entropy()
        << "\nMinval  = \t" << rnd_device.min()
        << "\nMaxval  = \t" << rnd_device.max()
        << endl;
   for (int i { }; i < 5; ++i)
   {
      cout << rnd_device() << endl;
   }
}
