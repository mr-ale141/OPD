#include <iostream>

int main()
{
    // в цикле от 1 до 100
    for (int num = 1; num <= 100; num++)
    {
        //  - если число кратно и 3, и 5, вывести FizzBuzz
        if (num % 3 == 0 && num % 5 == 0)
            std::cout << "FizzBuzz" << std::endl;
        //  - иначе если число кратно 3, вывести Fizz
        else if (num % 3 == 0 && num % 5 != 0)
            std::cout << "Fizz" << std::endl;
        //  - иначе если число кратно 5, вывести Buzz
        else if (num % 3 != 0 && num % 5 == 0)
            std::cout << "Bazz" << std::endl;
        //  - иначе вывести число
        else
            std::cout << num << std::endl;
    }
}