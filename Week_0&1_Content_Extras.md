### 1. High-level Language vs Assembly Language vs Machine Language

- **High-level Language**: Closer to human language, easier to read and write (e.g., C, Python).
- **Assembly Language**: A low-level language that uses mnemonics to represent machine code instructions. e.g. "MOV AL, 61h  ;" Load 97 (hexadecimal 61) into the AL register
- **Machine Language**: The lowest level, consisting of binary code that the computer's CPU can execute directly. e.g. "10110000 01100001"

### 2. Compiled Language vs Interpreted Language

- **Compiled Language**: Needs to be translated into executable code by a compiler before it can be run (e.g., C).
- **Interpreted Language**: Executed directly by an interpreter, without needing to be compiled into machine code first (e.g., Python).
- **Efficiency**: Compiled languages are generally faster but less flexible in development; interpreted languages are slower but more flexible.
- **Portability**: Compiled languages are less portable; interpreted languages are more portable across different platforms.

### 3. Procedural vs Object-oriented

- **Procedural Language**: Focuses on procedures or routines (e.g., C). No support for classes or objects.
- **Object-oriented Language**: Focuses on objects and classes (e.g., Java, C++).

## Syntax

### 1. Data Types

#### Integer Types
  | Type(16bit OS) | Min Size | Min Range                               |
  |----------------|----------|-----------------------------------------|
  | int            | 16 bits  | -32,768 to 32,767 (±2^15)               |
  | unsigned int   | 16 bits  | 0 to 65,535 (2^16 - 1)                  |
  | long           | 32 bits  | -2,147,483,648 to 2,147,483,647 (±2^31) |
  | unsigned long  | 32 bits  | 0 to 4,294,967,295 (2^32 - 1)           |
  | char           | 8 bits   | -128 to 127 (±2^7)                      |
  | unsigned char  | 8 bits   | 0 to 255 (2^8 - 1)                      |

#### Floating-Point Types
  | Type           | Min Size | Min Range                 |
  |----------------|----------|---------------------------|
  | float          | 32 bits  | ±1.2E-38 to ±3.4E+38      |
  | double         | 64 bits  | ±2.3E-308 to ±1.7E+308    |
  | long double    | 64 bits  | ±2.3E-308 to ±1.7E+308    |

  **Note**: Floating-point arithmetic may have precision issues.

#### Pointer Types

#### Aggregate Types
- **Array**: A collection of elements of the same type.
- **Union**: A special data structure of different types of data in the same memory location.
- **Structure**: A collection of variables of different types grouped together.
**Note**: There is no Boolean type in C; 1 and 0 are used to represent true and false, respectively.

### 2. Variables, Declarations, and Statements

#### Declaring a Variable
```c
int a;
```

#### Declaring and Initializing a Variable
```c
int a = 10;
```

#### Difference Between Const Variable and Pre-defined Name
```c
const int MAX = 10;
#define MAX 10
```
- **Const Variable**: A true variable with a constant value.
- **Pre-defined Name**: Replaced by its value during the pre-processing phase.

### 3. Scope

#### Block Scope
- **Rule 1**: A variable outside a block can be accessed inside the block, but not vice versa.
- **Rule 2**: If there are multiple variables with the same name, the closest variable takes precedence.

#### File Scope
- A variable declared outside any block can be accessed throughout the file.

### 4. Operators

#### Arithmetic Operators
`+ - * / % ++ --`

#### Relational Operators
`== != > < >= <=`

#### Logical Operators
`&& || !`

#### Bitwise Operators
`& | ^ << >>`

#### Conditional Operator
`A ? B : C`

#### Assignment Operators
`=`

- **Compound Assignment**: `+= -= *= /= %=`

#### sizeof Operator
- Use `sizeof` to avoid magic numbers and ensure portability across platforms.

#### Operator Precedence
- Use parentheses `()` to clarify and control the order of operations.

### 5. Control Statements

#### if else

#### switch
- Don't forget `break` and `default`.

#### while (do while)
- `do while` executes at least once.

#### for

#### break and continue

#### goto
- Avoid using `goto` as it can lead to complex and hard-to-maintain code.

### 6. Arrays

#### Declaring an Array
```c
int arr[5];
```

#### Declaring and Initializing an Array
```c
int arr[5] = {1, 2, 3, 4, 5};
int arr[] = {1, 2, 3, 4, 5};
char str[] = {'H', 'e', 'l', 'l', 'o', '\0'};
char str[] = "Hello";
```

#### Accessing Array Elements
```c
int val = arr[index];
```

#### Multidimensional Arrays
```c
int multiArr[2][3] = {{1, 2, 3}, {4, 5, 6}};
int val = multiArr[0][1];
```

### 7. Functions

#### Defining a Function
```c
int add(int a, int b) {
    return a + b;
}
```

#### Calling a Function
```c
int result = add(1, 2);
```

#### Value Passing
- Functions in C use value passing, not reference passing.

#### Recursion
- A function can call itself.

```c
int fac(int x) {
    if (x == 1) {
        return 1;
    }
    return x * fac(x - 1);
}
```

### 8. Pointers

A pointer is a variable that stores the memory address of another variable. Pointers are a powerful feature of C, allowing for efficient memory management and dynamic data structures.

### Key Concepts of Pointers

1. **Definition**:
   - A pointer is defined using the `*` operator.
   - Example: `int *ptr;` declares `ptr` as a pointer to an integer.

2. **Initialization**:
   - Pointers must be initialized to a valid address before use, often using the address-of operator (`&`) to point to an existing variable.
   - Example:
     ```c
     int var = 10;
     int *ptr = &var;  // ptr now holds the address of var
     ```

3. **Dereferencing**:
   - Dereferencing a pointer means accessing the value at the memory address the pointer is pointing to. This is done using the `*` operator.
   - Example:
     ```c
     int value = *ptr;  // Retrieves the value stored at the address held by ptr
     ```

4. **Pointer Arithmetic**:
   - Pointers can be incremented or decremented, and arithmetic operations can be performed based on the size of the data type they point to.
   - Example:
     ```c
     int arr[3] = {1, 2, 3};
     int *ptr = arr;  // Points to the first element of arr
     ptr++;           // Now points to the second element of arr
     ```
     ```c
     long a = 0;
     long *p = &a;
     (p + 4) == (unsigned long)(p) + 4 * sizeof(long);  // true
     ```

5. **Dynamic Memory Allocation**:
   - Pointers are used with functions like `malloc`, `calloc`, and `free` to allocate and deallocate memory dynamically.
   - Example:
     ```c
     int *ptr = (int *)malloc(sizeof(int) * 10);  // Allocates memory for 10 integers
     free(ptr);  // Deallocates the memory
     ```

6. **Null Pointer**:
   - A pointer that does not point to any valid memory location is called a null pointer. It is often initialized to `NULL`.
   - Example:
     ```c
     int *ptr = NULL;  // ptr is a null pointer

7. **Pointer to Pointer**:
    - A pointer can point to another pointer.

    ```c
    int a = 0;
    int *p1 = &a;
    int **p2 = &p1;
    int ***p3 = &p2;
    ```

8. **Comparing Pointers**:
    - Pointers can be compared.

    ```c
    int arr[3] = {3, 2, 1};
    (arr < arr + 1);  // true
    ```

9. **Pointers and Arrays**:
    - Array names act as pointers to the first element of the array.

    ```c
    int arr[5] = {1, 2, 3, 4, 5};
    *arr == 1;  // true
    *(arr + 1) == 2;  // true
    ```

### 9. Memory Allocation

#### Dynamic Memory Allocation

##### malloc
- Allocate a block of memory of a specified size and returns a pointer to the beginning of this block.
```c
void *malloc(size_t size);
```
- size: The number of bytes to allocate.
- Returns: A pointer to the allocated memory block, or NULL if the allocation fails.
```c
int *pointer = (int *)malloc(40);
```

##### free
- Frees allocated memory.

```c
free(pointer);
```

##### realloc
- Used to change the size of an already allocated memory block. It can either increase or decrease the size. If the new size is larger, the additional memory is uninitialized. If it is smaller, the excess memory is freed.
```c
void *realloc(void *ptr, size_t new_size);
```
- ptr: A pointer to the previously allocated memory block. This pointer must have been allocated with malloc, calloc, or realloc itself.
- new_size: The new size of the memory block in bytes.
- Returns: A pointer to the newly allocated memory block, which may be at a different location. If the allocation fails, it returns NULL, and the original memory block remains unchanged.
```c
pointer = (int *)realloc(pointer, 20);
```

### 10. Structure and Union

In C and C++, both `union` and `struct` are used to group related variables together, but they have key differences in how they manage memory and access their members.

### Key Differences Between `union` and `struct`

1. **Memory Allocation**:
   - **`struct`**: Allocates enough memory to hold all of its members. Each member has its own memory location.
   - **`union`**: Allocates enough memory to hold only its largest member. All members share the same memory location, meaning only one member can be accessed at a time.

   **Example:**

   ```c
   // Structure example
   struct ExampleStruct {
       int i;
       float f;
       char str[20];
   };
   // Size = sizeof(int) + sizeof(float) + sizeof(char[20])

   // Union example
   union ExampleUnion {
       int i;
       float f;
       char str[20];
   };
   // Size = sizeof(char[20]) (largest member)
   ```

2. **Member Access**:
   - **`struct`**: All members can be accessed independently at the same time.
   - **`union`**: Only one member can be used at a time. Writing to one member affects the values of other members.

   **Example:**

   ```c
   struct ExampleStruct exampleStruct;
   exampleStruct.i = 10;
   exampleStruct.f = 3.14f;
   exampleStruct.str[0] = 'H'; // Accessing all members

   union ExampleUnion exampleUnion;
   exampleUnion.i = 10;
   exampleUnion.f = 3.14f; // Overwrites the integer value
   snprintf(exampleUnion.str, sizeof(exampleUnion.str), "Hello"); // Overwrites the float value
   ```

3. **Initialization**:
   - **`struct`**: You can initialize all members independently.
   - **`union`**: Only the first member or the member being accessed is initialized.

   **Example:**

   ```c
   // Struct initialization
   struct ExampleStruct exampleStruct = {10, 3.14f, "Hello"};

   // Union initialization
   union ExampleUnion exampleUnion = {10}; // Initializes the first member (i)
   ```

4. **Use Cases**:
   - **`struct`**: Ideal when you need to represent a record where each member has its own distinct value, and you need to access all members simultaneously.
   - **`union`**: Useful when you need to store different types of data but only one type at a time, and you want to save memory.

   **Example Use Case:**

   - **`struct`**: A `struct` might be used to represent a complex data type like a person with name, age, and height where each member is used independently.
   - **`union`**: A `union` might be used in a situation where you need to handle different data types in a flexible way, like interpreting different types of data from a network packet.

### Summary

- **Memory Allocation**:
  - `struct`: Total size is the sum of all members' sizes.
  - `union`: Total size is the size of the largest member.

- **Member Access**:
  - `struct`: All members can be accessed and modified independently.
  - `union`: Only one member can be accessed at a time; modifying one member affects the other members.

- **Initialization**:
  - `struct`: Can initialize all members at once.
  - `union`: Only the first member or the member being used is initialized.

Understanding these differences helps in choosing between `struct` and `union` based on the requirements of memory usage and data representation in your program.

### `fgets` and `scanf` in C

#### `fgets`

The `fgets` function is used to read a string from a file or standard input (`stdin`). It reads characters until a newline is encountered or until the specified number of characters have been read, whichever comes first.

**Syntax**:
```c
char *fgets(char *str, int n, FILE *stream);
```

- **Parameters**:
  - `str`: Pointer to a character array where the read string will be stored.
  - `n`: Maximum number of characters to read, including the null terminator.
  - `stream`: Input stream to read from (e.g., `stdin` for standard input).

- **Return Value**: A pointer to the string `str` on success, or `NULL` if an error occurs or end-of-file is reached.

**Example**:
```c
#include <stdio.h>

int main() {
    char buffer[100];
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("You entered: %s", buffer);
    } else {
        printf("Error reading input.");
    }
    return 0;
}
```

#### `scanf`

The `scanf` function is used to read formatted input from standard input (`stdin`). It processes the input based on the provided format specifiers and stores the results in the corresponding variables.

**Syntax**:
```c
int scanf(const char *format, ...);
```

- **Parameters**:
  - `format`: A format string containing format specifiers that dictate the type of data to read.
  - `...`: Additional arguments, each pointing to the location where the read data should be stored.

- **Return Value**: The number of items successfully read and assigned, or `EOF` if an input failure occurs.

**Example**:
```c
#include <stdio.h>

int main() {
    int number;
    char character;
    printf("Enter a number and a character: ");
    if (scanf("%d %c", &number, &character) == 2) {
        printf("You entered: %d and %c\n", number, character);
    } else {
        printf("Error reading input.");
    }
    return 0;
}
```

## Differences Between `fgets` and `scanf`

1. **Reading Method**:
   - `fgets`: Reads a line of text until a newline character or the specified limit is reached. It reads the entire line as a string, including spaces.
   - `scanf`: Reads formatted input based on format specifiers. It stops reading at whitespace unless instructed otherwise by the format string.

2. **Buffer Handling**:
   - `fgets`: Requires a buffer to store the read string and ensures null-termination.
   - `scanf`: Stores the read data directly into the variables provided as arguments.

3. **Input Safety**:
   - `fgets`: Safer for reading strings as it prevents buffer overflow by limiting the number of characters read.
   - `scanf`: More prone to buffer overflow if not used carefully, especially when reading strings without specifying the maximum width.

4. **Whitespace Handling**:
   - `fgets`: Includes newline characters and spaces in the read string.
   - `scanf`: Ignores leading whitespace and stops reading a string at the first whitespace character unless specified otherwise.

5. **Usage Scenarios**:
   - `fgets`: Preferred for reading entire lines of text or when input needs to be processed as a string.
   - `scanf`: Suitable for reading multiple types of data formatted in a specific way (e.g., integers, characters, floating-point numbers).

### Example Comparison

**Using `fgets` to Read a String**:
```c
#include <stdio.h>

int main() {
    char buffer[100];
    printf("Enter a string: ");
    fgets(buffer, sizeof(buffer), stdin);
    printf("You entered: %s", buffer);
    return 0;
}
```

**Using `scanf` to Read a String**:
```c
#include <stdio.h>

int main() {
    char buffer[100];
    printf("Enter a string: ");
    scanf("%99s", buffer); // %99s ensures no buffer overflow
    printf("You entered: %s", buffer);
    return 0;
}
```

In the `scanf` example, `%99s` ensures that at most 99 characters are read, preventing buffer overflow. However, `scanf` stops reading at the first whitespace, making it less suitable for input containing spaces compared to `fgets`.

---

## `scanf` Format Specifiers

`scanf` in C provides a wide range of format specifiers to read different types of input. Here are the main categories of format specifiers:

### Integer Formats

- `%d` : Reads a decimal integer.
- `%i` : Reads an integer (accepts decimal, hexadecimal, and octal).
- `%u` : Reads an unsigned decimal integer.
- `%o` : Reads an octal integer.
- `%x` or `%X` : Reads a hexadecimal integer.

### Floating-Point Formats

- `%f` : Reads a floating-point number (float).
- `%lf` : Reads a floating-point number (double).
- `%Lf` : Reads a floating-point number (long double).
- `%e`, `%E`, `%g`, `%G` : Reads a floating-point number (float, double, or long double) in scientific notation.

### Character Formats

- `%c` : Reads a single character.
- `%s` : Reads a string (stops at whitespace).
- `%[...]` : Reads a set of characters defined by the set inside the brackets (e.g., `%[^,]` reads until a comma).

### Pointer Formats

- `%p` : Reads a pointer (address in hexadecimal).

### Other Formats

- `%n` : Returns the number of characters read so far.
- `%%` : Reads a literal percent sign.

### Field Width

Each of these format specifiers can also be modified with a field width. For example, `%5d` reads at most 5 digits for an integer.

### Example of `%[^,]`

The `%[...]` format specifier allows you to specify a set of characters to include or exclude when reading a string. The `%[^,]` format specifier means "read a string until a comma is encountered".

Here is an example demonstrating the use of `%[^,]`:
```c
#include <stdio.h>

int main() {
    char str[100];
    printf("Enter a string (up to the first comma): ");
    scanf("%[^,]", str); // Reads until a comma is encountered
    printf("You entered: %s\n", str);
    return 0;
}
```

### Full List of Common `scanf` Format Specifiers

1. **Integer**:
   - `%d` : Decimal integer
   - `%i` : Integer (accepts decimal, hexadecimal, and octal)
   - `%u` : Unsigned decimal integer
   - `%o` : Octal integer
   - `%x`, `%X` : Hexadecimal integer

2. **Floating-Point**:
   - `%f` : Floating-point number (float)
   - `%lf` : Floating-point number (double)
   - `%Lf` : Floating-point number (long double)
   - `%e`, `%E`, `%g`, `%G` : Floating-point number (scientific notation)

3. **Character and String**:
   - `%c` : Single character
   - `%s` : String (stops at whitespace)
   - `%[...]` : Scanset (e.g., `%[^,]` to read until a comma)

4. **Pointer**:
   - `%p` : Pointer (address in hexadecimal)

5. **Other**:
   - `%n` : Number of characters read so far
   - `%%` : Literal percent sign

6. **Field Width**:
   - `%5d` : Reads at most 5 digits for an integer
   - `%9s` : Reads at most 9 characters for a string

---

## Example Programs
1. **Input a String of Maximal 79 Characters**:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[80];  // Array to hold the input string. 80 to include space for null terminator.

    printf("Enter a string (max 79 characters): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // fgets reads up to sizeof(buffer) - 1 characters and adds a null terminator
        // Remove the trailing newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        printf("You entered: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
```

2. **Function to Reverse a String**:

```c
#include <stdio.h>
#include <string.h>

// Function to reverse a string
void reverseString(char *str) {
    int len = strlen(str);  // Get the length of the string
    char temp;
    int start = 0;
    int end = len - 1;
    
    // Swap characters from start and end moving towards the center
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    char str[80];  // Array to hold the input string

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        // Remove the trailing newline character if present
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        reverseString(str);  // Call the function to reverse the string
        printf("Reversed string: %s\n", str);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
```

3. **Function to Extract Alphabetic Characters**:

```c
#include <stdio.h>
#include <ctype.h>

// Function to check if a character is alphabetic
int isAlphabetic(char c) {
    // Check if the character is between 'A' and 'Z' or 'a' and 'z'
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Function to filter alphabetic characters from the input string
void filterAlphabetic(const char *input, char *output) {
    while (*input) {  // While not at the end of the string
        if (isAlphabetic(*input)) {  // Check if the character is alphabetic
            *output = *input;  // Copy the alphabetic character
            output++;  // Move to the next position in the output string
        }
        input++;  // Move to the next character in the input string
    }
    *output = '\0';  // Null-terminate the output string
}

int main() {
    char input[80];
    char output[80];  // Array to hold the filtered string

    printf("Enter a string (max 79 characters): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove the trailing newline character if present
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Call the function to filter alphabetic characters
        filterAlphabetic(input, output);

        // Print the filtered string
        printf("Filtered string: %s\n", output);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
```

4. **Detect and Print Anagrams**:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRS 1000
#define MAX_STR_LEN 99

#define NUM_LETTERS 26
#define NUM_DIGITS 10
#define SIZE (NUM_LETTERS + NUM_DIGITS)

int read_strings(char ss[][MAX_STR_LEN + 1]);
int is_anagram(char *s1, char *s2);

int main(int argc, char *argv[]) {
	char ss[MAX_STRS][MAX_STR_LEN + 1];
	int n;   // number of strings
	int printed[MAX_STRS] = {0}; // =1 if string was printed in a stored
	int i, j, set = 0; 
	n = read_strings(ss);
	for (i = 0; i < n - 1; i++) {
		if (printed[i]) continue;  // skips if string was printed before
		int found = 0;              // flag for printing ss[i]  
		for (j = i + 1; j < n; j++) {
			if (is_anagram(ss[i], ss[j])) {
				if (!found) {   // if first anagram of ss[i] found
					printf("#set %d:\n", ++set);
					printf("%s\n", ss[i]);
					printed[i] = 1;  // marks ss[i] as printed
					found = 1;
				}
				printf("%s\n", ss[j]);
				printed[j] = 1;    // marks ss[j] as printed
			}
		}
	}
	return 0;
}

int read_strings(char ss[][MAX_STR_LEN + 1]) {
	int n = 0;
	printf("Enter strings (max=%d characters each):\n", MAX_STR_LEN);
	while ( fgets(ss[n], MAX_STR_LEN, stdin) ) {
		if ( ss[n][strlen(ss[n]) - 1] == '\n' ) {
			ss[n][strlen(ss[n]) - 1] = '\0';
		}
		n++;
	}
	// another version for the above loop, using scanf:
	// for ( ; n<MAX_STRS && scanf(" %[^\n]",ss[n])==1; n++);
	return n;
}

/* count frequencies of alphabetic characters in s, ignoring case
   frequencies will be stored in array freq[36],
   where freq[0] is frequency of 'A', freq[1] is frequency of 'B'...
         freq[26] is frequnecy of '0', freq[27] is frequency of '1',...
*/
void count_freq(char *s, int freq[]) {   
	int i; char *p;    
	for(i = 0; i < SIZE; i++) freq[i]= 0;
	for (p = s; *p; p++) {
		if (isalpha(*p)) {
			freq[ toupper(*p) - 'A' ]++;
			// if c is A,B,C, ..., Z , p-'A' is 0,1,2,...,25 
		} else if (isdigit(*p)){
			freq[ NUM_LETTERS + (*p - '0')]++;
			// if c is digit '0','1',...'9', p-'0' is integer 0,1,...9
		}
	}
}

/* 
  returns 1 if the two strings contain the same letters & digits, 
     possibly in a different order, and 0 otherwise, 
     ignoring whitespace characters, and ignoring case
  in addition, ignoring any non-alphanumeric characters,
*/
int is_anagram(char *s1, char *s2) {
	int f1[SIZE], f2[SIZE];   /* frequencies for s1 ans s2 */
	int i;
	int has_alnum = 0;
	count_freq(s1, f1);
	count_freq(s2, f2);
	for (i = 0; i < SIZE; i++) {
		if (f1[i] != f2[i]) return 0;
		if (f1[i]) has_alnum = 1;
	}
	// here, f1 and f2 are identical, and each array has at least one non-zero values
	//   --> the corresponding strings are anagram
	return has_alnum;
}
```

Here’s a consolidated and polished version of the code snippets for each problem:

### 5. Handling CSV File Input and Sorting Cities

```c
// A Touch Of Reality

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_N 1000
#define MAX_NAME_LEN 99
#define NOTFOUND (-1)

typedef struct city city_t;
struct city {
	char name[MAX_NAME_LEN + 1];
	int population;
	double percent;
};

int readCities(city_t A[]);
void printCities(city_t A[], int n); 
void insertionSort(city_t A[], int n);
int indexOfMax(city_t A[], int n);
int search(city_t A[], int n, char *givenCity); 
void printOvertaken(city_t cities[], int n); 

int main(int argc, char *argv[]) {
	assert (argc > 1);
	char *givenCity = argv[1];

	city_t cities[MAX_N];
	// 1. read & store cities
	int n = readCities(cities);

	// 2. sort arry by name & print
	insertionSort(cities, n);
	printf("LIST OF CITIES IN ALPHABETICAL ORDER\n");
	printCities(cities, n);
	printf("\n");

	// 3. find city with highest population
	int imax = indexOfMax(cities, n);
	printf("City with highest population: %s, population: %d\n",
			cities[imax].name, cities[imax].population);

	// 4. Find population of city givenCity
	int i = search(cities, n, givenCity);
	if (i != NOTFOUND) {
		printf("City: %s, Population: %d\n", 
		        cities[i].name, cities[i].population);
	} else {
		printf("City %s: NOTFOUND\n", givenCity);
	}

	// 5. print cities that givenCity overtakes in 2020  
	printOvertaken(cities, n);


	return EXIT_SUCCESS;
}

// read cities  
int readCities(city_t A[]) {
	int i;
	// skips the header line
	while( getchar() != '\n');

	// reads data 
	for (i = 0; i < MAX_N && scanf(" %[^,],%d,%lf%%", 
	            A[i].name, &A[i].population, &A[i].percent) == 3; i++);
	return i;
}

// prints data in CSV format
void printCities(city_t A[], int n) {
	int i;
	printf("City, Population June 2020, %% of national population June 2019\n");
	for (i = 0; i < n; i++) {
		printf("%s, %d, %.2lf%%\n", A[i].name, A[i].population, A[i].percent);
	}
}

// sorts array in ascending order of name
void insertionSort(city_t A[], int n) {
	int i, j;
	city_t x;
	for (i = 1; i < n; i++) {
		x = A[i];
		for (j = i - 1; j >= 0 && strcmp(x.name, A[j].name) < 0; j-- ) {
			A[j + 1] = A[j];
		}
		A[j + 1] = x;
	}
}

// returns the index of the city with highest population
int indexOfMax(city_t A[], int n) {
	int imax = 0;
	int i;
	for (i = 1; i < n; i++) {
		if (A[i].population > A[imax].population) imax = i;
	}
	return imax;
}


// returns index of the city with name givenCity, or NOTFOUND 
// using recursive binary search 
int binSearch(city_t A[], int left, int right, char *key) {
	if (left > right) 
		return NOTFOUND;
	int mid = (left + right)/2;
	if (strcmp(key, A[mid].name) < 0)
		return binSearch(A, left, right - 1, key);
	else if (strcmp(key, A[mid].name) > 0)
		return binSearch(A, left + 1, right, key);
	else
		return mid;
}


// returns index of the city with name givenCity, or NOTFOUND
//   by calling binSearch
int search(city_t A[], int n, char *givenCity) {
	return binSearch(A, 0, n - 1, givenCity);
}

// return 1 if x overtakes y in 2020 in population
int overtakes(city_t *x, city_t *y) {
	return (x->population > y->population && x->percent < y->percent);
}

 
// prints cities ovetaken by givenCity, 
//   and returns number of overtaken cities 
int findOvertaken(city_t cities[], int n, char *givenCity) { 
	int this = search(cities, n, givenCity);
	int i;
	int overtaken = 0;
	if (this != NOTFOUND) 
		for (i = 0; i < n; i++) {
			if (overtakes(cities + this, cities + i)) { 
				printf("%s overtakes %s in 2020 in population.\n", 
					givenCity, cities[i].name);
				overtaken++;
			}
		}
	return overtaken;
} 

// prints all the cities that overtake some other cities
void printOvertaken(city_t cities[], int n) {
	int winners = 0, losers = 0, i;
	printf("\nCITIES THAT OVERTAKE SOME OTHER IN 2020\n");
	for (i = 0; i < n; i++) {
		int tmp = findOvertaken(cities, n, cities[i].name);
		winners += (tmp > 0);
		losers += tmp;
	}
	printf("*** The list includes %d overtaking and %d overtaken cities\n", winners, losers);
}
```

### 6. Extracting Pairs of Characters

```c
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 1000
#define PAIR_SIZE 3  // 2 characters + 1 null terminator
#define MAX_PAIRS 500 // Maximum number of pairs for an input length of 1000

int main() {
    char input[MAX_INPUT_SIZE];
    char pairs[MAX_PAIRS][PAIR_SIZE];
    int numPairs = 0;

    // Read the input string
    printf("Enter the input string: ");
    scanf("%s", input);

    // Get the length of the input string
    int length = strlen(input);

    // Process the string two characters at a time
    for (int i = 0; i < length; i += 2) {
        if (i + 1 < length) {
            // Manually copy two characters into the pairs array
            pairs[numPairs][0] = input[i];
            pairs[numPairs][1] = input[i + 1];
            pairs[numPairs][2] = '\0'; // Null-terminate the string
            numPairs++;
        }
    }

    // Print the results
    printf("Extracted pairs:\n");
    for (int i = 0; i < numPairs; i++) {
        printf("[%s]\n", pairs[i]);
    }

    return 0;
}
```

### 7. Extracting Variable Length Strings

```c
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 1000
#define MAX_STRINGS 7
#define MAX_STRING_LENGTH 100

int main() {
    char input[MAX_INPUT_SIZE];
    char strings[MAX_STRINGS][MAX_STRING_LENGTH];
    int index = 0;
    int length;

    // Read the input string
    printf("Enter the input string: ");
    scanf("%s", input);

    // Get the length of the input string
    int inputLength = strlen(input);

    // Initialize the position to read from the input string
    int pos = 0;

    // Process the string
    while (pos < inputLength && index < MAX_STRINGS) {
        // Read the length of the next string
        length = input[pos] - '0'; // Convert character to integer
        pos++; // Move to the start of the actual string

        // Check if the length is within acceptable bounds
        if (length > 0 && length <= MAX_STRING_LENGTH - 1 && pos + length <= inputLength) {
            // Copy the string into the array
            strncpy(strings[index], &input[pos], length);
            strings[index][length] = '\0'; // Null-terminate the string
            index++;
            pos += length; // Move to the start of the next string length
        } else {
            // Handle any unexpected cases
            break;
        }
    }

    // Print the results
    printf("Extracted strings:\n");
    for (int i = 0; i < index; i++) {
        printf("[%s]\n", strings[i]);
    }

    return 0;
}
```

### 8. Modifying the Value of `x` in `main` Using Pointers

```c
#include <stdio.h>

/* Function prototype with a pointer to an integer */
void changeX(int *x);

int main(int argc, char **argv){
    int x = 5;
    printf("[main    before] x = %d\n", x);
    changeX(&x);  // Pass the address of x to the function
    printf("[main    after ] x = %d\n", x);
    return 0;
}

void changeX(int *x){
    printf("[changeX before] x = %d\n", *x);
    *x = 9;  // Dereference the pointer to change the value of x
    printf("[changeX after ] x = %d\n", *x);
}
```
### Explanation

1. **Function Call with Pass-by-Value**:
   - In C, function arguments are passed by value, meaning that a copy of the argument is made. Changes to this copy do not affect the original variable.

2. **Current Behavior**:
   - When you call `changeX(x)`, the `x` in `changeX` is a copy of the `x` in `main`. Changing `x` in `changeX` does not affect the `x` in `main`.

### Desired Behavior

If you want `changeX` to modify the value of `x` in `main`, you need to use pointers. By passing a pointer to `x`, `changeX` can modify the original `x` in `main`.

### 9. Finding Prime Numbers Using the Sieve of Eratosthenes
**Sieve of Eratosthenes** 

1. **Initialization**:
   - Create a boolean array `isPrime` of size \( n + 1 \). Initialize all entries to `true`, assuming all numbers are prime.
   - Set `isPrime[0]` and `isPrime[1]` to `false` since 0 and 1 are not prime numbers.

2. **Sieve Process**:
   - Start with the first prime number (2). For each number \( i \):
     - If `isPrime[i]` is `true`, then \( i \) is a prime number.
     - Mark all multiples of \( i \) (starting from \( i^2 \)) as `false`, indicating that they are not prime.
   - Continue this process up to \( \sqrt{n} \), because any composite number \( n \) will have at least one factor less than or equal to \( \sqrt{n} \).

3. **Extract Primes**:
   - Iterate through the `isPrime` array. The indices with `true` values represent prime numbers.

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int main() {
    bool isPrime[MAX + 1];
    int i, j;

    // Initialize all entries as true
    for (i = 0; i <= MAX; i++) {
        isPrime[i] = true;
    }

    // 0 and 1 are not prime numbers
    isPrime[0] = isPrime[1] = false;

    // Implementing the Sieve of Eratosthenes
    for (i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            // Mark multiples of i as not prime
            for (j = i * i; j <= MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Print all prime numbers
    printf("Prime numbers up to %d are:\n", MAX);
    for (i = 2; i <= MAX; i++) {
        if (isPrime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
```
