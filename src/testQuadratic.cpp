#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "quadratic.h"
#include "testQuadratic.h"

void printOK (int testNumber);

void testAll () {
    IsEqualTest setIsEqualTest[] = {{0.0345, 0.0348, true},
                                    {1.2451, 1.2660, false}};

    SolveLinearEquationTest setSolveLinearEquation[] = {{                   1, 4, 7, -1.750},
                                                        {                   0, 0, 9, 0.0000},
                                                        {INFINITE_ROOTS_COUNT, 0, 0, 0.0000}};

    SolveQuadraticEquationTest setSolveQuadraticEquation[] = {{-3,  0, 75, 2, -5.000, 5.000},
                                                              {-2,  0,  7, 2, -1.870, 1.870},
                                                              {16, -8,  1, 1,  0.250, 0.000},
                                                              { 9, -6,  2, 0,  0.000, 0.000}};

    printf ("Test isEqual:\n");
    for (int i = 0; i < 2; i++) {
        testIsEqual (i + 1, &setIsEqualTest[i]);
    }

    printf ("\nTest solveLinearEquation:\n");
    for (int i = 0; i < 3; i++) {
        testSolveLinearEquation (i + 1, &setSolveLinearEquation[i]);
    }

    printf ("\nTest solveQuadraticEquation:\n");
    for (int i = 0; i < 4; i++) {
        testSolveQuadraticEquation (i + 1, &setSolveQuadraticEquation[i]);
    }
}

void testSolveQuadraticEquation (int testNumber, const SolveQuadraticEquationTest *test) {
    assert (test != NULL);
    assert (isfinite (test->a));
    assert (isfinite (test->b));
    assert (isfinite (test->c));
    assert (isfinite (test->correctX1));
    assert (isfinite (test->correctX2));

    double x1 = 0, x2 = 0;
    int rootsCount = solveQuadraticEquation (test->a, test->b, test->c, &x1, &x2);

    if (rootsCount != test->correctRootsCount || ((!isEqual (x1, test->correctX1) || !isEqual (x2, test->correctX2)) &&
       (!isEqual (x1, test->correctX2) || !isEqual (x2, test->correctX1)))) {
        printf ("Error in Quadratic Equation\n");
        printf ("FAIL #%d, a = %lf, b = %lf, c = %lf\n", testNumber, test->a, test->b, test->c);
        printf ("correctCountSolves = %d, correctX1 = %.2lf, correctX2 = %.2lf\n", test->correctRootsCount, test->correctX1, test->correctX2);
        printf ("countSolves        = %d, x1        = %.2lf, x2        = %.2lf\n", rootsCount, x1, x2);
        return;
    }

    printOK (testNumber);
}

void testSolveLinearEquation (int testNumber, const SolveLinearEquationTest *test) {
    assert (test != NULL);
    assert (isfinite (test->k));
    assert (isfinite (test->b));

    double x = 0;
    int rootsCount = solveLinearEquation (test->k, test->b, &x);
    if (rootsCount == test->correctRootsCount && (rootsCount == INFINITE_ROOTS_COUNT || rootsCount == 0)) {
        printOK (testNumber);
        return;
    }

    if (rootsCount != test->correctRootsCount || !isEqual (x, test->correctX)) {
        printf ("Error in Linear Equation\n");
        printf ("FAIL #%d, k = %lf, b = %lf\n", testNumber, test->k, test->b);
        printf ("correctRootsNumber = %d, correctX = %.2lf", test->correctRootsCount, test->correctX);
        printf ("countSolves        = %d, x        = %.2lf", rootsCount, x);
        return;
    }

    printOK (testNumber);
}

void testIsEqual (int testNumber, const IsEqualTest* test) {
    assert (test != NULL);
    assert (isfinite (test->firstNumber));
    assert (isfinite (test->secondNumber));

    bool answer = isEqual (test->firstNumber, test->secondNumber);

    if (answer != test->correctAnswer) {
        printf ("Error in IsEqual\n");
        printf ("FAIl #%d, x = %lf, y = %lf\n", testNumber, test->firstNumber, test->secondNumber);
        printf ("correctAnswer = %d\n", test->correctAnswer);
        printf ("answer        = %d\n", answer);
        return;
    }

    printOK (testNumber);
}

void printOK (int testNumber) {
    printf ("OK #%d \n", testNumber);
}
