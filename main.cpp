#include <iostream>
#include "testcase_generator.h"
int main() {
  using namespace std;
  //step 1: testcase generator
  //step 1A: set customer parameter: amount of item,random and influenced payment method
  //step 1B: initial and generate testcase matrix
  //step 2: similiator (start global timer)
  //step 2A:setup cashiers and distribute customers to different cashiers in a period of time
  //step 2B: once the first customer reach the cashiers, start the timer for that cashier.
  //step 2C: for each occupied cashiers, once reached 15min, flush queue.
  //step 2C: sum up the served customers for each cashiers
  //step 2E:continue the loop until global timer reached
  //step 3: caluculate ratio(n/c) and reiterate for the other n.
  
  //testcase debug below
  using namespace testcase;
  tcGenerator gen(5, 5);
  gen.editConstraints(0, 0.0, 100.0, "double");
  gen.editConstraints(1, 1000.0, 2000.0, "double");
  gen.editConstraints(2, 0, 100, "int");
  gen.editConstraints(3, 1, 2000, "int");
  gen.editConstraints(4, 0.0, 1.0, "double");
  gen.generate();
  gen.printMatrix();
  cout<<"DONE"<<endl;
  return 0;
}