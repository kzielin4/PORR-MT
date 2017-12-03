//
// Created by kamil on 28.10.17.
//

#ifndef UNTITLED_DERIVATIVE_H
#define UNTITLED_DERIVATIVE_H

template<typename value_type, typename function_type> value_type derivative(const value_type x, const value_type dx, function_type func);
double fun1(double a);
double fun2(double a);
double fun3(double a);
double fun4(double a);
double fun5(double a);
double dfun1(double a);
double dfun2(double a);
double dfun3(double a);
double dfun4(double a);
double dfun5(double a);
double getL(double (*derivative)(double),double a,double b);

#endif //UNTITLED_DERIVATIVE_H
