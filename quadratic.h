#ifndef QUADRATIC_H_INCLUDED
#define QUADRATIC_H_INCLUDED

const int INFINITE_ROOTS_COUNT = -1;
const double PRECISION = 1e-3;

int  solveQuadraticEquation (double a, double b, double c, double *x1, double *x2);
int  solveLinearEquation    (double b, double c, double *x);
bool isEqual                (double x, double y);
void printOK                (int testNumber);
void readCoefficients       (double *a, double *b, double *c);
void readCoefficient        (double *pointerToCoefficient, char typeCoefficient);
void clearConsoleBuffer     ();
void printAnswer            (int rootsCount, double x1, double x2);

void testAll                    ();
void testSolveQuadraticEquation (int testNumber, double a, double b, double c,
                                 int correctRootsCount, double correctX1, double correctX2);
void testSolveLinearEquation    (int testNumber, int correctRootsCount, double k, double b, double correctX);
void testIsEqual                (int testNumber, double x, double y, bool correctAnswer);

#endif // QUADRATIC_H_INCLUDED
