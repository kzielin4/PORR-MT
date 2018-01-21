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
#include <atomic>
#include <mutex>
#include <thread>

using namespace std;

class Solver {
    std::mutex mutex;
    std::list<Interval> intervalList;
    std::list<Interval>::iterator itGlobal = intervalList.begin();
    double minValue = 999999999999;
    double minx = 999999999999;
    double L;
    int howMuchUp=0;
    double (*derivative)(double);
    double (*function)(double);
    bool isNOTFound = true;

public:
    Solver(const Interval &interval, double (*derivative1)(double), double (*function2)(double), double LVal){
        L = LVal;
        intervalList.push_back(interval);
        derivative = derivative1;
        function = function2;
    };
public:
    void addIntervalToList(const Interval &interval) {
        mutex.lock();
        intervalList.push_back(interval);
        mutex.unlock();
    }

    void removeIntervalFromList() {
        mutex.lock();
        intervalList.pop_front();
        --howMuchUp;
        mutex.unlock();
    }

    list<Interval>::iterator getBeginIterator(){
        mutex.lock();
        std::list<Interval>::iterator it = intervalList.begin();
        mutex.unlock();
        return it;
    }

    tuple<list<Interval>::iterator,double> increaseAndGetIterator(){
        mutex.lock();
        bool isNotOutOfMemory;
//        isNotOutOfMemory = it != intervalList.end();
//        for (int i =0 ;i<howMuchUp+1;++i) {
//            isNotOutOfMemory = it != intervalList.end();
//           if (!isNotOutOfMemory) {
//                ++it;
//           }
//       }
//        ++howMuchUp;
        isNotOutOfMemory =  intervalList.size()!=0;
        std::list<Interval>::iterator it = intervalList.begin();
        if(isNotOutOfMemory) {
            intervalList.pop_front();
            mutex.unlock();
            return std::make_tuple(it, isNotOutOfMemory);
        }
        mutex.unlock();
        return std::make_tuple(it, isNotOutOfMemory);
    }

    double getFunVal(double val) const {
        return function(val);
    }

    bool isEndOfList(){
        mutex.lock();
        int size = intervalList.size();
        mutex.unlock();
        return size==0;
    }

    std::tuple<double,double,double> countIntervalCrossPoint(double a, double b,double L) {
        double result;
        double funValA =getFunVal(a);
        double funValB =getFunVal(a);
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

public:

    void runAlgorithm(){
       // test();
        thread t1(&Solver::test, this);
        thread t2(&Solver::test, this);
        thread t3(&Solver::test, this);
        thread t4(&Solver::test, this);
        thread t5(&Solver::test, this);
        thread t6(&Solver::test, this);
        thread t7(&Solver::test, this);
        thread t8(&Solver::test, this);
        thread t9(&Solver::test, this);
        thread t0(&Solver::test, this);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();
        t0.join();
    }
    bool getisNOTFound(){
        mutex.lock();
        bool isNotFound = isNOTFound;
        mutex.unlock();
        return isNotFound;
    }

    void setIsNOTFoundFalse(){
        mutex.lock();
        isNOTFound = false;
        mutex.unlock();
    }

    double getminValue(){
        mutex.lock();
        double minValueTmp = minValue;
        mutex.unlock();
        return minValueTmp;
    }

    void setminValueXY(double minValY, double minValX){
        mutex.lock();
        minValue = minValY;
        minx = minValX;
        mutex.unlock();
    }

    void printEnd(int i){
        cout<<"Koniec"<< std::endl;
        std::cout << "Solver:" << std::endl;
        mutex.lock();
        std::cout << "X: " << minx << "   Y: " << minValue << std::endl;
        std::cout << "Ilosc:" << i<<std::endl;
        mutex.unlock();
        return;
    }

    void test() {
        std::list<Interval> minIntervalList;
        double x, result;
        std::list<Interval>::iterator it ;
        bool outNotOfMemory = true;
        double aprox;
        int i=0;
        std::tie(it, outNotOfMemory)= increaseAndGetIterator();
        if(!outNotOfMemory){
            printEnd(i);
            return;
        }
        while (getisNOTFound()){
            //std::tie(x, result, aprox) = it->countIntervalCrossPoint();
            std::tie(x, result, aprox) = countIntervalCrossPoint(it->a,it->b,L);
            if (aprox >= getminValue() ||
                (result <= getminValue() && std::abs(it->a - it->b) < 0.01)) {
                if (std::abs(it->a - it->b) < 0.01 ) {
                    setIsNOTFoundFalse();
                }
                std::tie(it, outNotOfMemory)= increaseAndGetIterator();
                if(!outNotOfMemory){
                    printEnd(i);
                    return;
                }
                //removeIntervalFromList();
            } else {
                if (result < getminValue()) {
                    setminValueXY(result,x);
                }
                Interval *firstPoint = new Interval(it->a, x, derivative, function, L);
                //Interval *firstPoint = new Interval(it->getSmallesValue(), x);
                Interval *secondPoint = new Interval(x, it->b, derivative, function, L);
                //Interval *secondPoint = new Interval(x, it->getBiggestValue());
                addIntervalToList(*firstPoint);
                addIntervalToList(*secondPoint);
                std::tie(it, outNotOfMemory)= increaseAndGetIterator();
                if(!outNotOfMemory){
                    printEnd(i);
                    return;
                }
                //removeIntervalFromList();
            }
            ++i;
        }
        std::cout << "Solver:" << std::endl;
        std::cout << "X: " << minx << "   Y: " << minValue << std::endl;
        std::cout << "Ilosc:" << i<<std::endl;

    };

};


#endif //UNTITLED_SOLVER_H
