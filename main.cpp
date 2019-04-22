/*
    File: main.cpp
    Purpose: Combine all modules to find optimal solution to problem
*/
#include <iostream>
#include <string>
#include "testcase_generator.h"
#include "main.h"

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
            b. distribute customers to different cashiers in a period of time
  */

  int numberOfCashiers = 1;

  //step 2B: once the first customer reach the cashiers, start the timer for that cashier.
  //step 2C: for each occupied cashiers, once reached 15min, flush queue.
  //step 2C: sum up the served customers for each cashiers
  //step 2E:continue the loop until global timer reached
  //step 3: caluculate ratio(n/c) and reiterate for the other n.
  
  return 0;
}
