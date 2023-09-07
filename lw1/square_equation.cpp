#include <cstdio>
#include <cmath>

int main() {
    // 1. prompt user to enter coefficients
    std::puts("please enter a, b and c for 'ax^2+bx+c=0':");
    // 2. read coefficients for equation `ax^2+bx+c=0`
    float a = 0;
    float b = 0;
    float c = 0;
    float D = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    // 3. solve equation `ax^2+bx+c=0`
    // solution: `x = -b / a`
    D = b * b - 4 * a * c;
    if (0 > D) {
      std::printf("No solutions");
    } else if (0 == D) {
      std::printf("solution: %f\n", -b / (2 * a));
    } else {
    std::printf("1 solution: %f\n", (-b + std::sqrt(D)) / (2 * a));
    std::printf("2 solution: %f\n", (-b - std::sqrt(D)) / (2 * a));
    }
}