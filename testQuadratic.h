#ifndef TESTQUADRATIC_H_INCLUDED
#define TESTQUADRATIC_H_INCLUDED

void testAll                    ();
void testSolveQuadraticEquation (int testNumber, double a, double b, double c,
                                 int correctRootsCount, double correctX1, double correctX2);
void testSolveLinearEquation    (int testNumber, int correctRootsCount, double k, double b, double correctX);
void testIsEqual                (int testNumber, double x, double y, bool correctAnswer);

#endif // TESTQUADRATIC_H_INCLUDED
