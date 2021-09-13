#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "quadratic.h"

void testAll () {
    printf ("Test isEqual:\n");
    testIsEqual (1, 0.0345, 0.0348, true);
    testIsEqual (2, 1.2451, 1.2660, false);
    printf("\n");

    printf ("Test solveLinearEquation:\n");
    testSolveLinearEquation (1,                    1, 4, 7, -1.750);
    testSolveLinearEquation (2,                    0, 0, 9, 0.0000);
    testSolveLinearEquation (3, INFINITE_ROOTS_COUNT, 0, 0, 0.0000);
    printf("\n");

    printf ("Test solveQuadraticEquation:\n");
    testSolveQuadraticEquation (1, -3,  0, 75, 2, -5.000, 5.000);
    testSolveQuadraticEquation (2, -2,  0,  7, 2, -1.870, 1.870);
    testSolveQuadraticEquation (3, 16, -8,  1, 1,  0.250, 0.000);
    testSolveQuadraticEquation (4,  9, -6,  2, 0,  0.000, 0.000);
}

void testSolveQuadraticEquation (int testNumber, double a, double b, double c, int correctRootsCount, double correctX1,
                                 double correctX2) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (isfinite (correctX1));
    assert (isfinite (correctX2));

    double x1 = 0, x2 = 0;
    int rootsCount = solveQuadraticEquation (a, b, c, &x1, &x2);

    if (rootsCount != correctRootsCount || ((!isEqual (x1, correctX1) || !isEqual (x2, correctX2)) &&
    (!isEqual (x1, correctX2) || !isEqual (x2, correctX1)))) {
        printf ("Error in Quadratic Equation\n");
        printf ("FAIL #%d, a = %lf, b = %lf, c = %lf\n", testNumber, a, b, c);
        printf ("correctCountSolves = %d, correctX1 = %.2lf, correctX2 = %.2lf\n", correctRootsCount, correctX1, correctX2);
        printf ("countSolves        = %d, x1        = %.2lf, x2        = %.2lf\n", rootsCount, x1, x2);
        return;
    }

    printOK (testNumber);
}

void testSolveLinearEquation (int testNumber, int correctRootsCount, double k, double b, double correctX) {
    assert (isfinite (k));
    assert (isfinite (b));

    double x = 0;
    int rootsCount = solveLinearEquation (k, b, &x);
    if (rootsCount == correctRootsCount && (rootsCount == INFINITE_ROOTS_COUNT || rootsCount == 0)) {
        printOK (testNumber);
        return;
    }

    if (rootsCount != correctRootsCount || !isEqual (x, correctX)) {
        printf ("Error in Linear Equation\n");
        printf ("FAIL #%d, k = %lf, b = %lf\n", testNumber, k, b);
        printf ("correctRootsNumber = %d, correctX = %.2lf", correctRootsCount, correctX);
        printf ("countSolves        = %d, x        = %.2lf", rootsCount, x);
        return;
    }

    printOK (testNumber);
}

void testIsEqual (int testNumber, double x, double y, bool correctAnswer) {
    assert (isfinite (x));
    assert (isfinite (y));

    bool answer = isEqual (x, y);

    if (answer != correctAnswer) {
        printf ("Error in IsEqual\n", PRECISION);
        printf ("FAIl #%d, x = %lf, y = %lf\n", testNumber, x, y);
        printf ("correctAnswer = %d\n", correctAnswer);
        printf ("answer        = %d\n", answer);
        return;
    }

    printOK (testNumber);
}
