/*
    File: testcase_generator.cpp
    Purpose: Generate N number of testcases (N is user-defined)
             to feed into simulator
*/
#include "testcase_generator.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

namespace numGenerator {
    using namespace std;
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
    mt19937 generator_int (seed_int);
    mt19937 generator_double (seed_double);
    mt19937 generator_nd_int (seed_nd_int);
    mt19937 generator_nd_double (seed_nd_double);

    /*
        Function: Random number generator (RNG)
        Description: The random number generator randomly generates a number.
                     This number can then be the "value" of a variable.
        Features: 1. Generate a random number within lowerbound and upperbound (both are user-defined).
                  2. Overloaded with types int, double, to be used for different variables.
                  3. mt19937 is a Mersenne Twister is fast and can randomly generate numbers
                     that range from 0 to 4294967295 (more than enough for our simulator).
        Return: Random int / double
    */
    int RNG(int lowerbound, int upperbound) {
        uniform_int_distribution<int> normalize(lowerbound, upperbound);    // uniform distribution (int)
        return normalize(generator_int);
    }
    double RNG(double lowerbound, double upperbound) {
        uniform_real_distribution<double> normalize(lowerbound, upperbound);    // uniform distribution (double)
        return normalize(generator_double);
    }

    /*
        Function: Normal distribution generator (NDG)
        Description: The normal distribution generator generate random numbers according to the normal distribution.
        Features: 1. Generate a random number given the mean and standard deviation.
                  2. Overloaded with types int, double, to be used for different variables.
                  3. mt19937 is a Mersenne Twister is fast and can randomly generate numbers
                     that range from 0 to 4294967295 (more than enough for our simulator).
        Return: Normally distributed int / double
    */
    int NDG(int mean, int standard_deviation) {
        normal_distribution<double> distribution(mean, standard_deviation);    // int distribution
        return (int)distribution(generator_nd_int);
    }
    double NDG(double mean, double standard_deviation) {
        normal_distribution<double> distribution(mean, standard_deviation);    // int distribution
        return distribution(generator_nd_double);
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
        // Empty constructor
    }
    randomVariable::randomVariable(int lowerbound, int upperbound) {
        rInt = RNG(lowerbound, upperbound);
    }
    randomVariable::randomVariable(double lowerbound, double upperbound) {
        rDouble = RNG(lowerbound, upperbound);
    }
    /*
        Function: randomInt, randomDouble
        Description: Generate a random integer or random double for the randomVariable.
        Return: void
    */
    void randomVariable::randomInt(int lowerbound, int upperbound) {
        rInt = RNG(lowerbound, upperbound);
    }
    void randomVariable::randomDouble(double lowerbound, double upperbound) {
        rDouble = RNG(lowerbound, upperbound);
    }
    /*
        Function: setLabel
        Description: Assign a name to the randomVariable.
        Return: void
    */
    void randomVariable::setLabel(string name) {
        label = name;
    }
    /*
        Function: read_Int, read_Double, read_Label
        Description: Returns a random int, random double, or the randomVariable label. 
        Return: int, double, string
    */
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
                  2. Access value of matrix at position i, j with function valueAt
                  3. Supports operations we need such as +, -, *, /
                  4. Equality operator to compare two matrices
    */
    matrix::matrix() {
        // Empty constructor
    }
    matrix::matrix(int n, int m) {
        dim = make_pair(n, m);
        mDouble.resize(n, vector<double>(m, 0.0));
    }
    void matrix::resize(int n, int m) {
        dim = make_pair(n, m);
        mDouble.resize(n, vector<double>(m, 0.0));
    }
    pair<int, int> matrix::dimension() {
        return dim;
    }
    double& matrix::valueAt(int i, int j) {
        return mDouble[i][j];
    }
    matrix matrix::operator+(matrix operand) {
        if (operand.dimension() != dimension()) {
            return *this;
        }
        matrix result;
        result.resize(dim.first, dim.second);
        for (int i(0); i < dim.first; ++i) {
            for (int j(0); j < dim.second; ++j) {
                result.valueAt(i, j) = valueAt(i, j) + operand.valueAt(i, j);
            }
        }
        return result;
    }
    matrix matrix::operator-(matrix operand) {
        if (operand.dimension() != dimension()) {
            return *this;
        }
        matrix result;
        result.resize(dim.first, dim.second);
        for (int i(0); i < dim.first; ++i) {
            for (int j(0); j < dim.second; ++j) {
                result.valueAt(i, j) = valueAt(i, j) - operand.valueAt(i, j);
            }
        }
        return result;
    }
    bool matrix::operator==(matrix operand) {
        if (dimension() != operand.dimension()) {
            return false;
        }
        for (int i(0); i < dim.first; ++i) {
            for (int j(0); j < dim.second; ++j) {
                if (valueAt(i, j) != operand.valueAt(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }
    matrix matrix::operator*(matrix operand) {
        if (dim.second != operand.dimension().first) {
            return *this;
        }
        matrix result;
        result.resize(dim.first, operand.dimension().second);
        for (int i(0); i < dim.first; ++i) {
            for (int j(0); j < operand.dimension().second; ++j) {
                double dotProduct(0);   // First compute dot product
                for (int c(0); c < operand.dimension().first; ++c) {
                    dotProduct += valueAt(i, c) * operand.valueAt(c, j);
                }
                result.valueAt(i, j) = dotProduct;
            }
        }
        return result;
    }
    matrix matrix::operator*(double factor) {
        matrix result;
        result.resize(dim.first, dim.second);
        for (int i(0); i < dim.first; ++i) {
            for (int j(0); j < dim.second; ++j) {
                result.valueAt(i, j) = factor * valueAt(i, j);
            }
        }
        return result;
    }
    matrix matrix::operator/(double denominator) {
        matrix result;
        result.resize(dim.first, dim.second);
        for (int i(0); i < dim.first; ++i) {
            for (int j(0); j < dim.second; ++j) {
                result.valueAt(i, j) = valueAt(i, j) / denominator;
            }
        }
        return result;
    }

    /*
        Class: test case generator
        Description: Returns a matrix containing all testcases, as well as generate a file containing all cases
        Features: 1. Default test-case constraints range from 0-100 of type int
                  2. Generates a number of testcases (user defined) and store it into a matrix
                  3. Store "time constants" which are used to calculate amount of time a customer spends at the cashier
    */
    tcGenerator::tcGenerator(int noOfTestcases, int noOfVariables) {
        numberOfTestcases = noOfTestcases;
        numberOfVariables = noOfVariables;
        testcases.resize(numberOfTestcases, numberOfVariables);
        constraints.resize(numberOfVariables, make_pair(make_pair(0, 100), "int"));
        timeConstants.resize(numberOfVariables, 1);
    }
    /*
        Function: editConstraints
        Description: Set the lowerbound and upperbound of random numbers to be generated.
                     These randomly generated numbers are to simulation different aspects of customers at a grocery store.
        Return: void
    */
    void tcGenerator::editConstraints(int no, double lowerbound, double upperbound, string type) {
        constraints[no] = make_pair(make_pair(lowerbound, upperbound), type);   // 0-based index
    }
    /*
        Function: generate
        Description: Using the random number constraints set by editConstraints, generate random numbers 
                     for a pre-determined number of customers (which is equivalent to number of testcases).
        Return: void
    */
    void tcGenerator::generate() {
        randomVariable rInt, rDouble;
        ofstream testcases_file;
        char timeBuffer[100];
        time_t t = time(0);
        struct tm * now = localtime(&t);                     // acquire current time
        strftime (timeBuffer,100,"%Y-%m-%d-%H-%M-%S",now);   // create string from current time
        string timeBuff = timeBuffer;
        string filename = "Simulation-" + timeBuff;
        testcases_file.open(filename);                     // create unique file for storing this specific testcase
        testcases_file << left;
        for (int row(0); row < numberOfTestcases; ++row) {
            testcases_file << setw(10) << "Customer " << setw(8) << row + 1 << ": ";
            for (int col(0); col < numberOfVariables; ++col) {
                double randomValue = 0;
                if (constraints[col].second == "int") {
                    rInt.randomInt((int)constraints[col].first.first, (int)constraints[col].first.second);
                    randomValue = rInt.read_Int();
                }
                else if (constraints[col].second == "double") {
                    rDouble.randomDouble((double)constraints[col].first.first, (double)constraints[col].first.second);
                    randomValue = rDouble.read_Double();
                }
                testcases.valueAt(row, col) = randomValue;
                testcases_file << setw(10) << randomValue;  // store the random variables of each customer into file
            }
            testcases_file << "\n";
        }
        testcases_file.close();
    }
    /*
        Function: editTimeConstants
        Description: Edits a matrix that contains time constants. 
                     Time constants are used to determine the amount of time a customer needs to spend at a cashier.
        Return: void
    */
    void tcGenerator::editTimeConstants(int no, int timeConstant) {
        timeConstants.valueAt(no, 0) = timeConstant;
    }
    void tcGenerator::editTimeConstants(int no, double timeConstant) {
        timeConstants.valueAt(no, 0) = timeConstant;
    }
    /*
        Function: returnTestcases, returnTimeConstants
        Description: Return each matrix respectively.
        Return: matrix
    */
    matrix tcGenerator::returnTestcases() {
        return testcases;
    }
    matrix tcGenerator::returnTimeConstants() {
        return timeConstants;
    }
    /*
        Function: getMatrixValue
        Description: Return, in terms of integer, the number stored at position (i, j) of a matrix.
        Return: int
    */
    int tcGenerator::getMatrixValue(int i, int j) {
        return testcases.valueAt(i, j);
    }
}
