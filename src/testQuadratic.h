#ifndef TESTQUADRATIC_H_INCLUDED
#define TESTQUADRATIC_H_INCLUDED

/*!
Test for the isEqual function
firstNumber first number
secondNumber second number
correctAnswer is it true that firstNumber and secondNumber are equal.
*/
struct IsEqualTest {
    double firstNumber;
    double secondNumber;
    bool correctAnswer;
};

/*!
Test for the solveLinearEquation function
correctRootsCount number of solutions
k coefficient k
b coefficient b
correctX the root of the equation
*/
struct SolveLinearEquationTest {
    int correctRootsCount;
    double k;
    double b;
    double correctX;
};

/*!
Test for the solveQuadraticEquation function
a coefficient a
b coefficient b
c coefficient c
correctRootsCount number of solutions
correctX1 the first root of the equation 
correctX2 the second root of the equation 
*/
struct SolveQuadraticEquationTest {
    double a;
    double b;
    double c;
    int correctRootsCount;
    double correctX1;
    double correctX2;
};

/*!
Runs the program on all tests
*/
void testAll                    ();

/*!
Tests the solveQuadraticEquation function
\param[in] testNumber test number
\param[in] test test
*/
void testSolveQuadraticEquation (int testNumber, const SolveQuadraticEquationTest *test);

/*!
Tests the solveLinearEquation function
\param[in] testNumber test number
\param[in] test test
*/
void testSolveLinearEquation    (int testNumber, const SolveLinearEquationTest *test);

/*!
Tests the isEqual function
\param[in] testNumber test number
\param[in] test test
*/
void testIsEqual                (int testNumber, const IsEqualTest *test);

#endif // TESTQUADRATIC_H_INCLUDED
