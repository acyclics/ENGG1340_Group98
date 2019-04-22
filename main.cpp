/*
    File: main.cpp
    Purpose: Combine all modules to find optimal solution to problem
*/
#include <iostream>
#include <string>
#include "testcase_generator.h"
#include "main.h"
#include "iomanip"
#include "simulator.h"

int main() {
  using namespace std;
  using namespace testcase;

  /*
    Step 1: 
            Goal: Generate testcases
            a. Let user define number of testcases
            b. Setup customer parameters: amount of items, payment methods
            c. Initialize and generate testcase matrix
  */

  int numberOfCustomers = 0;
  cin >> numberOfCustomers;
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
  gen.editTimeConstants(0, 5);          // each grocery is assumed to take 5 seconds for checkout

  gen.editConstraints(1, 1, 4, "int");  // each payment method is given a multiplier according
  gen.editTimeConstants(1, 3);          // to the theoretical amount of time needed.
                                        // For example, Cash is given a multiplier of 2
                                        // whereas Octopus card is given a multiplier of 1
                                        // as Octopus card needs less moves by the customer
                                        // to pay
  gen.generate();

  /*
    Step 2: 
            Goal: Create simulator
            a. setup cashiers
            b. once the first customer reach the cashiers, start the timer for that cashier
            c. for each occupied cashiers, once reached 15min, flush queue.
            d. sum up the served customers for each cashiers
            e. continue the loop until global timer reached
            f. find optimal number of cashiers by finding the ratio number of cashiers / number of customers served
  */
  for (int numberOfCashiers = 1; numberOfCashiers < 30; ++numberOfCashiers) {
    long long customers_served = simulate(numberOfCashiers, numberOfCustomers, gen);
    cout << left << fixed << setw(25) << "Number of cashiers:";
    cout << setw(10) << numberOfCashiers;
    cout << setw(33) << "Number of served customers:";
    cout << setw(10) << customers_served;
    cout << setw(12) << "Ratio:";
    cout << setw(11) << (double)numberOfCashiers/(double)customers_served << "\n";
  }

  return 0;
}
