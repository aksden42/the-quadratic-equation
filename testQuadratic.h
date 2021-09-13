#ifndef TESTQUADRATIC_H_INCLUDED
#define TESTQUADRATIC_H_INCLUDED

struct IsEqualTest {
    double firstNumber, secondNumber;
    bool correctAnswer;
};

struct SolveLinearEquationTest {
    int correctRootsCount;
    double k, b;
    double correctX;
};

struct SolveQuadraticEquationTest {
    double a, b, c;
    int correctRootsCount;
    double correctX1, correctX2;
};

void testAll                    ();
void testSolveQuadraticEquation (int testNumber, const SolveQuadraticEquationTest *test);
void testSolveLinearEquation    (int testNumber, const SolveLinearEquationTest *test);
void testIsEqual                (int testNumber, const IsEqualTest *test);

#endif // TESTQUADRATIC_H_INCLUDED
