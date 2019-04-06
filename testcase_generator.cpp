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
        seed_nd_double: for the function "double NDG(double mean, double standard_deviation)"
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

namespace testcase {
    using namespace numGenerator;
    using namespace std;
    /*
        Class: randomVariable
        Description: A container for a variable that needs a randomly generated value
        Features: 1. Create a randomVariable and generate either random ints or doubles
                  2. Label the randomVariable with string for better categorization
                  3. Access the randomly generated values with "read" functions
                  4. Three constructors, can initialize random variable with either int and/or double
    */
    randomVariable::randomVariable() {
        // empty constructor
    }
    randomVariable::randomVariable(int lowerbound, int upperbound) {
        rInt = RNG(lowerbound, upperbound);
    }
    randomVariable::randomVariable(double lowerbound, double upperbound) {
        rDouble = RNG(lowerbound, upperbound);
    }
    void randomVariable::randomInt(int lowerbound, int upperbound) {
        rInt = RNG(lowerbound, upperbound);
    }
    void randomVariable::randomDouble(double lowerbound, double upperbound) {
        rDouble = RNG(lowerbound, upperbound);
    }
    void randomVariable::setLabel(string name) {
        label = name;
    }
    int randomVariable::read_Int() {
        return rInt;
    }
    double randomVariable::read_Double() {
        return rDouble;
    }
    string randomVariable::read_Label() {
        return label;
    }

    /*
        Class: matrix
        Description: Matrix to do computations
        Features: 1. By default, constructor and "resize" function initializes all values to zero
    */
    matrix::matrix() {
        // empty constructor
    }
    matrix::matrix(int n, int m) {
        dim = {n, m};
        mInt.resize(n, vector<int>(m, 0));
        mDouble.resize(n, vector<double>(m, 0.0));
    }
    void matrix::resize(int n, int m) {
        dim = {n, m};
        mInt.resize(n, vector<int>(m, 0));
        mDouble.resize(n, vector<double>(m, 0.0));
    }
    int& matrix::at_int(int i, int j) {
        return mInt[i][j];
    }
    double& matrix::at_double(int i, int j) {
        return mDouble[i][j];
    }
}






// DEBUG BELOW, REMOVE WHEN ALL IS DONE
#include <iostream>
int main() {
    using namespace testcase;
    matrix A;
    A.resize(3,3);
    A.at_int(2,2) = 7;
    cout << A.at_int(2,2);
    return 0;
}
