#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define TEST_MODE

const int INFINITE_ROOTS_COUNT = -1;
const double PRECISION = 1e-3;

void testAll ();
void testSolveQuadraticEquation (int testNumber, double a, double b, double c,
                                 int correctRootsCount, double correctX1, double correctX2);
void testSolveLinearEquation (int testNumber, int correctRootsCount, double k, double b, double correctX);
void testIsEqual (int testNumber, double x, double y, bool correctAnswer);

int solveQuadraticEquation (double a, double b, double c, double *x1, double *x2);
int solveLinearEquation (double b, double c, double *x);
bool isEqual (double x, double y);
void printOK (int testNumber);
void readCoefficients (double *a, double *b, double *c);
void readCoefficient (double *pointerToCoefficient, char typeCoefficient);
void clearConsoleBuffer ();
void printAnswer (int rootsCount, double x1, double x2);

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
    printAnswer (rootsCount, x1, x2);
    return 0;
}

void testAll () {
    printf ("Test is Equal:\n");
    testIsEqual (1, 0.0345, 0.0348, true);
    testIsEqual (2, 1.2451, 1.2660, false);
    printf("\n");

    printf ("Test solve linear equation:\n");
    testSolveLinearEquation (1,                    1, 4, 7, -1.750);
    testSolveLinearEquation (2,                    0, 0, 9, 0.0000);
    testSolveLinearEquation (3, INFINITE_ROOTS_COUNT, 0, 0, 0.0000);
    printf("\n");

    printf ("Test solve Quadratic Equation:\n");
    testSolveQuadraticEquation (1, -3,  0, 75,                    2, -5.000, 5.000);
    testSolveQuadraticEquation (2, -2,  0,  7,                    2, -1.870, 1.870);
    testSolveQuadraticEquation (3, 16, -8,  1,                    1,  0.250, 0.250);
    testSolveQuadraticEquation (4,  9, -6,  2,                    0,  0.000, 0.000);
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
        printf ("FAIL #%d, a = %lg, b = %lg, c = %lg\n", testNumber, a, b, c);
        printf ("correctCountSolves = %d, correctX1 = %.18f, correctX2 = %.18f\n", correctRootsCount, correctX1, correctX2);
        printf ("countSolves = %d, x1 = %.18f, x2 = %.18f\n", rootsCount, x1, x2);
        return;
    }

    printOK (testNumber);
}

void testSolveLinearEquation(int testNumber, int correctRootsCount, double k, double b, double correctX){
    double x = 0;
    int rootsCount = solveLinearEquation(k, b, &x);
    if (rootsCount == correctRootsCount && (rootsCount == INFINITE_ROOTS_COUNT || rootsCount == 0)) {
        printOK (testNumber);
        return;
    }
    if(rootsCount != correctRootsCount || !isEqual (x, correctX)) {
        printf ("Error in Linear Equation\n");
        printf ("FAIL #%d, k = %lg, b = %lg\n", testNumber, k, b);
        printf ("correctRootsNumber = %d, correctX = %lg", correctRootsCount, correctX);
        printf ("countSolves = %d, x = %lg", rootsCount, x);
        return;
    }

    printOK (testNumber);
}

void testIsEqual(int testNumber, double x, double y, bool correctAnswer){
    bool answer = isEqual (x, y);
    if (answer != correctAnswer){
        printf ("Error in IsEqual\n", PRECISION);
        printf ("FAIl #%d, x = %lg, y = %lg\n", testNumber, x, y);
        printf ("correctAnswer = %d\n", correctAnswer);
        printf ("answer = %d\n", answer);
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

void printAnswer (int rootsCount, double x1, double x2) {
    assert (isfinite (x1));
    assert (isfinite (x2));

    switch (rootsCount) {
        case 0:
            printf ("No solution\n");
            break;

        case 1:
            printf ("One solution: x = %.4f\n", x1);
            break;

        case 2:
            printf ("Two solutions: x1 = %.4f, x2 = %.4f\n", x1, x2);
            break;

        default:
            printf ("Infinitely many solutions\n");
            break;
    }
}
