//
// Created by kamil on 28.10.17.
//

#ifndef UNTITLED_INTERVAL_H
#define UNTITLED_INTERVAL_H

#include "derivative.h"
#include <iostream>
#include <tuple>
#include <algorithm>

class Interval {
public:
    double a;
    double b;
    double funValA;
    double funValB;
    bool isDericativeExist;
    double (*derivative)(double);
    double (*function)(double);
    double L;

public:
    Interval(double a, double b, double (*derivative1)(double), double (*function2)(double),double L) {
        this->a = a;
        this->b = b;
        this->L = L;
        derivative = derivative1;
        function = function2;
        funValA = function(a);
        funValB = function(b);
    }

    Interval(double a, double b) {
        this->a = a;
        this->b = b;
    }

public:
    std::tuple<double,double,double> countIntervalCrossPoint() {
            isDericativeExist = true;
        double result;
            result = (funValA + L * a - funValB + L * b) / ( 2* L);
            //policz jedna wybrana strone
            double val = funValA-L*(result-a);
            if(result<a){
                result = a+0.01;
            }
            else if(result>b){
                result = b -0.01;
            }
            double resultVal = function(result);
            std::cout << "A: " << a << "   B:" << b << "   X: " << result << "     Y:" << function(result) << std::endl;
            return std::make_tuple(result, resultVal ,val);

    }
    double getH(double x){
        return std::max(funValA - L*(x-a),funValB - L*(b-x));
    }

public:
    double getSmallesValue() {
        return (b >= a) ? a : b;
    }

    double getBiggestValue() {
        return (b >= a) ? b : a;
    }

    double getFunValA() const {
        return funValA;
    }

    double getFunValB() const {
        return funValB;
    }

    double getValuedFromArg(double val) const {
        return function(val);
    }

    bool getIsDericativeExist() {
        return isDericativeExist;
    }
    void setL(double L) {
        Interval::L = L;
    }

    double getL() const {
        return L;
    }

};

#endif //UNTITLED_INTERVAL_H
