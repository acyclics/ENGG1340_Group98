# Problem statement

Everyday experiences at grocery stores tells us that one of the biggest deciding factor for customers retainment is the time it takes to purchase items; although the variety of item selection is important too, people generally go to the nearest and most convenient grocery store anyway, hence minimizing the time customers take to checkout is important. For this project, we aim to optimize the checkout time for customers at a grocery store in order to maximize the revenue generated for any grocery stores that uses the optimized model.

# Problem setting

This program simulate a grocery store and, with the help of a mathematical model, figure out the best way to allocate all customers at the grocery store's checkout while maximizing profit. However, there is a catch: if a customer waits more than 15 minutes in queue, the customer will then leave without buying anything. Obviously, the grocery store would want to minimize the number of customers leaving, and they can do so by increasing the number of cashiers. Yet there's another catch: increasing the amount of cashiers also increases cost, which the grocery store has to deduct from their revenue. So, here we have a problem: how do we find the best way so that the grocery store could maximize their overall profit (cost of cashiers - revenue from customers)?

A big problem is to determine a way to measure the "best way"; what is a best way? We decided that in order to find the optimal solution, the grocery store must be able to acommodate as many customers in as little time possible. This is because if customers leave after waiting too long, then the price they will pay for the goods is a "lost", which would otherwise be a revenue. If the grocery store can minimize the total time spent on acommodating customers, their corresponding revenue will increase as less customers would leave. Therefore, our program will find the optimal solution by minimizing time customers spent at cashier (perhaps by changing the number of cashiers, method of payments, etc).

The problem also requires the simulation to be as realistic as possible. We noticed that from everyday experience, nothing is certain; some customers might spend longer at the cashier than others. So, to account for this stochastic nature of life, the simulation must include some factors that is random. For example, for two customers buying the same items, the first customer might spend a certain amount of time more than the other customer, just like in real life. Of course, this randomness will follow the normal distribution, as there is a lot of statistics that shown that most things in life follow the normal distribution.

Last but not least, our simulation will emulate a grocery store as closely as possible. It takes into account most things a customer would find at a cashier when the program tries to find the optimal solution. The key factors we observed are the payment methods (paying with octopus card and/or cash is often quicker than paying with credit card), the number of cashiers, number of people, amount of groceries, and perhaps some other factors that the simulation will take into account should we see fit.

# Program features

### Read from "simulation" files that holds critical information needed to find the optimal solution
1. the files should include information such as the types of grocery, prices, stocks, payment methods, number of customers,      and the number of cashiers.

### Generate at least 50 random customers to find the optimal solution
1. We will program a "test-case generator" to generate test cases and simulate them in another program to find the optimal solution
2. Ideally, we use "mt19937" to generate random numbers for our simulation (the range of random numbers from rand() is dependent on the host's machine and realistically, if this project is to be implemented in real-life it should give the same result on any machines, regardless of the host.

### Function that serves to calculate the processing time each customer would spent at the cashier
1. Function should take into account the types of items, amount of items, and payment method.
2. Real life has a lot of uncertainties; a customer might take more time than others for a variety of reason. Hence, we decided to include a factor that randomly increases time. This random factor would follow the normal distribution as real life events tend to follow the normal distribution as well.
3. As there will be a lot of test cases and a lot of factors that would affect the time each customers take, using matrices to represent both the data and calculation would allow for clean implementation. Hence, we will implement a matrix data structure as well.

### Algorithm to sort customers into cashiers
1. Mod, ceil, floor functions from STL can be used to evenly distribute customers into each queue. We could also just sort customers one-by-one to evenly distribute them into each queue. This is realistic as customers would most likely queue at the current shortest queue, hence customers would evenly distribute themselves into each queue. Of course, we could add a feature that randomly place a small number of customers in random queues to better approximate a real-life scenario where customers don't evenly distribute themselves (perhaps lining up with friends, as a group, etc)
2. Take edge cases into account

### Express line for grocery amount under 5 grocery items
1. In a lot of grocery stores, there is an express line for customers with little groceries. To make our simulation as realistic as possible, the simulation would also optimize the amount of express lines in order to maximize the grocery store's revenue.

### Find optimal solution with optimization algorithm(s)
1. Nelder-mead is an optimization algorithm that takes parameters as inputs, calculate the output using those parameters (in this case the total time spent for each customer / total revenue of grocery store), and adjust the parameters to find the maximum output. Implementing this optimization algorithm with the simulator would provide us the solution to the problem statement.
2. Dynamic programming can be used to keep track of past test cases. After each simulation, we can keep the test case that maximizes the revenue of the grocery store. After all test cases are ran, the test case that remains theoretically contains the parameters that would maximize the revenue of the grocery store.

### How to use the simulator
1. first `git clone` the repository and use `make cashier` to generate the executable cashier program
2. Open the executable `cashier` file.
3. The program requires for 3 compulsory inputs and 2 optional inputs.

  | Input Information  | Size of the input |
  | --- | --- |
  | Number of customers| 0  - 2147483647   |
  | Number of cashiers | 0  - 2147483647   |
  | Do you know the average spending of each customer and cost of each cashier | YES / NO |
  | Average spending of customers | 0  - 2147483647 |
  | Cost of each cashier | 0  - 2147483647 |
  
4. The program outputs all the number of served customers with respect to different number of cashiers
5. The program outputs the best number of cashier according to the user's inputs

### Sample testcase
1. *FIRST TESTCASE*

Number of customers:     `100`

Number of cashiers:      `5`

Do you know the average spending of each customer and cost of each cashier? (YES / NO):            ` NO`

********************* The following is the results of each simulation *********************

Number of cashiers:      1         Number of served customers:      99        
Number of cashiers:      2         Number of served customers:      99        
Number of cashiers:      3         Number of served customers:      99        
Number of cashiers:      4         Number of served customers:      99        
Number of cashiers:      5         Number of served customers:      99        

The recommended number of cashiers: 1

2. *SECOND TESTCASE*

Number of customers:     `1000`

Number of cashiers:      `25`

Do you know the average spending of each customer and cost of each cashier? (YES / NO):             `YES`

Average spending of customers: `200`

Cost of each cashier:    `500`

********************* The following is the results of each simulation *********************

Number of cashiers:      1         Number of served customers:      336       
Number of cashiers:      2         Number of served customers:      663       
Number of cashiers:      3         Number of served customers:      958       
Number of cashiers:      4         Number of served customers:      990       
Number of cashiers:      5         Number of served customers:      991       
Number of cashiers:      6         Number of served customers:      991       
Number of cashiers:      7         Number of served customers:      991       
Number of cashiers:      8         Number of served customers:      991       
Number of cashiers:      9         Number of served customers:      991       
Number of cashiers:      10        Number of served customers:      991       
Number of cashiers:      11        Number of served customers:      991       
Number of cashiers:      12        Number of served customers:      991       
Number of cashiers:      13        Number of served customers:      991       
Number of cashiers:      14        Number of served customers:      991       
Number of cashiers:      15        Number of served customers:      991       
Number of cashiers:      16        Number of served customers:      991       
Number of cashiers:      17        Number of served customers:      991       
Number of cashiers:      18        Number of served customers:      991       
Number of cashiers:      19        Number of served customers:      991       
Number of cashiers:      20        Number of served customers:      991       
Number of cashiers:      21        Number of served customers:      991       
Number of cashiers:      22        Number of served customers:      991       
Number of cashiers:      23        Number of served customers:      991       
Number of cashiers:      24        Number of served customers:      991       
Number of cashiers:      25        Number of served customers:      991       

The recommended number of cashiers: 25
