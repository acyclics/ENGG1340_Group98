/*
    File: simulator.cpp
    Purpose: Simulates the checkout procedure of a grocery store
*/
#include <queue>
#include "simulator.h"
#include "testcase_generator.h"

/*
    Struct: Cashier
    Description: Stores the time a customer is spending at the cashier
*/
struct Customer {
    int checkoutTimeNeeded = 0;
};

class Cashier {
    public:
    int timer = 0;
    bool occupied = false;
    std::queue<Customer> line;
};

long long simulate(int numberOfCashiers, int numberOfCustomers, testcase::tcGenerator testcases) {
    using namespace testcase;
    using namespace std;
    int current_time = 0;   // time is to simulate a day. ++current_time equals plus one second.

    Cashier *cashiers;
    cashiers = new Cashier[numberOfCashiers];   // dynamically allocate cashiers

    // calculate time needed for each customer with a matrix multiplication and add each customer to a queue
    matrix time_customers = testcases.returnTestcases() * testcases.returnTimeConstants(); 
    queue<Customer> line;
    for (int cus(0); cus < numberOfCustomers; ++cus) {
        Customer tmp;
        tmp.checkoutTimeNeeded = time_customers.valueAt(cus, 0);
        line.push(tmp);   // queue creates copies so we don't have to be afraid of tmp being out of scope after for loop ends
    }

    // variables to handle the distribution of customer to each cashier
    int current_cashier = 0;
    int mean = numberOfCustomers / 86400;   // on average around one customer arrives to the checkout per second
    int standard_deviation = 2;

    // loop ends when 86400 seconds past
    while (current_time != 86400) {

        // determine number of customers to be distributed in this time frame
        int new_customers = numGenerator::NDG(mean, standard_deviation);

        while (new_customers--) {
            for (;current_cashier < numberOfCashiers; current_cashier = ++current_cashier % numberOfCashiers) {
                // we evenly distribute customers to each cashier as this is the optimal strategy for all customers
                Customer front_of_line = line.front();
                line.pop();
                cashiers[current_cashier].line.push(front_of_line);
            }
        }

        ++current_time; // increase time by one second
    }
}
