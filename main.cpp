#include <iostream>
#include <map>
#include <string>
#include "testcase_generator.h"
#include "main.h"
int main() {
  using namespace std;
  //step 1: testcase generator
  //step 1A: set customer parameter: amount of item,random and influenced payment method
  using namespace testcase;
  cin >> numberofcustomer;
  tcGenerator gen(numberofcustomer, 3);
  /*
  Matrix description
  ID:0 -- amount of goods
  ID:1 -- payment method: 0:Cash 1:octopus card 2:credit card 3:electronic payment
  ID:2 -- boolean for influenced payment 0:FALSE 1:TRUE
  */
  gen.editConstraints(0, 0, 100, "int");
  gen.editConstraints(1, 0, 3, "int");
  gen.editConstraints(2, 0, 1, "int");
  //step 1B: initial and generate testcase matrix
  gen.generate();
  //step 2: similiator (start global timer - main.h)
  //step 2A:setup cashiers and distribute customers to different cashiers in a period of time
  //iterate day with different number of cashiers
  for(int num_cashier(1); num_cashier<100; num_cashier++) {
    for(int i(1); i<num_cashier; i++){
      //setting up the cashier
      cashier working_cashier[i];
    }
  }

  //step 2B: once the first customer reach the cashiers, start the timer for that cashier.
  //step 2C: for each occupied cashiers, once reached 15min, flush queue.
  //step 2C: sum up the served customers for each cashiers
  //step 2E:continue the loop until global timer reached
  //step 3: caluculate ratio(n/c) and reiterate for the other n.

  //testcase debug below
  gen.printMatrix();
  cout << gen.getMatrixValue(0,0);
  cout << "DONE\n";
  return 0;
}
