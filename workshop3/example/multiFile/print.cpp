#include "print.h"
#include <iostream>

void printDownTo1(unsigned value)
{
    if (value % 2 == 0)
    {
        printEvenRecursive(value);
    }
    else
    {
        printOddRecursive(value);
    }
}

void printEvenRecursive(unsigned value)
{
    std::cout << "even " << value << std::endl;
    if (value > 1)
    {
        printOddRecursive(value - 1);
    }
}

void printOddRecursive(unsigned value)
{
    std::cout << "odd " << value << std::endl;
    if (value > 1)
    {
        printEvenRecursive(value - 1);
    }
}