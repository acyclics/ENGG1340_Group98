#ifndef testcase_generator_h
#define testcase_generator_h

/*
    includes:
*/
#include <random>
#include <chrono>
#include <string>
#include <vector>

namespace testcase {
    using namespace std;
    /*
        Class: randomVariable
    */
    class randomVariable {
        int rInt = 0;
        double rDouble = 0.0;
        string label = "";
        public:
        randomVariable();
        randomVariable(int lowerbound, int upperbound);
        randomVariable(double lowerbound, double upperbound);
        void randomInt(int lowerbound, int upperbound);
        void randomDouble(double lowerbound, double upperbound);
        void setLabel(string name);
        int read_Int();
        double read_Double();
        string read_Label();
    };

    /*
        Class: matrix
    */
    class matrix {
        pair<int, int> dim = {0, 0};
        vector<vector<double>> mDouble;
        public:
        matrix();
        matrix(int n, int m);
        void resize(int n, int m);
        pair<int, int> dimension();
        double& valueAt(int i, int j);
        matrix operator+(matrix operand);
        matrix operator-(matrix operand);
        bool operator==(matrix operand);
        matrix operator*(matrix operand);
        matrix operator*(double factor);
        matrix operator/(double denominator);
    };
}

#endif