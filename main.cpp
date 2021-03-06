#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>
#include "src/Interval.h"
#include "src/Solver.h"
#include <mpi/mpi.h>

using namespace std;

int main() {
    using boost::math::constants::pi;
    using boost::multiprecision::cpp_dec_float_50;

    int howManyThreads = 4;
    int receive_port = 1;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);


    int startTime = clock();

    int intervalA = -5;
    int intervalB = 20;
    double (*derivative)(double)= &dfun2;
    double (*function)(double)=&fun2;
    double L = 20;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Data " << std::endl;
    std::cout << "Min x: " << intervalA << std::endl;
    std::cout << "Max x: " << intervalB << std::endl;
    std::cout << "L: " << L << std::endl;
    std::cout << "---------------------------" << std::endl;


    double step = (std::abs(intervalA-intervalB))/howManyThreads;

    /*for(int i=0; i < howManyThreads; howManyThreads++ ) {
        if (world_rank == i) {
            Interval *nowy = new Interval(intervalA + i * step, intervalA + (i + 1) * step, derivative, function, L);
            Solver *solver = new Solver(*nowy, derivative, function, L);

            solver->runAlgorithm(processor_name, world_rank, world_size);
        }
    }*/
    if (world_rank == 0) {
        Interval *nowy = new Interval(intervalA, intervalA + step, derivative, function, L);
        Solver *solver = new Solver(*nowy, derivative, function, L);

        solver->runAlgorithm(processor_name, world_rank, world_size, receive_port);
    }
    else if (world_rank == 1) {
        Interval *nowy = new Interval(intervalA + step, intervalA + 2*step, derivative, function, L);
        Solver *solver = new Solver(*nowy, derivative, function, L);

        solver->runAlgorithm(processor_name, world_rank, world_size, receive_port);
    }
    else if (world_rank == 2) {
        Interval *nowy = new Interval(intervalA + 2*step, intervalA + 3*step, derivative, function, L);
        Solver *solver = new Solver(*nowy, derivative, function, L);

        solver->runAlgorithm(processor_name, world_rank, world_size, receive_port);
    }
    else if (world_rank == 3) {
        Interval *nowy = new Interval(intervalA + 3*step, intervalB, derivative, function, L);
        Solver *solver = new Solver(*nowy, derivative, function, L);

        solver->runAlgorithm(processor_name, world_rank, world_size, receive_port);
    }

    int duration = clock() - startTime;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Czas trwania: " << duration << "[ms] " << std::endl;
    std::cout << "---------------------------" << std::endl;


    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}

