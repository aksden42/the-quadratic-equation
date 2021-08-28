#include <stdio.h>
#include <math.h>
#include "assert.h"

const int INF = 1e9;
const double EPS = 1e-18;

int checkEps(double x , double y) { // 1 -> true, 0 -> false
    if ( fabs( x - y) < EPS ) return 1;
    return 0;
}

int solveEquation( double a, double b, double c, double *x1, double *x2 ) {
    assert( isfinite( a ));
    assert( isfinite( b ));
    assert( isfinite( c ));
    assert( x1 != NULL );
    assert( x2 != NULL );
    assert( x1 != x2 );
    if ( checkEps( a, 0 )) {
        if ( checkEps( b , 0)) {
            if ( checkEps( c , 0)) return INF;
            return 0;
        }
        *x1 = *x2 = -c / b;
        return 1;
    } else {
        double D = b * b - 4 * a * c;
        if ( D < 0 ) return 0;
        if ( checkEps( D, 0 )) {
            *x1 = *x2 = (-b) / (2 * a);
            return 1;
        } else {
            *x1 = (-b + sqrt( D )) / (2 * a);
            *x2 = (-b - sqrt( D )) / (2 * a);
            return 2;
        }
    }
}

void swap(double *x1, double *x2) {
    double temp = *x1;
    *x1 = *x2;
    *x2 = temp;
}

void doublePairSort(double *x1, double *x2){
    if(!checkEps(*x1, *x2) && *x1 > *x2) swap(x1, x2);
}



int checkSolve(double a, double b, double c, int cnt_user_solve, double user_x1, double user_x2){
    double x1 = 0, x2 = 0;
    int cnt_program_solve = solveEquation(a, b, c, &x1, &x2);
    if(cnt_program_solve != cnt_user_solve){
        return 0;
    }
    if( cnt_user_solve == INF || cnt_user_solve == 0) return 1;
    doublePairSort(&user_x1, &user_x2);
    doublePairSort(&x1, &x2);
    return checkEps(x1, user_x1) && checkEps(x2, user_x2);
}

int main( ) {
    double coef[3]; // a, b, c;
    double x1 = 0, x2 = 0;
    printf( "ax^2 + bx + c = 0 \n" );
    for ( int i = 0; i < 3; i++ ) {
        printf( "%c =", i + 'a' );
        scanf( "%lg", &coef[i] );
    }


    int CntSolveEquation = solveEquation( coef[0], coef[1], coef[2], &x1, &x2 );
    int result = checkSolve(-3, 0, 75, 2, 5, -5);
    if(result) printf("The solutions coincided \n");
    else printf("The solutions did not match \n");
    switch ( CntSolveEquation ) {
        case 0: {
            printf( "No solution" );
            break;
        }
        case 1: {
            printf( "One solution: x = %.18f", x1 );
            break;
        }
        case 2: {
            printf( "Two solutions: x1 = %.18f, x2 = %.18f", x1, x2 );
            break;
        }
        default: {
            printf( "Infinitely many solutions" );
            break;
        }

    }
    return 0;
}
