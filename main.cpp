#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>
#include "src/Interval.h"
#include "src/Solver.h"
#include <pthread.h>



void print_message(int i) {
    std::cout << "lolL :"<< i << std::endl;
}

int main() {
    using boost::math::constants::pi;
    using boost::multiprecision::cpp_dec_float_50;
    int startTime = clock();

    int i =2;
    int i2=20;
    std::thread t([&]() {
        while (true)
        {
            std::cout << i << std::endl;
        }
    });
    std::thread t2([&]() {
        while (true)
        {
            std::cout << "12213" << std::endl;
        }
    });

    int intervalA = -12;
    int intervalB = 20;
    double (*derivative)(double)= &dfun5;
    double (*function)(double)=&fun5;
    double L = -1.02;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Data " << std::endl;
    std::cout << "Min x: " << intervalA << std::endl;
    std::cout << "Max x: " << intervalB << std::endl;
    std::cout << "L: " << L << std::endl;
    std::cout << "---------------------------" << std::endl;
    Interval *nowy = new Interval(intervalA, intervalB, derivative, function, L);
    Solver *solver = new Solver(*nowy, derivative, function);
   // solver->test();
    //solver->test2();


    int duration = clock() - startTime;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Duration: " << duration << "[ms] " << std::endl;
    std::cout << "---------------------------" << std::endl;

    return 0;

}

