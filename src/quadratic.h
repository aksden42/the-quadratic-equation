#ifndef QUADRATIC_H_INCLUDED
#define QUADRATIC_H_INCLUDED

const int INFINITE_ROOTS_COUNT = -1;
const double PRECISION = 1e-3;

/*!
Solves quadratic equation with given parameters a, b, c
\param[in] a Coefficient a
\param[in] b Coefficient b
\param[in] c Coefficient c
\param[out] x1 The first root of the equation
\param[out] x2 The second root of the equation
/return Number of roots of the equation
*/
int  solveQuadraticEquation (double a, double b, double c, double *x1, double *x2);

/*!
Solves  linear equation with given parameters b, c
\param[in] b Coefficient b
\param[in] c Coefficient c
\param[out] x The root of the equation
/return Number of roots of the equation
*/
int  solveLinearEquation    (double b, double c, double *x);

/*!
Сhecks the equality of two numbers
\param[in] x First number
\param[in] y Second number
/returns True if the numbers are equal with the PRECISION error, otherwise it returns False;
*/
bool isEqual                (double x, double y);

/*!
Entering the coefficients of the quadratic equation
\param[out] a Coefficient a
\param[out] b Coefficient b
\param[out] c Coefficient c
*/
void readCoefficients       (double *a, double *b, double *c);

/*!
Prints solutions of the quadratic equation
\param[in] rootsCount Number of roots
\param[in] x1 First root
\param[in] x2 Second root
*/
void printAnswer            (int rootsCount, double x1, double x2);

#endif // QUADRATIC_H_INCLUDED
