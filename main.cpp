#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>
#include "src/Interval.h"
#include "src/Solver.h"


int main() {
    using boost::math::constants::pi;
    using boost::multiprecision::cpp_dec_float_50;
    int startTime = clock();

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
    solver->test();

    int duration = clock() - startTime;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Czas trwania: " << duration << "[ms] " << std::endl;
    std::cout << "---------------------------" << std::endl;
    return 0;
}

