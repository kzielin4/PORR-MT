#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>
#include "src/Interval.h"
#include "src/Solver.h"
#include <pthread.h>


void* print_message(void*) {
    std::cout << " ###### Launched by thread #########" << std::endl;
    return NULL;
}

int main() {
    using boost::math::constants::pi;
    using boost::multiprecision::cpp_dec_float_50;
    int startTime = clock();


    pthread_t t1;

    for(int i= 0; i <= 100; i++) {
        pthread_create(&t1, NULL, &print_message, NULL);
    }

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

    solver->test2();

    int duration = clock() - startTime;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Duration: " << duration << "[ms] " << std::endl;
    std::cout << "---------------------------" << std::endl;

    pthread_join(t1, NULL);
    return 0;
}

