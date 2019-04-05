/*
    File: testcase_generator.cpp
    Purpose: Generate N number of testcases (N is user-defined) 
             to feed into simulator
*/
#include "testcase_generator.h"

namespace numGenerator {
    /*
        seed: Contains information required to generate random numbers.
              These variables, in most cases, should only be generated once.
        seed_int: for the function "int RNG(int lowerbound, int upperbound)"
        seed_double: for the function "double RNG(double lowerbound, double upperbound)"
        seed_nd_int: for the function "int NDG(int mean, int standard_deviation)"
    */
    unsigned seed_int = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed_double = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed_nd_int = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed_nd_double = std::chrono::system_clock::now().time_since_epoch().count();

    /*
        Function: Random number generator (RNG)
        Description: The random number generator randomly generates a number. 
                     This number can then be the "value" of a variable.
        Features: 1. Generate a random number within lowerbound and upperbound (both are user-defined).
                  2. Overloaded with types int, double, to be used for different variables.
                  3. mt19937 is a Mersenne Twister is fast and can randomly generate numbers
                     that range from 0 to 4294967295 (more than enough for our simulator).
    */
    int RNG(int lowerbound, int upperbound) {
        using namespace std;
        mt19937 generator (seed_int);
        uniform_int_distribution<int> normalize(lowerbound, upperbound);    // uniform distribution (int)
        return normalize(generator);
    }
    double RNG(double lowerbound, double upperbound) {
        using namespace std;
        mt19937 generator (seed_double);
        uniform_real_distribution<double> normalize(lowerbound, upperbound);    // uniform distribution (double)
        return normalize(generator);
    }

    /*
        Function: Normal distribution generator (NDG)
        Description: The normal distribution generator generate random numbers according to the normal distribution. 
        Features: 1. Generate a random number given the mean and standard deviation.
                  2. Overloaded with types int, double, to be used for different variables.
                  3. mt19937 is a Mersenne Twister is fast and can randomly generate numbers
                     that range from 0 to 4294967295 (more than enough for our simulator).
    */
    int NDG(int mean, int standard_deviation) {
        using namespace std;
        mt19937 generator (seed_nd_int);
        normal_distribution<int> distribution(mean, standard_deviation);    // int distribution
        return distribution(generator);
    }
    double NDG(double mean, double standard_deviation) {
        using namespace std;
        mt19937 generator (seed_nd_double);
        normal_distribution<double> distribution(mean, standard_deviation);    // int distribution
        return distribution(generator);
    }
}








// DEBUG BELOW, REMOVE WHEN ALL IS DONE
#include <iostream>
int main() {
    using namespace std;
    using namespace numGenerator;
    cout << RNG(1.111, 99.9999);
    return 0;
}
