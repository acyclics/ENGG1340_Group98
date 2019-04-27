/*
    File: main.cpp
    Purpose: Combine all modules to find optimal solution to problem
*/
#include <iostream>
#include <string>
#include <iomanip>
#include "main.h"
#include "testcase_generator.h"
#include "simulator.h"

/*
    Function: main
    Description: This function runs the program.
    Return: 0
*/
int main() {
  using namespace std;
  using namespace testcase;

  /*
    Step 1:
            Goal: Generate testcases
            a. Let user define number of testcases and maximum number of cashiers
            b. Setup customer parameters: amount of items, payment methods
            c. Initialize and generate testcase matrix
            d. Ask user for extra details. These details DOES NOT affect simulation; rather, it changes the method for calculating optimal solution.
            e. If user has extra details, request input. Otherwise, go straight to Step 2.
            f. If the user has extra details, Step 3 will calculate optimal solution with METHOD 1. Else, Step 3 will calculate optimal solution with METHOD 2.
  */

  int numberOfCustomers = 0, maxNumberOfCashiers = 0;                                                        
  cout << left << setw(25) << "Number of customers: ";
  cin >> numberOfCustomers;
  cout << setw(25) << "Number of cashiers: ";
  cin >> maxNumberOfCashiers;
  tcGenerator gen(numberOfCustomers, 2);

  /*
    Testcase description:
                          We placed the testcases into a matrix.
                          Each row corresponds to a customer and
                          each column corresponds to a customer
                          parameter.
    Customer parameter:
                          ID:0 -- amount of goods
                          ID:1 -- payment method -- 1: Octopus card
                                                    2: Cash
                                                    3: Credit card
                                                    4: Electronic payment
  */

  gen.editConstraints(0, 0, 100, "int");
  gen.editTimeConstants(0, 5);          // Each grocery is assumed to take 5 seconds for checkout.
  gen.editConstraints(1, 1, 4, "int");  // Each payment method is given a multiplier according to the theoretical amount of time needed. For example, Cash is given
  gen.editTimeConstants(1, 3);          // a multiplier of 2 whereas Octopus card is given a multiplier of 1 as customers generally need less time to pay by Octopus card.
  gen.generate();

  string user_input;
  cout << setw(100) << "Do you know the average spending of each customer and cost of each cashier? (YES / NO):";
  cin >> user_input;
  int customer_average_spending = 0, cost_of_cashier = 0;
  if (user_input == "YES") {
    // Ask for extra data
    cout << left << setw(25) << "Average spending of customers: ";
    cin >> customer_average_spending;
    cout << setw(25) << "Cost of each cashier: ";
    cin >> cost_of_cashier;
  }
  cout << "\n";

  /*
    Step 2:
            Goal: Simulate! Simulation is done by the function "simulate". Details of implementation can be found in the file simulator.cpp. 
                  Below is a brief overview of the simulation process. Note that we are also gathering info during simulation for finding the optimal solution.
            a. Setup cashiers and start simulation.
            b. Customers will be uniformly distributed to the cashiers throughout the day.
            c. Once a customer has waited in queue for over 15 minutes, he / she will leave the queue.
            d. During the simulation, the number of customers served by each cashier is summed up.
            e. Simulation will continue until "one day" has passed.
            f. When simulation ends, it will return the total number of customers served.
            g. A for-loop will repeat the simulation from 1 to "maxNumberOfCashiers" which is specified by the user.
               The output from each simulation is stored into the array "increment".
            h. Note that during simulations, the minimum number of customers served is constantly updated. This variable is used for Step 3.
  */

  int *increment = new int[maxNumberOfCashiers + 1];
  increment[0] = 0;
  int minimum_customers_served = numeric_limits<int>::max();
  cout << "********************* The following is the results of each simulation *********************\n\n";

  for (int numberOfCashiers = 1; numberOfCashiers <= maxNumberOfCashiers; ++numberOfCashiers) {
    long long customers_served = simulate(numberOfCashiers, numberOfCustomers, gen);
    increment[numberOfCashiers] = customers_served;
    if (minimum_customers_served > customers_served) {
      minimum_customers_served = customers_served;
    }
    cout << left << fixed << setw(25) << "Number of cashiers:";
    cout << setw(10) << numberOfCashiers;
    cout << setw(33) << "Number of served customers:";
    cout << setw(10) << customers_served << "\n";
  }
  cout << "\n";

  /*
    Step 3:
            Goal: Find and output the optimal solution
            a. Iterate through the array "increment".
            b. If the user has provided extra data, use METHOD 1 to find optimal solution. Otherwise, use METHOD 2.
            c. Output the optimal solution.

            Method 1:
                      - We have enough data to find an optimal solution that is tailored towards the user.
                      - If "average customer spending" * "number of served customers" < "cost of each cashier" * "number of cashiers", 
                        then this "number of cashiers" and any larger number of cashiers is "not optimal".
            Method 2:
                      - We do not have enough data to find an optimal solution that is tailored towards the user. So, we must base our decision on statistics alone.
                      - If "number of customers served with (n) cashiers" - "number of customers served with (n - 1) cashiers" < "minimum number of customers served" * 0.9
                        then "n" cashiers and any larger number of cashiers is "not optimal".
  */

  int bottle_neck = 1;

  for (int numberOfCashiers = 1; numberOfCashiers <= maxNumberOfCashiers; ++numberOfCashiers) {
    if (user_input == "YES") {  // METHOD 1
      if (customer_average_spending * increment[numberOfCashiers] < cost_of_cashier * numberOfCashiers) {
        break;
      }
    }
    else {                      // METHOD 2
      if (abs(increment[numberOfCashiers] - increment[numberOfCashiers - 1]) < minimum_customers_served * 0.9) {
        break;
      }
    }
    bottle_neck = numberOfCashiers;
  }

  cout << "The recommended number of cashiers: " << bottle_neck << "\n";  // This is the optimal solution

  delete[] increment;
  
  return 0;
}
