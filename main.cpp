/*
    File: main.cpp
    Purpose: Combine all modules to find optimal solution to problem
*/
#include <iostream>
#include <string>
#include "testcase_generator.h"
#include "main.h"
#include <iomanip>
#include "simulator.h"

int main() {
  using namespace std;
  using namespace testcase;

  /*
    Step 1:
            Goal: Generate testcases
            a. Let user define number of testcases and maximum number of cashiers
            b. Setup customer parameters: amount of items, payment methods
            c. Initialize and generate testcase matrix
            d. Initialize ratio and customers served array
  */

  int numberOfCustomers = 0, maxNumberOfCashiers = 0;
  cout << left << setw(25) << "Number of customers: ";
  cin >> numberOfCustomers;
  cout << setw(25) << "Number of cashiers: ";
  cin >> maxNumberOfCashiers;
  tcGenerator gen(numberOfCustomers, 2);
  double ratio_array[maxNumberOfCashiers];
  int customers_served_array[maxNumberOfCashiers];

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
  for (int numberOfCashiers = 1; numberOfCashiers <= maxNumberOfCashiers; ++numberOfCashiers) {
    long long customers_served = simulate(numberOfCashiers, numberOfCustomers, gen);
    cout << left << fixed << setw(25) << "Number of cashiers:";
    cout << setw(10) << numberOfCashiers;
    cout << setw(33) << "Number of served customers:";
    cout << setw(10) << customers_served;
    cout << setw(12) << "Ratio:";
    cout << setw(11) << (double)numberOfCashiers/(double)customers_served << "\n";
    customers_served_array[numberOfCashiers]=customers_served;
    ratio_array[numberOfCashiers]=(double)numberOfCashiers/(double)customers_served;
  }
  /*
    Step 3:
            Goal: Find the best number of cashiers according to maximum of customer served
            a. iterate the array
            b. store the maximum and mininium index
            c. print the best and the Worst
  */
  int max_index=1,min_index=1;
  for (int numberOfCashiers = 1; numberOfCashiers <= maxNumberOfCashiers; ++numberOfCashiers) {
    if(customers_served_array[numberOfCashiers]>customers_served_array[max_index]) {
      max_index=numberOfCashiers;
    }
    if(customers_served_array[numberOfCashiers]<customers_served_array[min_index]) {
      min_index=numberOfCashiers;
    }
  }
  cout<<"\n";
  cout << left << fixed << setw(30) <<"Best number of cashier:";
  cout << setw(10) <<max_index;
  cout << setw(33) << "Number of served customers:";
  cout << setw(10) << customers_served_array[max_index];
  cout << setw(12) <<"Ratio:";
  cout << setw(11) <<ratio_array[max_index]<<"\n";
  cout << left << fixed << setw(30) <<"Worst number of cashier:";
  cout << setw(10) <<min_index;
  cout << setw(33) << "Number of served customers:";
  cout << setw(10) << customers_served_array[min_index];
  cout << setw(12) <<"Ratio:";
  cout << setw(11) << ratio_array[min_index]<<"\n";
  return 0;
}
