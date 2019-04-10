#include "main.h"
#include "testcase_generator.h"
#include "testcase_generator.cpp"
#include <iostream>

void InitializeConstantMatrix()
{
  using namespace testcase;
  matrix ConstantMatrix;
  ConstantMatrix.valueAt(0, 0)=2;   // factor for ID0
  ConstantMatrix.valueAt(0, 1)=5;   // factor for ID1
  ConstantMatrix.valueAt(0, 2)=10;  // factor for ID2
  ConstantMatrix.valueAt(0, 3)=7;   // factor for ID3
  ConstantMatrix.valueAt(0, 4)=1;   // factor for ID4
  ConstantMatrix.valueAt(0, 4)=20;  // factor for ID5
}

int main()
{
  using namespace testcase;
  cin>>N;
  tcGenerator gen(N, 6);
  /*
  ID 0 - number of people in a group (at most 20)
  ID 1 - payment method
  (0 = CASH, 1 = Octopus Card, 2 = Credit Card paywave/ mobile payment, 3 = Credit Card with Signature )
  ID 2 - amount of items (0- infinity)
  ID 3 - types of item
  (0 = lightweight items ~ below 5kg in total 1 = moderate weight items 5-15kg in total 2 = heavy items > 20 kg in total )
  ID 4 - random factors(0-10)
  ID 5 - express line (0= false , 1= true)
  */
  gen.editConstraints(0, 0, 20, "int");
  gen.editConstraints(1, 0, 4, "int");
  gen.editConstraints(2, 0, 256, "int");
  gen.editConstraints(3, 0, 3, "int");
  gen.editConstraints(4, 0.0, 10.0, "double");
  gen.editConstraints(5, 0, 2, "int");
  gen.generate();
}
