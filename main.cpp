#include <stdio.h>
#include "quadratic.h"
#include "testQuadratic.h"

#define TEST_MODE

int main()
{
    #ifdef TEST_MODE
        testAll ();
        return 0;
    #endif

    double a = 0, b = 0, c = 0;

    printf ("ax^2 + bx + c = 0 \n");
    readCoefficients (&a, &b, &c);

    double x1 = 0, x2 = 0;
    int rootsCount = solveQuadraticEquation (a, b, c, &x1, &x2);
    printAnswer (rootsCount, x1, x2);
    return 0;
}
