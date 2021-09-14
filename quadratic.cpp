#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "quadratic.h"

void clearConsoleBuffer ();

void readCoefficient (double *pointerToCoefficient, char typeCoefficient);

int solveQuadraticEquation (double a, double b, double c, double *x1, double *x2) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    *x1 = 0;
    *x2 = 0;

    if (isEqual (a, 0)) {
        return solveLinearEquation (b, c, x1);
    }

    double D = b * b - 4 * a * c;
    if (D < 0) {
        return 0;
    }

    if (isEqual (D, 0)) {
        *x1 = (-b) / (2 * a);
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

    return (fabs (x - y) < PRECISION);
}

void readCoefficients (double *a, double *b, double *c) {
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);

    readCoefficient (a, 'a');
    readCoefficient (b, 'b');
    readCoefficient (c, 'c');
}

void printAnswer (int rootsCount, double x1, double x2) {
    assert (isfinite (x1));
    assert (isfinite (x2));

    switch (rootsCount) {
        case 0:
            printf ("No solution\n");
            break;

        case 1:
            printf ("One solution: x = %.2lf\n", x1);
            break;

        case 2:
            printf ("Two solutions: x1 = %.2lf, x2 = %.2lf\n", x1, x2);
            break;

        default:
            printf ("Infinitely many solutions\n");
            break;
    }
}

void clearConsoleBuffer () {
    while (getchar () != '\n');
}

void readCoefficient (double *pointerToCoefficient, char typeCoefficient) {
    assert (pointerToCoefficient != NULL);

    printf ("%c = ", typeCoefficient);
    while (scanf ("%lf", pointerToCoefficient) != 1) {
        clearConsoleBuffer ();
        printf ("Incorrect input. Please try again: %c = ", typeCoefficient);
    }
}
