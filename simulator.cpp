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
    Description: Stores the time a customer needs during checkout. 
                 Also stores the time when the customer first entered queue.
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
                 There is no reason for keeping it modular.
*/
class Cashier {
    Customer checkingOut;
    public:
    std::queue<Customer> line;
    int timeCashierIsOcuppiedUntil = 0;

    /*
        Function: process
        Description: This simulates a cashier within the grocery store.
        Return: Returns 1 if a customer has checked-out. Return 0 otherwise.
    */
    int process(int current_time) {                                                             
        
        Customer current;
        if (!line.empty())
            current = line.front();
        
        if (checkingOut.checkoutTimeNeeded == 0 && !line.empty()) {                             // If a customer has 0 checkout time, it means the current customer checking-out is not a real customer
            checkingOut = current;                                                              // Hence, we assign the customer in front of the queue for this cashier to checkout at this cashier
            timeCashierIsOcuppiedUntil = current_time + checkingOut.checkoutTimeNeeded;
            line.pop();
            if (!line.empty())
                current = line.front();
        }

        while (current.checkoutTimeNeeded != 0 && current_time - current.timeCustomerEnteredQueue >= 15 * 60 && !line.empty()) {   // 15 minutes has passed. Customers in line has already left.
            line.pop();                                                                                                            // So, we remove them from the queue
            current = line.front();
        }

        if (checkingOut.checkoutTimeNeeded != 0 && current_time == timeCashierIsOcuppiedUntil) {
            Customer emptyCashier;                                                              // Customer has checked-out. Cashier is now empty
            checkingOut = emptyCashier;
            timeCashierIsOcuppiedUntil = 0;
            return 1;                                                                           // Return 1 as one customer has been served
        }
        else {
            return 0;                                                                           // Return 0 as customer at cashier is still checking-out 
        }
    }
};

/*
    Function: simulate
    Description: This is the core of the simulation. Each call to this simulation 
                 simulates one day at a grocery store
    Return: Total customers served during the simulation of a day at a grocery store.
*/
long long simulate(int numberOfCashiers, int numberOfCustomers, testcase::tcGenerator testcases) {
    using namespace testcase;
    using namespace std;
    int current_time = 0;                                                                       // current_time is to simulate a day. ++current_time = plus one second.

    Cashier *cashiers = new Cashier[numberOfCashiers];                                          // dynamically allocate cashiers
    
    matrix time_customers = testcases.returnTestcases() * testcases.returnTimeConstants();
    /*
        Explanation of above line:

                    - "testcases.returnTestcases()" and "testcases.returnTimeConstants()" each is a matrix.
                    - So let A = "testcases.returnTestcases()" and B = "testcases.returnTimeConstants()".
                    - A is a "numberOfCustomers" by 2 matrix. 
                    - B is a 2 x 1 matrix.
                    - AB is a matrix multiplication (operator "*" is overloaded so that this is feasible).
                    - AB is a "numberOfCustomers" by 1 matrix, a.k.a vector, where entry "i" stores the 
                      total amount of time customer "i" needs to checkout at a cashier.
    */

    queue<Customer> line;

    for (int cus(0); cus < numberOfCustomers; ++cus) {                                          // we put the time each customer needs for checkout into the data structure queue
        Customer tmp;
        tmp.checkoutTimeNeeded = time_customers.valueAt(cus, 0);
        line.push(tmp);                                                                         // queue creates copies so we don't have to be afraid of tmp being out of scope after for loop ends
    }

    int current_cashier = 0;                                                                    // variables to handle the distribution of customer to each cashier
    double mean = (double)numberOfCustomers / 86400.0;                                          // on average around one customer arrives to the checkout per second
    double standard_deviation = 0.0005;
    double probability = 0;

    long long total_customers_served = 0;

    while (current_time != 86400) {                                                             // Simulation / while loop ends when 86400 seconds past

        double probabilityOfCustomer = max(0.0, numGenerator::NDG(mean, standard_deviation));   // Determine number of customers to be distributed in this time frame
        probability += probabilityOfCustomer;
        int new_customers = probability;                                                        // Customers are discrete, so once the probabilty of having a customer is equal to or greater than 1, new_customer will equal 1 as the double probability will truncate
        if (new_customers >= 1) probability = 0;                                                // Event (customer's arrival) occurred. So we reset the probability of a customer's arrival

        for (;current_cashier < numberOfCashiers && !line.empty() && new_customers--; current_cashier = ++current_cashier % numberOfCashiers) {             
            Customer front_of_line = line.front();                                              // We evenly distribute customers to each cashier as this is the optimal strategy for all customers
            front_of_line.timeCustomerEnteredQueue = current_time;
            line.pop();                            
            cashiers[current_cashier].line.push(front_of_line);                                 // Here, customers are added to the queue for each cashier
        }

        for (int cshr(0); cshr < numberOfCashiers; ++cshr) {
            total_customers_served += cashiers[cshr].process(current_time);                     // We distributed customers to cashier, now we simulate the operations at each cashier
        }
        
        ++current_time;                                                                         // Increase time by one second
    }

    delete[] cashiers;

    return total_customers_served;
}
