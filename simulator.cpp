/*
    File: simulator.cpp
    Purpose: Simulates the checkout procedure of a grocery store
*/
#include <queue>
#include <iostream>
#include "simulator.h"
#include "testcase_generator.h"

/*
    Struct: Customer
    Description: Stores the time a customer needs during checkout
*/
struct Customer {
    int checkoutTimeNeeded = 0;
    int timeCustomerEnteredQueue = 0;
};

/*
    Class: Cashier
    Description: Stores the time a customer is spending at the cashier. 
                 For this Class, we won't divide it into header and source file
                 as the functions and class is only used by the simulator.
                 There is no point to keeping it modular.
*/
class Cashier {
    public:
    std::queue<Customer> line;
    Customer checkingOut;
    int timeCashierIsOcuppiedUntil = 0;
    int process(int current_time) {
        
        Customer current;
        if (!line.empty())
            current = line.front();
        
        if (checkingOut.checkoutTimeNeeded == 0 && !line.empty()) {                             // If a customer has 0 checkout time, it means the current customer checking out is not a real customer
            checkingOut = current;                                                              // Hence, we assign the customer in front of the queue to check out at this cashier
            timeCashierIsOcuppiedUntil = current_time + checkingOut.checkoutTimeNeeded;
            line.pop();
            if (!line.empty())
                current = line.front();
        }

        while (current.checkoutTimeNeeded != 0 && current_time - current.timeCustomerEnteredQueue >= 15 * 60 && !line.empty()) {   // 15 minutes has passed. Customers in line has already left. So we remove them from queue
            line.pop();
            current = line.front();
        }

        if (checkingOut.checkoutTimeNeeded != 0 && current_time == timeCashierIsOcuppiedUntil) {
            Customer emptyCashier;                                                              // Customer has checked out. Cashier is now empty
            checkingOut = emptyCashier;
            timeCashierIsOcuppiedUntil = 0;
            return 1;                                                                           // Return 1 as one customer has been served
        }
        else {
            return 0;     
        }
    }
};

long long simulate(int numberOfCashiers, int numberOfCustomers, testcase::tcGenerator testcases) {
    using namespace testcase;
    using namespace std;
    int current_time = 0;                                                                       // time is to simulate a day. ++current_time equals plus one second.

    Cashier *cashiers = new Cashier[numberOfCashiers];                                          // dynamically allocate cashiers
    
    matrix time_customers = testcases.returnTestcases() * testcases.returnTimeConstants();      // calculate time needed for each customer with a matrix multiplication and add each customer to a queue
    queue<Customer> line;

    for (int cus(0); cus < numberOfCustomers; ++cus) {
        Customer tmp;
        tmp.checkoutTimeNeeded = time_customers.valueAt(cus, 0);
        line.push(tmp);                                                                         // queue creates copies so we don't have to be afraid of tmp being out of scope after for loop ends
    }

    int current_cashier = 0;                                                                    // variables to handle the distribution of customer to each cashier
    double mean = (double)numberOfCustomers / 86400.0;                                          // on average around one customer arrives to the checkout per second
    double standard_deviation = 0.0005;
    double probability = 0;

    long long total_customers_served = 0;

    while (current_time != 86400) {                                                             // loop ends when 86400 seconds past or if queue is empty

        double probabilityOfCustomer = max(0.0, numGenerator::NDG(mean, standard_deviation));   // determine number of customers to be distributed in this time frame
        probability += probabilityOfCustomer;
        int new_customers = probability;                                                        // Customers are discrete, so once the probabilty of having a customer is high enough we add the number of customers by one
        if (new_customers >= 1) probability = 0;                                                // event (customer's arrival) occurred. So we reset the probability of a customer's arrival

        for (;current_cashier < numberOfCashiers && !line.empty() && new_customers--; current_cashier = ++current_cashier % numberOfCashiers) {             
            Customer front_of_line = line.front();                                              // we evenly distribute customers to each cashier as this is the optimal strategy for all customers
            front_of_line.timeCustomerEnteredQueue = current_time;
            line.pop();                            
            cashiers[current_cashier].line.push(front_of_line);
        }

        for (int cshr(0); cshr < numberOfCashiers; ++cshr) {
            total_customers_served += cashiers[cshr].process(current_time);
        }
        
        ++current_time;                                                                         // increase time by one second
    }

    delete[] cashiers;

    return total_customers_served;
}
