# Data Structures: Arrays

## 1. What is a Data Structure?

A data structure is a particular way of organizing and storing data in a computer so that it can be accessed and modified efficiently. Data structures are essential for managing large amounts of data and for implementing algorithms effectively.

### 1.1 Abstract Data Type (ADT)

An Abstract Data Type (ADT) is a model for data structures that defines a set of operations on the data, but does not specify the implementation of these operations. ADTs provide a logical description of data and the operations that can be performed on them without specifying how these operations will be carried out.

Examples of ADTs include:
- List
- Stack
- Queue
- Tree
- Graph

### Characteristics of an ADT
- **Collection of data items:** The data that the ADT operates on.
- **Family of operations:** The set of operations that can be performed on the data.

Think of an ADT as a set of promises or contracts. The ADT defines what operations are possible, but not how these operations are implemented. This separation allows for more flexible and maintainable code.

### Implementation of an ADT
While the ADT defines the operations, we must still implement these promises. The implementation of an ADT includes defining the actual data structure and writing the code for the operations.

Good programming practice supports the separation of the ADT's definition from its implementation:
- **Encapsulation:** The implementation details of the ADT are hidden from the rest of the program. Nothing outside of the definitions of the ADT should refer to anything inside, except through function calls for the basic operations.
- **Modularity:** The implementation can be changed without affecting the rest of the program, as long as the interface remains consistent.

### Example of ADT: Stack
A stack ADT might include operations such as `push`, `pop`, `peek`, and `isEmpty`. Here is a simple example in C:

**Stack ADT Interface:**
```c
typedef struct Stack Stack;

Stack* createStack(int capacity);
void push(Stack* stack, int item);
int pop(Stack* stack);
int peek(Stack* stack);
int isEmpty(Stack* stack);
```


### 1.2 Concrete Data Structure

A concrete data structure is a specific way of storing and organizing data to implement the operations defined by an abstract data type. Concrete data structures provide the actual implementation details, which include memory layout, pointer usage, and algorithms for performing the operations.

## 2. Random Access Memory (RAM)

Random Access Memory (RAM) is a type of computer memory that can be accessed randomly. Any byte of memory can be accessed without touching the preceding bytes, making it fast and efficient for storing and retrieving data.

Key characteristics of RAM:
- Volatile memory: Data is lost when the power is turned off.
- Fast access times: Allows quick read and write operations.
- Direct access: Each memory cell can be accessed directly via its address. Each byte in RAM has a unique address, starting from 0 up to the maximum size of the RAM (e.g., a system with 4GB of RAM has addresses ranging from 0x00000000 to 0xFFFFFFFF).

## 3. Pointers

Pointers are variables that store the memory address of another variable. They are a powerful feature in programming languages like C and C++ because they allow direct access and manipulation of memory.

Key concepts:
- **Pointer declaration:** `int *ptr;` declares a pointer to an integer.
- **Dereferencing:** `*ptr` accesses the value at the memory address stored in the pointer.
- **Pointer arithmetic:** Allows traversal of arrays and other data structures.

## 4. Arrays

An array is a collection of elements, all of the same type, stored in contiguous memory locations. Arrays provide a simple and efficient way to store and access a fixed-size sequence of elements.

### 4.1 Arrays in Memory

In memory, arrays are stored as a contiguous block of elements. The address of the first element (base address) and the size of each element are used to calculate the address of any element in the array.

Example:
```c
int arr[5] = {1, 2, 3, 4, 5};
```

### 4.2 Arrays: Complexity Analysis

The time and space complexity of arrays are important for understanding their efficiency:

- **Access (indexing):** O(1) - Direct access via the index.
- **Search:**
  - Unsorted: O(n) - Linear search.
  - Sorted: O(log n) - Binary search (requires sorted array).
