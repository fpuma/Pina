#include <utils/genericid.h>

#include <bitset>
#include <iostream>

int main()
{

    std::bitset<100> bs;

    bs[50] = true;

    std::cout << bs;

}