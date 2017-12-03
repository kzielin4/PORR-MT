//
// Created by kamil on 30.10.17.
//

#ifndef UNTITLED_SOLVER_H
#define UNTITLED_SOLVER_H

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <list>
#include <float.h>
#include "Interval.h"
#include <tuple>

class Solver {

    std::list<Interval> intervalList;
    double minValue;
    double startA;
    double startB;

    double (*derivative)(double);

    double (*function)(double);

public:
    Solver(const Interval &interval, double (*derivative1)(double), double (*function2)(double)) {
        minValue = DBL_MAX;
        intervalList.push_back(interval);
        std::list<Interval>::iterator it = intervalList.begin();
        startA = it->getSmallesValue();
        startB = it->getBiggestValue();
        derivative = derivative1;
        function = function2;

    };
public:
    void addIntervalToList(const Interval &interval) {
        intervalList.push_back(interval);
    }

public:
    void test() {
        Interval *minInterval;
        Interval *minX;
        std::list<Interval> minIntervalList;
        std::list<Interval> minXList;
        std::list<Interval>::iterator it = intervalList.begin();
        double x, result;
        double minx = DBL_MAX;
        int i;
        double L = it->getL();
        bool isFirsLoop = false;
        double lastCorrectX;
        int counter=0;
        for (i = 0; it != intervalList.end(); ++i) {
            std::tie(x, result) = it->countIntervalCrossPoint();
            if (result > minValue) {
                if (intervalList.size() == 1 && std::abs(minInterval->getSmallesValue() - minInterval->getBiggestValue()) > 0.02) {
                    double minA = minInterval->getSmallesValue(), minB = minInterval->getBiggestValue();
                    double funA01 = minInterval->getValuedFromArg(minx - 0.01);
                    double funB01 = minInterval->getValuedFromArg(minx + 0.01);
                    if ((startA <= minA && startB >= minB) && (funA01 < minValue || funB01 < minValue)) {
                        if(lastCorrectX == false){
                            lastCorrectX == true;
                        }
                        else{
                            if(lastCorrectX = x){
                                ++counter;
                                if(counter>50){
                                    std::cout << "Solver:"<< std::endl;
                                    for (it = minXList.begin(); it != minXList.end(); ++it) {
                                        std::cout << "X: " << it->getSmallesValue() << "   Value: " << minValue << std::endl;
                                    }
                                    return;
                                }
                            }
                            else{
                                counter=0;
                            }
                        }
                        lastCorrectX=x;
                        if(L > 0){
                            minA = minx-1;
                            minB = minx-0.1;
                        }
                        else if(L<0){
                            minB = minx + 1;
                            minA = minx;
                        }
                        else{
                            minA = minx - 0.3;
                            minB = minx + 0.3;

                        }
                        if(startA > minA){
                            minA = startA;
                        }
                        if(startB < minB){
                            minB = startB;
                        }

                        Interval *secondPoint = new Interval(minA,
                                                             minB, derivative,
                                                             function,L);
                        addIntervalToList(*secondPoint);
                    }
                }
                ++it;
                intervalList.pop_front();
            } else {//jezeli duzy przedzial a jest ostani element wtedy iteracja od poczatku
                minInterval = new Interval(it->getSmallesValue(), it->getBiggestValue(), derivative, function,L);
                minX = new Interval(x, x, derivative, function,L);
                if(result==minValue){
                    minXList.push_back(*minX);
                    minIntervalList.push_back(*minInterval);
                }
                else{
                    minIntervalList.clear();
                    minIntervalList.push_back(*minInterval);
                    minXList.clear();
                    minXList.push_back(*minX);
                }
                minValue = result;
                minx = x;
                Interval *firstPoint = new Interval(it->getSmallesValue(), x, derivative, function,L);
                addIntervalToList(*firstPoint);
                Interval *secondPoint = new Interval(x, it->getBiggestValue(), derivative, function,L);
                addIntervalToList(*secondPoint);
                ++it;
                intervalList.pop_front();
            }
        }
        std::cout << "Solver:"<< std::endl;
        for (it = minXList.begin(); it != minXList.end(); ++it) {
            std::cout << "X: " << it->getSmallesValue() << "   Value: " << minValue << std::endl;
        }
    };
};


#endif //UNTITLED_SOLVER_H
