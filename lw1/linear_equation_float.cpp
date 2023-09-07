#include <cstdio>

int main() {
    // 1. prompt user to enter coefficients
    std::puts("please enter a and b for 'ax + b = 0':");
    // 2. read coefficients for equation `ax + b = 0`
    float a = 0;
    float b = 0;
    std::scanf("%f %f", &a, &b);
    // 3. solve equation `ax + b = 0`
    // solution: `x = -b / a`
    float x = -b / a;
    std::printf("solution: %f\n", x );
}