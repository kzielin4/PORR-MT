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
#include <mpi/mpi.h>
#include <sstream>


using namespace std;

class Solver {
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
        intervalList.push_back(interval);
    }

    void removeIntervalFromList() {
        intervalList.pop_front();
        --howMuchUp;
    }

    list<Interval>::iterator getBeginIterator(){
        
        std::list<Interval>::iterator it = intervalList.begin();
        return it;
    }

    tuple<list<Interval>::iterator,double> increaseAndGetIterator(){
        
        bool isNotOutOfMemory;
        isNotOutOfMemory =  intervalList.size()!=0;
        std::list<Interval>::iterator it = intervalList.begin();
        if(isNotOutOfMemory) {
            intervalList.pop_front();
            
            return std::make_tuple(it, isNotOutOfMemory);
        }
        
        return std::make_tuple(it, isNotOutOfMemory);
    }

    double getFunVal(double val) const {
        return function(val);
    }

    bool isEndOfList(){
        int size = intervalList.size();
        
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
    // std::cout << "A: " << a << "   B:" << b << "   X: " << result << "     Y:" << function(result) << std::endl;
        return std::make_tuple(result, resultVal ,val);

    }

public:

    void runAlgorithm(char* processor_name, int world_rank, int world_size, int receive_rank){
        // Print off a hello world message
        printf("Hello world from processor %s, rank %d"
                       " out of %d processors\n",
               processor_name, world_rank, world_size);

        test(world_rank, receive_rank);
    }
    bool getisNOTFound(){
        
        bool isNotFound = isNOTFound;
        
        return isNotFound;
    }

    void setIsNOTFoundFalse(){
        
        isNOTFound = false;
        
    }

    double getminValue(){
        
        double minValueTmp = minValue;
        
        return minValueTmp;
    }

    void setminValueXY(double minValY, double minValX){
        
        minValue = minValY;
        minx = minValX;
        
    }

    void printEnd(int i){
        cout<<"Koniec"<< std::endl;
        std::cout << "Solver:" << std::endl;
        
        std::cout << "X: " << minx << "   Y: " << minValue << std::endl;
        std::cout << "Ilosc:" << i<<std::endl;
        
        return;
    }

    void test(int world_rank, int receive_rank) {
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
            } else {
                if (result < getminValue()) {
                    setminValueXY(result,x);
                }
                Interval *firstPoint = new Interval(it->a, x, derivative, function, L);
                Interval *secondPoint = new Interval(x, it->b, derivative, function, L);
                addIntervalToList(*firstPoint);
                addIntervalToList(*secondPoint);

                std::tie(it, outNotOfMemory)= increaseAndGetIterator();
                if(!outNotOfMemory){
                    printEnd(i);
                    return;
                }
            }
            ++i;
        }

        if (world_rank != receive_rank) {
            MPI_Send(&x, 1, MPI_DOUBLE, receive_rank, 0, MPI_COMM_WORLD);
            MPI_Send(&minValue, 1, MPI_DOUBLE, receive_rank, 0, MPI_COMM_WORLD);
        }
        else if(world_rank == receive_rank ) {
            double new_x;
            double new_y;

            MPI_Recv(&new_x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&new_y, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if(new_y < minValue){
                minValue = new_y;
                x = new_x;
            }
        }

        std::cout << "Solver:" << std::endl;
        std::cout << "X: " << minx << "   Y: " << minValue << std::endl;
        std::cout << "Ilosc:" << i<<std::endl;

    };

    inline const char * const BoolToString(bool b)
    {
        return b ? "true" : "false";
    }
};


#endif //UNTITLED_SOLVER_H
