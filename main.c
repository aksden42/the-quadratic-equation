#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#define TEST_MODE

const int INFINITE_ROOTS_COUNT = -1;
const double PRECISION = 1e-3;

void testAll ();
void testSolveQuadraticEquation (int testNumber, double a, double b, double c,
                                 int correctRootsCount, double correctX1, double correctX2);

int solveQuadraticEquation (double a, double b, double c, double *x1, double *x2);
int solveLinearEquation (double b, double c, double *x);
bool isEqual (double x, double y);
void printOK (int testNumber);
void readCoefficients (double *a, double *b, double *c);
void readCoefficient (double *pointerToCoefficient, char typeCoefficient);
void clearConsoleBuffer ();
void printAns (int countOfSolutionsQuadraticEquation, double *x1, double *x2);

int main () {
    #ifdef TEST_MODE
        testAll ();
        return 0;
    #endif

    double a = 0, b = 0, c = 0;

    printf ("ax^2 + bx + c = 0 \n");
    readCoefficients (&a, &b, &c);

    double x1 = 0, x2 = 0;
    int rootsCount = solveQuadraticEquation (a, b, c, &x1, &x2);
    printAns (rootsCount, &x1, &x2);
    return 0;
}

void testAll () {
    testSolveQuadraticEquation (1,  0,  4,  7,                    1, -1.750, 0.000);
    testSolveQuadraticEquation (2,  0,  0,  0, INFINITE_ROOTS_COUNT, 0.0000, 0.000);
    testSolveQuadraticEquation (3, -3,  0, 75,                    2, -5.000, 5.000);
    testSolveQuadraticEquation (4, -2,  0,  7,                    2, -1.870, 1.870);
    testSolveQuadraticEquation (5, 16, -8,  1,                    1,  0.250, 0.250);
    testSolveQuadraticEquation (6,  9, -6,  2,                    0,  0.000, 0.000);
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
    if (correctRootsCount == INFINITE_ROOTS_COUNT || rootsCount == correctRootsCount && correctRootsCount == 0) {
        printOK (testNumber);
        return;
    }

    if (rootsCount != correctRootsCount || ((!isEqual (x1, correctX1) || !isEqual (x2, correctX2)) &&
    (!isEqual (x1, correctX2) || !isEqual (x2, correctX1)))) {
        printf ("FAIL #%d, a = %lg, b = %lg, c = %lg\n", testNumber, a, b, c);
        printf ("correctCountSolves = %d, correctX1 = %.18f, correctX2 = %.18f\n", correctRootsCount, correctX1, correctX2);
        printf ("countSolves = %d, x1 = %.18f, x2 = %.18f\n", rootsCount, x1, x2);
        return;
    }

    printOK (testNumber);
}

int solveQuadraticEquation (double a, double b, double c, double *x1, double *x2) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (isEqual (a, 0)) {
        return solveLinearEquation (b, c, x1);
    }

    double D = b * b - 4 * a * c;
    if (D < 0) {
        return 0;
    }

    if (isEqual (D, 0)) {
        *x1 = *x2 = (-b) / (2 * a);
        return 1;
    }

    double sqrtD = sqrt (D);
    *x1 = (-b + sqrtD) / (2 * a);
    *x2 = (-b - sqrtD) / (2 * a);
    return 2;
}

int solveLinearEquation (double k, double b, double *x) { // kx + b = 0
    assert (isfinite (k));
    assert (isfinite (b));
    assert (x != NULL);

    if (isEqual (k, 0)) {
        if (isEqual (b, 0)) {
            return INFINITE_ROOTS_COUNT;
        }

        return 0;
    }

    *x = -b / k;
    return 1;
}

bool isEqual (double x, double y) {
    assert (isfinite (x));
    assert (isfinite (y));

    if (fabs (x - y) < PRECISION) {
        return true;
    }

    return false;
}

void printOK (int testNumber) {
    printf ("OK #%d \n", testNumber);
}

void readCoefficients (double *a, double *b, double *c) {
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);

    readCoefficient (a, 'a');
    readCoefficient (b, 'b');
    readCoefficient (c, 'c');
}

void readCoefficient (double *pointerToCoefficient, char typeCoefficient) {
    assert (pointerToCoefficient != NULL);

    printf ("%c =", typeCoefficient);
    while (scanf ("%lg", pointerToCoefficient) != 1) {
        clearConsoleBuffer ();
        printf ("Incorrect input. Please try again: %c =", typeCoefficient);
    }
}

void clearConsoleBuffer () {
    while (getchar () != '\n');
}

void printAns (int rootsCount, double *x1, double *x2) {
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    switch (rootsCount) {
        case 0:
            printf ("No solution\n");
            break;

        case 1:
            printf ("One solution: x = %.18f\n", *x1);
            break;

        case 2:
            printf ("Two solutions: x1 = %.18f, x2 = %.18f\n", *x1, *x2);
            break;

        default:
            printf ("Infinitely many solutions\n");
            break;
    }
}
