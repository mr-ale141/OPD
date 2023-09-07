#include <cstdio>

int main() {
    // 1. prompt user to enter coefficients
    std::puts("please enter a and b for 'ax + b = 0':");
    // 2. read coefficients for equation `ax + b = 0`
    int a = 0;
    int b = 0;
    std::scanf("%d %d", &a, &b);
    // 3. solve equation `ax + b = 0`
    // solution: `x = -b / a`
    int x = -b / a;
    std::printf("solution: %d\n", x );
}