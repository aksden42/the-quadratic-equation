#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#define TEST_MODE
const int INF = 1e9;
const double PRECISION = 1e-18;

bool isEqual (double x, double y) {
    if (fabs (x - y) < PRECISION)
    {
        return true;
    }
    return false;
}


int solveLinearEquation (double b, double c, double *x1, double *x2) {
    if (isEqual (b, 0)){
        if (isEqual (c, 0)) {
            return INF;
        }
        return 0;
    }

    *x1 = *x2 = -c / b;
    return 1;
}


int solveQadraticEquation (double a, double b, double c, double *x1, double *x2) {
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
    } else {
        *x1 = (-b + sqrt (D)) / (2 * a);
        *x2 = (-b - sqrt (D)) / (2 * a);
        return 2;
    }
}



void clear (){
    while (getchar () != '\n');
}


void readCoefficient (double *pointerToCoefficient, char typeCoefficient) {
    printf ("%c =", typeCoefficient);
    while(scanf ("%lg", pointerToCoefficient) != 1){
        clear ();
        printf ("%c =", typeCoefficient);
    }
}

void readCoefficients (double *a, double *b, double *c) {
    readCoefficient (a, 'a');
    readCoefficient (b, 'b');
    readCoefficient (c, 'c');
}


void printFAIL (int numberTest, double a, double b, double c, int CntSolveQadraticEquation, double user_x1, double user_x2, double x1, double x2) {
    printf ("FAIL# %d: a = %lg, b = %lg, c = %lg, correctCountSolves = %d, correctX1 = %.18f, correctX2 = %.18f, x1 = %.18f, x2 = %.18f \n", numberTest, a, b, c, CntSolveQadraticEquation, user_x1, user_x2, x1, x2);
}

void printOK (int numberTest){
    printf ("OK# %d \n", numberTest);
}

void testSolveQadraticEquation (int numberTest, double a, double b, double c, int CntSolveQadraticEquation, double user_x1, double user_x2) {
    double x1 = 0, x2 = 0;
    int CntSolveEquation = solveQadraticEquation (a, b, c, &x1, &x2);
    if (CntSolveEquation != CntSolveQadraticEquation) {
        printFAIL (numberTest, a, b, c, CntSolveQadraticEquation, user_x1, user_x2, x1, x2);
        return;
    }
    if (CntSolveQadraticEquation == 0 || CntSolveQadraticEquation == INF){
        printOK (numberTest);
        return;
    }

    if (( isEqual (x1, user_x1) && isEqual (x2, user_x2)) || (isEqual (x1, user_x2) && isEqual(x2, user_x1)) ) {
        printOK (numberTest);
        return;
    }
    printFAIL (numberTest, a, b, c, CntSolveQadraticEquation, user_x1, user_x2, x1, x2);
}


void printAns (int CntSolveQadraticEquation, double *x1, double *x2) {
    assert (x1 != x2);
    switch (CntSolveQadraticEquation) {
        case 0: {
            printf ("No solution");
            break;
        }
        case 1: {
            printf ("One solution: x = %.18f", *x1);
            break;
        }
        case 2: {
            printf ("Two solutions: x1 = %.18f, x2 = %.18f", *x1, *x2);
            break;
        }
        default: {
            printf ("Infinitely many solutions");
            break;
        }

    }
}


void allTest () {
    testSolveQadraticEquation (1, 0, 4, 7, 1, -1.75, -1.75);
    testSolveQadraticEquation (2, 0, 0, 0, INF, 0, 0);
    testSolveQadraticEquation (3, -3, 0, 75, 2, -5, 5);
    testSolveQadraticEquation (4, -2, 0, 7, 2, -1.870828693386970700, 1.870828693386970700);
    testSolveQadraticEquation (5, 16, -8, 1, 1, 0.25, 0.25);
    testSolveQadraticEquation (6, 9, -6, 2,0, 0, 0);
}



int main () {
#ifdef TEST_MODE
    allTest ();
    return 0;
#endif
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    printf ("ax^2 + bx + c = 0 \n");
    readCoefficients (&a, &b, &c);
    int CntSolveQadraticEquation = solveQadraticEquation (a, b, c, &x1, &x2);
    printAns (CntSolveQadraticEquation, &x1, &x2);
    return 0;
}
