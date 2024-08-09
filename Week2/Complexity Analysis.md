### Why Study Efficiency?

**1. Understand How Problems Scale with Input:**
- **Growth Rates:** Know how algorithms perform as input sizes increase.
- **Predictability:** Anticipate performance changes with larger datasets.
- **Avoid Pitfalls:** Prevent inefficiencies with growing data.

**2. Choose Which Algorithm to Use for a Problem:**
- **Best Fit:** Select the most suitable algorithm based on complexity.
- **Optimization:** Pick the fastest or most resource-efficient algorithm.
- **Trade-offs:** Balance between time and space efficiency.

### Additional Benefits

- **Performance Optimization:** Enhance speed and resource utilization.
- **Scalability:** Ensure software handles growth efficiently.
- **Future-Proofing:** Design for long-term efficiency.

### Complexity Analysis

- **Express Complexity T(n) as a Function of the Input Size n:**
  - Analyze how the algorithm’s resource usage grows with the size of the input.

- **Complexity in Operations (Steps), Not Time:**
  - Focus on the number of operations performed, not the actual elapsed time.

- **Classify Algorithms into Groups Based on Their Growth Rate:**
  - Categorize algorithms by how their complexity increases as the input size grows.

- **Big O Notation: O(g(n)):**
  - Describes the upper bound of an algorithm's growth rate.
  - Represents the order of the function, indicating how the complexity scales.

- **Example:**
  - A problem that grows linearly with the input size is O(n).

### Big-O Definition

- **For Two Functions f(n) and g(n):**
  - We say f(n) is in O(g(n))  if:
    - There exist constants  c_0  and  N_0  such that
       f(n) < c_0 * g(n)  for all  n > N_0 .
  - We are interested in the behavior as  n  becomes very large.

- **Asymptotic Behavior:**
  - Focuses on what happens when  n  approaches infinity.

### Big-O Definition Examples

- **Example 1:**
  -  T(n) = 4n^2  is in  O(n^2) 
  -  4n^2 < c_0 * n^2  for all  n > N_0 
  - Example:  4n^2 < 5n^2  for all  n > 0 

- **Example 2:**
  -  T(n) = n^2 + 2n + 8  is in  O(n^2) 
  -  n^2 + 2n + 8 < c_0 * n^2  for all  n > N_0 
  - Example:  n^2 + 2n + 8 < 11n^2  for all  n > 1 
  
### Big-O Heuristics

- **Ignore Coefficients:**
  - Focus on the growth rate of the function rather than the constant factors.
  - Example:  3n^2 + 5n  is  O(n^2) , ignoring the coefficient 3.

- **Drop Lower-Order Terms:**
  - In Big-O notation, only the term with the highest growth rate matters.
  - Example:  n^2 + 2n + 8  is  O(n^2) , dropping the lower-order terms  2n  and 8.
  
- **Summary:**
  - When n is large, the most expensive (highest order) term dominates; we can ignore lower-order terms and constant

### Big-O Classes

- ** O(1)  - Constant Time:**
  - **Description:** Operation that does not depend on  n .
  - **Example:** Accessing an element in an array by index.

- ** O(log n)  - Logarithmic Time:**
  - **Description:** Time grows logarithmically with the input size.
  - **Example:** Binary search.

- ** O(n)  - Linear Time:**
  - **Description:** Time grows linearly with the input size.
  - **Example:** Looping through  n  items.

- ** O(nlogn)  - Linearithmic Time:**
  - **Description:** Time grows proportionally to  n  multiplied by the logarithm of  n .
  - **Example:** Efficient sorting algorithms like mergesort.

- ** O(n^2)  - Quadratic Time:**
  - **Description:** Time grows proportionally to the square of the input size.
  - **Example:** Pairwise comparisons, nested loops.

- ** O(2^n)  - Exponential Time:**
  - **Description:** Time grows exponentially with the input size.
  - **Example:** Generating all possible subsets.

- ** O(n!)  - Factorial Time:**
  - **Description:** Time grows factorially with the input size.
  - **Example:** Generating all possible permutations.


### Big-Omega (Ω) Notation

- **Definition**: Big-Omega (Ω) notation represents the **lower bound** of an algorithm's time or space complexity. It indicates the minimum amount of time or space an algorithm will require, regardless of input size.
- **Formal Definition**: A function  f(n)  is said to be in  Ω(g(n))  if there exist constants  c  and  N_0  such that for all  n > N_0 :
  f(n) > c * g(n)
- **Purpose**: Provides a guarantee that the function will not run faster than a certain rate.

### Big-Theta (Θ) Notation

- **Definition**: Big-Theta (Θ) notation represents a **tight bound** on the time or space complexity of an algorithm. It describes both the upper and lower bounds, giving an exact asymptotic behavior.
- **Formal Definition**: A function  f(n)  is said to be in  Θ(g(n))  if there exist constants  c_1 ,  c_2 , and  N_0  such that for all  n > N_0 :
  c_1 * g(n) < f(n) < c_2 * g(n)
- **Purpose**: Provides a precise characterization of the function's growth rate, indicating that  f(n)  grows at the same rate as  g(n) .

### Summary

- **Big-Omega (Ω)**: Describes the lower bound of the growth rate. It tells you that the function will not grow slower than  g(n) .
- **Big-Theta (Θ)**: Provides a tight bound, describing both the upper and lower bounds. It indicates that the function grows at the same rate as  g(n) .

### Complexity Analysis

- **Description**: Complexity analysis describes how the performance of an algorithm changes as the size of the input grows.

- **Asymptotic Behaviour**:
  - Focuses on the performance of an algorithm as the input size becomes very large.
  - Helps in understanding how the algorithm scales and what its long-term behavior will be.

- **Big-O Notation**:
  - **Purpose**: Classifies algorithms based on their complexity.
  - **Definition**: Provides an upper bound on the performance of an algorithm.
  - **Focus**: Usually describes the worst-case performance, which ensures that the algorithm performs within this bound in the most challenging scenarios.

