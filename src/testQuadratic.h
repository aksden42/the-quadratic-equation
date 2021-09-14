#ifndef TESTQUADRATIC_H_INCLUDED
#define TESTQUADRATIC_H_INCLUDED

struct IsEqualTest {
    double firstNumber;
    double secondNumber;
    bool correctAnswer;
};

struct SolveLinearEquationTest {
    int correctRootsCount;
    double k;
    double b;
    double correctX;
};

struct SolveQuadraticEquationTest {
    double a;
    double b;
    double c;
    int correctRootsCount;
    double correctX1;
    double correctX2;
};

void testAll                    ();
void testSolveQuadraticEquation (int testNumber, const SolveQuadraticEquationTest *test);
void testSolveLinearEquation    (int testNumber, const SolveLinearEquationTest *test);
void testIsEqual                (int testNumber, const IsEqualTest *test);

#endif // TESTQUADRATIC_H_INCLUDED
