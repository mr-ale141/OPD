// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug .
#include <iostream>

int main()
{
    for (int num = 1; num <= 100; ++num)
    {
        switch (num % 15)
        {
        case 0:
            std::cout << "FizzBuzz" << std::endl;
            break;
        case 5:
        case 10:
            std::cout << "Buzz" << std::endl;
            break;
        case 3:
        case 6:
        case 9:
        case 12:
            std::cout << "Fizz" << std::endl;
            break;
        default:
            std::cout << num << std::endl;
        }
    }
}