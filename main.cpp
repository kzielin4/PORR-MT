#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>
#include "src/Interval.h"
#include "src/Solver.h"

using namespace std;

int main() {
    using boost::math::constants::pi;
    using boost::multiprecision::cpp_dec_float_50;
    int startTime = clock();

    int intervalA = -13;
    int intervalB = 13;
    double (*derivative)(double)= &dfun1;
    double (*function)(double)=&fun1;
    double L = 1000;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Data " << std::endl;
    std::cout << "Min x: " << intervalA << std::endl;
    std::cout << "Max x: " << intervalB << std::endl;
    std::cout << "L: " << L << std::endl;
    std::cout << "---------------------------" << std::endl;
    Interval *nowy = new Interval(intervalA, intervalB, derivative, function, L);
    Solver *solver = new Solver(*nowy, derivative, function,L);
    solver->runAlgorithm();

    int duration = clock() - startTime;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Czas trwania: " << duration << "[ms] " << std::endl;
    std::cout << "---------------------------" << std::endl;
    return 0;
}

