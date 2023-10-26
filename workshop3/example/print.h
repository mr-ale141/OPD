#pragma once

// Печатает числа от value до 1, добавляет слово
//  odd к нечётным числам и even к чётным
void printDownTo1(unsigned value);

// Для внутреннего использования
void printEvenRecursive(unsigned value);

// Для внутреннего использования
void printOddRecursive(unsigned value);