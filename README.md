# Problem statement

Everyday experiences at grocery stores tells us that one of the biggest deciding factor for customers retainment is the time it takes to purchase items; although the variety of item selection is important too, people generally go to the nearest and most convenient grocery store anyway, hence minimizing the time customers take to checkout is important. For this project, we aim to optimize the number of cashiers at a grocery store in order to maximize the profit of the grocery store.

# Problem setting

The simulator is based on the assumption that customers would uniformly appear at the grocery store. This means that customers would appear at the grocery store at random times throughout the day, but this "randomness" follows the normal distribution (which we believe would make the simulator most realistic). Customers would then line-up at each cashier to checkout (pay for their goods). However, there is a catch: if a customer waits for more than 15 minutes in queue, the customer will then leave without buying anything. Obviously, the grocery store would want to minimize the number of customers leaving, and they can do so by increasing the number of cashiers. Yet there's another catch: increasing the amount of cashiers also increases cost, which the grocery store has to deduct from their revenue. So, here we have a problem: how do we find the best way so that the grocery store could maximize their overall profit (cost of cashiers minus revenue from customers)?

A big problem is to determine a way to measure the "best way"; what is a best way? We decided that in order to find the optimal solution, the grocery store must be able to acommodate as many customers in as little time possible. This is because if customers leave after waiting too long, then the price they will pay for the goods is a "lost", which would otherwise be a revenue. If the grocery store can minimize the total time spent on acommodating customers, their corresponding revenue will increase as less customers would leave. Therefore, our program will find the optimal solution by minimizing time customers spent at the cashiers (by changing the number of cashiers).

The problem also requires the simulation to be as realistic as possible. We noticed that from everyday experience, nothing is certain; some customers might spend longer at the cashier than others. So, to account for this stochastic nature of life, the simulation must include some factors that is random. For example, for two customers buying the same items, the first customer might spend a certain amount of time more than the other customer, just like in real life. Of course, this randomness will follow the normal distribution, as there is a lot of statistics that shown that most things in life tend to follow the normal distribution.

Last but not least, our simulation will emulate a grocery store as closely as possible. It takes into account most things a customer would find at a cashier when the program tries to find the optimal solution. The key factors we observed are the payment methods (paying with octopus card and/or cash is often quicker than paying with credit card), the number of cashiers, number of people, and amount of groceries.

# Program features

### Generate N number of customers to find the optimal solution. N is user-defined
1. We will program a "test-case generator" to generate test cases and simulate them in another program to find the optimal solution

2. Ideally, we use "mt19937" to generate random numbers for our simulation (the range of random numbers from rand() is dependent on the host's machine and realistically, if this project is to be implemented in real-life it should give the same result on any machines, regardless of the host.

3. More details can be found in "main.cpp"

### Output "Simulation" files that holds critical information used to find the optimal solution
1. We want the results to be reproducible. Because the data are randomly generated, a record for each generation. Therefore, the randomly generated numbers used for the simulation will be outputted to a file. This filename has the format 

   "Simulation-Y-m-d-H-M-S"
   
   where Y = Year, m = Month, d = Day, H = Hour, M = Minute, S = Second. By using generation time as part of filename, we
   ensure that each generated data for simulation are recorded.
   
2. There are randomly generated data for each customer. So, each line in the "Simulation" file follows the following format:

   Customer #  :   A       B 
   
   where # = no. of customer, A = randomly generated number 1, B = randomly generated number 2. Details for these randomly 
   generated number are within "main.cpp". Note that there are a total of N lines in the "Simulation" file because there are N 
   customers (where N is user-defined) and each customer has randomly generated data.

### Function that serves to calculate the processing time each customer would spent at the cashier
1. Function should take into account the amount of items and payment method. The combination of the two will be used to calculate the total amount of time a customer needs to spend at the cashier.

2. Real life has a lot of uncertainties; a customer might take more time than others for a variety of reason. Hence, we decided to include a factor that randomly increases time. This random factor would follow the normal distribution as real life events tend to follow the normal distribution as well.

3. As there will be a lot of test cases and a lot of factors that would affect the time each customers take, using matrices to represent both the data and calculation would allow for clean implementation. Hence, we implemented a matrix data structure as well.

### Matrix implementation
1. The class "matrix" is used both for storing data of customers as well as to calculate time each customers need.

2. Matrix multiplication achieves this:

- Consider customer i. Customer i has "x" groceries and payment method "y". For each grocery, time needed to pay for it is 5 seconds. Also, let the time needed to use payment method "y" be 10 times "y". Then, the total amount of time a customer needs to checkout = 5x + 10y.
- The problem is that we have N number of customers, what is an efficient way to do all these computations? The answer is of course, with matrices.
- Let A = "customers", where each row is a customer and each column be "x" and 'y". So, A is a N by 2 matrix. Also, let B = "time constants" where "5 seconds" is row 1 and "10 seconds" is row 2. So, B is a 2 by 1 matrix.
- AB is a matrix multiplication and it gives us a N by 1 matrix, a.k.a vector, where entry "i" stores the total amount of time customer "i" needs to checkout at a cashier.

This is what we have achieved with our matrix implementation which allows us to efficiently compute the time each customer requires during checkout at the cashier. More details can be found in "testcase_generator.cpp" as well as "simulator.cpp".

### Function to sort customers into cashiers
1. We begin by sorting customers one-by-one to evenly distribute them into each queue. This is realistic as customers would most likely queue at the current shortest queue, hence customers would evenly distribute themselves into each queue.

2. "class" is used to implement the queue for each cashier as each cashier has its own queue. "class" allows each cashier to handle their own queue and improve modularity.

3. The data structure "queue" is used to distribute customers. The first-in-first-out (F.I.F.O) nature of the data structure "queue" proves to be well-suited for this task.

4. Each item of the queue is the struct "Customer". This allows us to keep everything well-contained.

### Find the optimal solution:
As the results of the simulation are stored in an array, we will iterate through the array to find the optimal solution. Given our problem, there are two possible methods of coming up with an optimal solution (optimal number of cashiers). We label them METHOD 1 and METHOD 2 respectively. METHOD 1 is used when the user can provide the program with the average spending of each customer and the cost of each cashier. Otherwise, METHOD 2 is used.

METHOD 1:
- We have enough data to find an optimal solution that is tailored towards the user.
- We first iterate through 1 to N number of cashiers (where N is user-defined) and compare the "number of served customers". If "average customer spending" * "number of served customers" < "cost of each cashier" * "number of cashiers", then this "number of cashiers" and any larger number of cashiers is "not optimal". So, once we encountered this condition, we should stop the program and return the optimal solution. This is because of two reasons:

1. If the cost of cashiers is greater than total generated revenue ("average customer spending" * "number of served customers"), then there is no point in adding more cashiers.

2. One can argue that instead of stopping the program, it should continue to search because there might be an even better solution if we let the program to continue searching. For example, in the sequence 1 -> 2 -> 5 -> 3 -> 2 -> 10, "5" might seem like an optimal solution but "10" is the true optimal solution. Thankfully, this argument is invalid as the condition we imposed is sufficient to find the optimal solution. Put simply, the total number of customers serve actually converges, so the previous terms in the sequence will always be smaller than future terms. For example, one sequence that fits the description would be 1 -> 2 -> 3 -> 4 -> 5 -> 10.

Generally, METHOD 1 is preferable to METHOD 2 as the program has extra data to make the calculations.

METHOD 2:
- We do not have enough data to find an optimal solution that is tailored towards the user. So, we must base our decision on statistics alone.
- We first iterate through 1 to N number of cashiers (where N is user-defined) and compare the "number of served customers". If "number of customers served with (n) cashiers" - "number of customers served with (n - 1) cashiers" < "minimum number of customers served" * 0.5, then "n" cashiers and any larger number of cashiers is "not optimal". The reasonings for this is similar to METHOD 1, but instead of comparing price of cashiers and customers spending, we compare the "increments" adding new cashiers give. For example,

   1 cashier = 5 customers
   
   2 cashiers = 10 customers
   
   3 cashiers = 14 customers
   
   4 cashiers = 15 customers
   
   5 cashiers = 15 customers

At first, 1 cashier gives us 5 customers that successfully checked-out. 2 cashiers give us 10, that is a +5 customers due to +1 cashier. 3 cashiers give us +4 customers due to +1 cashier (from 2 cashiers to 3 cashiers). 4 cashiers give us +1 customers due to +1 cashier (from 3 cashiers to 4 cashiers). 5 cashiers give us +0 customers due to +1 cashier. Using METHOD 2, our program will find the point where the increase in customers are insignificant (such as +0 customer) and that point will be the optimal solution (in this case, it will be 4 cashiers).

Defining "significance" is tricky. One can argue that the +1 customers from 3 cashiers to 4 cashiers is not worth the +1 cashier. So, our program solves this by comparing the incremental size with the minimum number of customers that checked-out. The reasoning is simple: if the total customers served (checked-out successfully) is 2 and the incremental size is +1, then obviously the +1 is significant! So, for METHOD 2, our program will define "significance" by comparing the incremental size to the minimum number of customers served and use this definition of "significance" to find the point where the increment size becomes insigificant (which is the optimal solution).

Note that in the above case, +1 is treated as significant because minimum number of customers served is only 5 customers. So, the optimal solution METHOD 2 will find for this is 4 cashiers. METHOD 2 will not consider 5 cashiers as +0 is insignificant. Also, it would not consider 5 cashiers because there is no change from 4 cashiers to 5 cashiers (and paying for extra cashiers without an increase in customers is definitely a loss in profit).

More details can be found in the file "main.cpp".

### How to use the simulator
1. First `git clone` the repository and use `make cashier` to generate the executable cashier program
2. Execute the program "cashier" with command `./cashier`.
3. The program requires for 3 compulsory inputs and 2 optional inputs.

  | Input Information  | Size of the input |
  | --- | --- |
  | Number of customers| 0  - 2147483647   |
  | Number of cashiers | 0  - 2147483647   |
  | Do you know the average spending of each customer and cost of each cashier | YES / NO |
  | Average spending of customers | 0  - 2147483647 |
  | Cost of each cashier | 0  - 2147483647 |
  
4. The program outputs all the number of served customers with respect to different number of cashiers.
5. Finally, the program outputs the optimal number of cashier using either METHOD 1 or METHOD 2.

We have also provided extra functionality in the Makefile to benefit the user. As each run of the program (simulation) will generate a file that contains data relevant to that simulation, users, if they so choose, can remove all generated files with the command `make rmsimu`. Also, `make rmprog` can be used to remove the generated executable file "cashier" when `make cashier` was called.

### Sample simulations

**----------FIRST SIMULATION----------**

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

**----------SECOND SIMULATION----------**

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

**----------THIRD SIMULATION----------**

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

**----------FORTH SIMULATION----------**

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

### Ending notes
Our simulation program follows very strict programming structures and a very mathematical approach to problem solving. We believe that to best simulate real-life events, probability and statistics are crucial, hence everything we implemented are rooted in probabilities and statistics. Some linear algebra is also employed to handle the sheer amount of data the user can request the program to generate.
