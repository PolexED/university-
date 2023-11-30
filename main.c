#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "lib.h"
#define N 100




/*функция индикатор завершения программы*/
void completed(void) {
    printf("\nProgram completed successfully");
}

/*основная функция с которой мы будем работать*/
double orig_f(double x) {
    double y = x*x - sin(x) - 1;
    return y;
}
/*производная для метода касательных*/
double f_dif(double x) {
    double y_dif = 2*x - cos(x); 
    return y_dif;
    }


/*функция вида x = f(x) где f - первоначальная функция для метода итераций*/
double f(double x) {
    double y = (sqrt(sin(x)+1));
    return y;
}



double Newton_method(double prev_x, double eps) {
    double df;
    double f;
    double delta=100;
    double curr_x = prev_x;
    while ((delta) > eps) {
        df = f_dif(curr_x);
        f = orig_f(curr_x);
        double tmp = curr_x;
        curr_x = prev_x - f/df;
        delta = fabs(curr_x) - fabs(prev_x);
        delta = fabs(delta);
        prev_x = curr_x;

    }
    return curr_x;
}

double iter_method(double x, double eps) {
    double prev_x = x;
    double curr_x = f(prev_x);
    double delt = abs(curr_x-prev_x);
    do {
        prev_x = curr_x;
        curr_x = f(prev_x);
        delt = (curr_x-prev_x);     
    } while (delt > eps/10 );

    return prev_x;
}

double dehotomic_method(double a, double b, double eps) {
    double c = (a+b)/2;
    while ((fabs(orig_f(c)) > eps/10)) { 
        c = (a+b)/2;
        if (orig_f(a)*orig_f(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }
    return c;      
}

double chord_method(double curr_x, double prev_x,double eps) { 
    double next_x = 0;
    double tmp;
    do {
        tmp = next_x;
        next_x = curr_x - orig_f(curr_x) * (prev_x- curr_x)/ (orig_f(prev_x) - orig_f(curr_x));
        prev_x = curr_x;
        curr_x = tmp;
    } while (fabs(next_x - curr_x) > eps/10);
    return next_x;
} 


int main(void) {
    
    double eps = 0.0001;
    double x = 1;
    double dehotomic_a = 1;
    double dehotomic_b = 2;
    printf("the input solution is %.1lf, input eps = %lf\ninput a = %.1lf, input b = %.1lf\n", x, eps, dehotomic_a, dehotomic_b);
    double result_of_iter_method = iter_method(x, eps);
    printf("the result of iteration method is %.5lf\n", result_of_iter_method);

    double result_of_Newton_method = Newton_method(x, eps);
    printf("The result of Newton method is %.5lf\n", result_of_Newton_method);

    double result_of_dehotomic_method = dehotomic_method(dehotomic_a,dehotomic_b, eps);
    printf("The result of dehotomic method is %.5lf\n", result_of_dehotomic_method);

    double result_of_chord_method = chord_method(dehotomic_b,dehotomic_a, eps);
    printf("The result of chords method is %.5lf\n", result_of_chord_method);

    completed();
}
