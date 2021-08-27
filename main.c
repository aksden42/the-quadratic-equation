#include <stdio.h>
#include <math.h>
#include "assert.h"

const int INF = 1e9;
const double EPS = 1e-18;

int checkEps( double x ) { // 1 -> true, 0 -> false
    if ( fabs( x ) < EPS ) return 1;
    return 0;
}


int solveEquation( double a, double b, double c, double *x1, double *x2 ) {
    assert( isfinite( a ));
    assert( isfinite( b ));
    assert( isfinite( c ));
    assert( x1 != NULL );
    assert( x2 != NULL );
    assert( x1 != x2 );
    if ( checkEps( a )) {
        if ( checkEps( b )) {
            if ( checkEps( c )) return INF;
            return 0;
        }
        *x1 = *x2 = -c / b;
        return 1;
    } else {
        double D = b * b - 4 * a * c;
        if ( D < 0 ) return 0;
        if ( checkEps( D )) {
            *x1 = *x2 = (-b) / (2 * a);
            return 1;
        } else {
            *x1 = (-b + sqrt( D )) / (2 * a);
            *x2 = (-b - sqrt( D )) / (2 * a);
            return 2;
        }
    }
}


int main( ) {
    double kaef[3]; // a, b, c;
    double x1 = 0, x2 = 0;
    printf( "ax^2 + bx + c = 0 \n" );
    for ( int i = 0; i < 3; i++ ) {
        printf( "%c =", i + 'a' );
        scanf( "%lg", &kaef[i] );
    }


    int CntSolveEquation = solveEquation( kaef[0], kaef[1], kaef[2], &x1, &x2 );
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