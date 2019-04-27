# Problem statement

Everyday experiences at grocery stores tells us that one of the biggest deciding factor for customers retainment is the time it takes to purchase items; although the variety of item selection is important too, people generally go to the nearest and most convenient grocery store anyway, hence minimizing the time customers take to checkout is important. For this project, we aim to optimize the number of cashiers at a grocery store in order to maximize the profit of the grocery store.

# Problem setting

The simulator is based on the assumption that customers would uniformly appear at the grocery store. This means that customers would appear at the grocery store at random times throughout the day, but this "randomness" follows the normal distribution (which we believe would make the simulator most realistic). Customers would then line-up at each cashier to checkout (pay for their goods). However, there is a catch: if a customer waits more than 15 minutes in queue, the customer will then leave without buying anything. Obviously, the grocery store would want to minimize the number of customers leaving, and they can do so by increasing the number of cashiers. Yet there's another catch: increasing the amount of cashiers also increases cost, which the grocery store has to deduct from their revenue. So, here we have a problem: how do we find the best way so that the grocery store could maximize their overall profit (cost of cashiers - revenue from customers)?

A big problem is to determine a way to measure the "best way"; what is a best way? We decided that in order to find the optimal solution, the grocery store must be able to acommodate as many customers in as little time possible. This is because if customers leave after waiting too long, then the price they will pay for the goods is a "lost", which would otherwise be a revenue. If the grocery store can minimize the total time spent on acommodating customers, their corresponding revenue will increase as less customers would leave. Therefore, our program will find the optimal solution by minimizing time customers spent at the cashiers (by changing the number of cashiers).

The problem also requires the simulation to be as realistic as possible. We noticed that from everyday experience, nothing is certain; some customers might spend longer at the cashier than others. So, to account for this stochastic nature of life, the simulation must include some factors that is random. For example, for two customers buying the same items, the first customer might spend a certain amount of time more than the other customer, just like in real life. Of course, this randomness will follow the normal distribution, as there is a lot of statistics that shown that most things in life follow the normal distribution.

Last but not least, our simulation will emulate a grocery store as closely as possible. It takes into account most things a customer would find at a cashier when the program tries to find the optimal solution. The key factors we observed are the payment methods (paying with octopus card and/or cash is often quicker than paying with credit card), the number of cashiers, number of people, and amount of groceries.

# Program features

### Generate at least 50 random customers to find the optimal solution
1. We will program a "test-case generator" to generate test cases and simulate them in another program to find the optimal solution
2. Ideally, we use "mt19937" to generate random numbers for our simulation (the range of random numbers from rand() is dependent on the host's machine and realistically, if this project is to be implemented in real-life it should give the same result on any machines, regardless of the host.

### Output "simulation" files that holds critical information used to find the optimal solution
1. the files include information such as the types of grocery, prices, stocks, payment methods, number of customers,      and the number of cashiers.

### Function that serves to calculate the processing time each customer would spent at the cashier
1. Function should take into account the types of items, amount of items, and payment method.
2. Real life has a lot of uncertainties; a customer might take more time than others for a variety of reason. Hence, we decided to include a factor that randomly increases time. This random factor would follow the normal distribution as real life events tend to follow the normal distribution as well.
3. As there will be a lot of test cases and a lot of factors that would affect the time each customers take, using matrices to represent both the data and calculation would allow for clean implementation. Hence, we will implement a matrix data structure as well.

### Function to sort customers into cashiers
1. We begin by sorting customers one-by-one to evenly distribute them into each queue. This is realistic as customers would most likely queue at the current shortest queue, hence customers would evenly distribute themselves into each queue.
2. "class" is used to implement the queue for each cashier as each cashier has its own queue. "class" allows each cashier to handle their own queue and improve modularity.
3. The data structure "queue" is used to distribute customers. The first-in-first-out (F.I.F.O) nature of the data structure "queue" proves to be well-suited for this task.

### Find optimal solution with min / max solutions:
Given our problem, there are two possible methods of coming up with an optimal solution (optimal number of cashiers). We label them METHOD 1 and METHOD 2 respectively. METHOD 1 is used when the user can provide the program with the average spending of each customer and the cost of each cashier. Otherwise, METHOD 2 is used.

METHOD 1:
- We have enough data to find an optimal solution that is tailored towards the user.
- If "average customer spending" * "number of served customers" < "cost of each cashier" * "number of cashiers", then this "number of cashiers" and any larger number of cashiers is "not optimal".

METHOD 2:
- We do not have enough data to find an optimal solution that is tailored towards the user. So, we must base our decision on statistics alone.
- If "number of customers served with (n) cashiers" - "number of customers served with (n - 1) cashiers" < "minimum number of customers served" * 0.5, then "n" cashiers and any larger number of cashiers is "not optimal".

### How to use the simulator
1. First `git clone` the repository and use `make cashier` to generate the executable cashier program
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
1. **FIRST TESTCASE**

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

2. **SECOND TESTCASE**

Number of customers:     `1000`

Number of cashiers:      `25`

Do you know the average spending of each customer and cost of each cashier? (YES / NO): `YES`

Average spending of customers:     `200`

Cost of each cashier:              `500`

********************* The following is the results of each simulation *********************

Number of cashiers:      1         Number of served customers:      321       
Number of cashiers:      2         Number of served customers:      678       
Number of cashiers:      3         Number of served customers:      952       
Number of cashiers:      4         Number of served customers:      988       
Number of cashiers:      5         Number of served customers:      988       
Number of cashiers:      6         Number of served customers:      988       
Number of cashiers:      7         Number of served customers:      988       
Number of cashiers:      8         Number of served customers:      988       
Number of cashiers:      9         Number of served customers:      988       
Number of cashiers:      10        Number of served customers:      988       
Number of cashiers:      11        Number of served customers:      988       
Number of cashiers:      12        Number of served customers:      988       
Number of cashiers:      13        Number of served customers:      988       
Number of cashiers:      14        Number of served customers:      988       
Number of cashiers:      15        Number of served customers:      988       
Number of cashiers:      16        Number of served customers:      988       
Number of cashiers:      17        Number of served customers:      988       
Number of cashiers:      18        Number of served customers:      988       
Number of cashiers:      19        Number of served customers:      988       
Number of cashiers:      20        Number of served customers:      988       
Number of cashiers:      21        Number of served customers:      988       
Number of cashiers:      22        Number of served customers:      988       
Number of cashiers:      23        Number of served customers:      988       
Number of cashiers:      24        Number of served customers:      988       
Number of cashiers:      25        Number of served customers:      988       

The recommended number of cashiers: 4

3.**THIRD TESTCASE**

Number of customers:     `10`

Number of cashiers:      `10`

Do you know the average spending of each customer and cost of each cashier? (YES / NO): `YES`

Average spending of customers:     `1000`

Cost of each cashier:              `10`

********************* The following is the results of each simulation *********************

Number of cashiers:      1         Number of served customers:      10        
Number of cashiers:      2         Number of served customers:      10        
Number of cashiers:      3         Number of served customers:      10        
Number of cashiers:      4         Number of served customers:      10        
Number of cashiers:      5         Number of served customers:      10        
Number of cashiers:      6         Number of served customers:      10        
Number of cashiers:      7         Number of served customers:      10        
Number of cashiers:      8         Number of served customers:      10        
Number of cashiers:      9         Number of served customers:      10        
Number of cashiers:      10        Number of served customers:      10        

The recommended number of cashiers: 1

4. **FORTH TESTCASE**

Number of customers:     `10000`

Number of cashiers:      `15`

Do you know the average spending of each customer and cost of each cashier? (YES / NO): `NO`

********************* The following is the results of each simulation *********************

Number of cashiers:      1         Number of served customers:      333       
Number of cashiers:      2         Number of served customers:      692       
Number of cashiers:      3         Number of served customers:      1020      
Number of cashiers:      4         Number of served customers:      1359      
Number of cashiers:      5         Number of served customers:      1725      
Number of cashiers:      6         Number of served customers:      2032      
Number of cashiers:      7         Number of served customers:      2320      
Number of cashiers:      8         Number of served customers:      2647      
Number of cashiers:      9         Number of served customers:      3010      
Number of cashiers:      10        Number of served customers:      3333      
Number of cashiers:      11        Number of served customers:      3715      
Number of cashiers:      12        Number of served customers:      4059      
Number of cashiers:      13        Number of served customers:      4395      
Number of cashiers:      14        Number of served customers:      4739      
Number of cashiers:      15        Number of served customers:      5044      

The recommended number of cashiers: 15
