#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#define TEST_MODE

const int INFINITE_ROOTS_COUNT = -1;
const double PRECISION = 1e-18;

bool isEqual (double x, double y) {
    assert (isfinite (x));
    assert (isfinite (y));

    if (fabs (x - y) < PRECISION) {
        return true;
    }

    return false;
}

int solveLinearEquation (double b, double c, double *x1, double *x2) {
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (isEqual (b, 0)) {
        if (isEqual (c, 0)) {
            return INFINITE_ROOTS_COUNT;
        }

        return 0;
    }

    *x1 = *x2 = -c / b;
    return 1;
}

int solveQuadraticEquation (double a, double b, double c, double *x1, double *x2) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (isEqual (a, 0)) {
        return solveLinearEquation (b, c, x1, x2);
    }

    double D = b * b - 4 * a * c;
    if (D < 0) {
        return 0;
    }

    if (isEqual (D, 0)) {
        *x1 = *x2 = (-b) / (2 * a);
        return 1;
    }

    *x1 = (-b + sqrt (D)) / (2 * a);
    *x2 = (-b - sqrt (D)) / (2 * a);
    return 2;
}

void clearConsoleBuffer () {
    while (getchar () != '\n');
}

void readCoefficient (double *pointerToCoefficient, char typeCoefficient) {
    assert (pointerToCoefficient != NULL);

    printf ("%c =", typeCoefficient);
    while (scanf ("%lg", pointerToCoefficient) != 1) {
        clearConsoleBuffer ();
        printf ("%c =", typeCoefficient);
    }
}

void readCoefficients (double *a, double *b, double *c) {
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);

    readCoefficient (a, 'a');
    readCoefficient (b, 'b');
    readCoefficient (c, 'c');
}

void printOK (int testNumber) {
    printf ("OK #%d \n", testNumber);
}

void testSolveQuadraticEquation (int testNumber, double a, double b, double c,
                                 int cntSolveQuadraticEquation, double correctX1, double correctX2) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (isfinite (correctX1));
    assert (isfinite (correctX2));

    double x1 = 0, x2 = 0;
    int cntSolveEquation = solveQuadraticEquation (a, b, c, &x1, &x2);
    if (cntSolveEquation != cntSolveQuadraticEquation) {
        printf ("FAIL #%d, a = %lg, b = %lg, c = %lg \n", a, b, c);
        printf ("correctCountSolves = %d, correctX1 = %.18f, correctX2 = %.18f \n", cntSolveQuadraticEquation, correctX1, correctX2);
        printf ("countOfSolutionsQuadraticEquation = %d, x1 = %.18f, x2 = %.18f \n", cntSolveQuadraticEquation, x1, x2);
        return;
    }
    if (cntSolveQuadraticEquation == 0 || cntSolveQuadraticEquation == INFINITE_ROOTS_COUNT) {
        printOK (testNumber);
        return;
    }

    if (( isEqual (x1, correctX1) && isEqual (x2, correctX2)) || (isEqual (x1, correctX2) && isEqual (x2, correctX1)) ) {
        printOK (testNumber);
        return;
    }
    printf ("FAIL #%d, a = %lg, b = %lg, c = %lg \n", a, b, c);
    printf ("correctCountSolves = %d, correctX1 = %.18f, correctX2 = %.18f \n", cntSolveQuadraticEquation, correctX1, correctX2);
    printf ("countOfSolutionsQuadraticEquation = %d, x1 = %.18f, x2 = %.18f \n", cntSolveQuadraticEquation, x1, x2);
}

void printAns (int countOfSolutionsQuadraticEquation, double *x1, double *x2) {
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    switch (countOfSolutionsQuadraticEquation) {
        case 0: 
            printf ("No solution");
            break;
        
        case 1: 
            printf ("One solution: x = %.18f", *x1);
            break;
        
        case 2: 
            printf ("Two solutions: x1 = %.18f, x2 = %.18f", *x1, *x2);
            break;
        
        default: 
            printf ("Infinitely many solutions");
            break;
        
    }
}

void testAll () {
    testSolveQuadraticEquation (1, 0, 4, 7, 1, -1.75, -1.75);
    testSolveQuadraticEquation (2, 0, 0, 0, INFINITE_ROOTS_COUNT, 0, 0);
    testSolveQuadraticEquation (3, -3, 0, 75, 2, -5, 5);
    testSolveQuadraticEquation (4, -2, 0, 7, 2, -1.870828693386970700, 1.870828693386970700);
    testSolveQuadraticEquation (5, 16, -8, 1, 1, 0.25, 0.25);
    testSolveQuadraticEquation (6, 9, -6, 2,0, 0, 0);
}

int main () {
#ifdef TEST_MODE
    testAll ();
    return 0;
#endif
    
    
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    printf ("ax^2 + bx + c = 0 \n");
    readCoefficients (&a, &b, &c);
    int CntSolveQuadraticEquation = solveQuadraticEquation (a, b, c, &x1, &x2);
    printAns (CntSolveQuadraticEquation, &x1, &x2);
    return 0;
}
