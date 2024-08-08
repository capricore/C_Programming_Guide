1. E2.1
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SIZE 4

int main(int argc, char **argv){
	// Variables and initialization for dynamic array
	char **strings = NULL;
	int n = 0;
	int size = INIT_SIZE;
	// FILL IN: malloc the initial array
	strings = malloc(size * sizeof(*strings));
	assert(strings);
	
	// FILL IN at all the /* comments */ belows
	while(!feof(stdin)){
		// Variables for using getline
		char *line = NULL;
		size_t lineSize = 0;
		/* Read the line using getline, appropriately break if failed */
        ssize_t len = getline(&line, &lineSize, stdin);
        if (len == -1) {
            free(line); // Free the memory allocated by getline
            break;
        }
		/* Make sure that array "strings" has room for a new element */
        if (n >= size) {
            size *= 2;
            strings = realloc(strings, size * sizeof(*strings));
            assert(strings);
        }
		/* Store the line in array */
        strings[n] = line;
        n++;
	}
	
	/* Print the array in reverse order */
	for (int i = n - 1; i >= 0; i--) {
    printf("%s", strings[i]);
}
	/* Free the memory allocated to each strings[i], then free "strings" */
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);
        return 0;
    }
```

2. E2.2

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
    int i, j;
    int a[10][20];
    int *b[10];
    
    /* Write code here to use b in the below loops. */
    for (i = 0; i < 10; i++) {
        b[i] = malloc(20 * sizeof(int)); // Allocate space for 20 integers
        assert(b[i]); // Ensure memory allocation was successful
    }

    for(i = 0; i < 10; i++){
        for(j = 0; j < 20; j++){
            /* This fills a and b with the numbers 0 -> 199 */
            a[i][j] = i*20 + j;
            b[i][j] = i*20 + j;
        }
    }
    
    for(i = 0; i < 10; i++){
        for(j = 0; j < 20; j++){
            /* This only prints when i == j to give less output, no real significance. */
            if(i == j){
                printf("a[%d][%d] = %d, b[%d][%d] = %d\n",i,j,a[i][j],i,j,b[i][j]);
            }
        }
    }

    // Free allocated memory for each row of b
    for (i = 0; i < 10; i++) {
        free(b[i]);
    }

    return 0;
}

```


3. E2.3

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
    int i,j;
    int a[10][20];
    int *b[10];
    int **c;
    
    /* Take your code from E2.2 for b and put it here. */
    for (i = 0; i < 10; i++) {
        b[i] = malloc(20 * sizeof(int)); // Allocate space for 20 integers
        assert(b[i]); // Ensure memory allocation was successful
    }
    
    /* Write the code for initialising c and put it here. */

    // Allocate memory for the array of pointers (c)
    c = malloc(10 * sizeof(int*)); // Allocate space for 10 pointers to int
    assert(c); // Ensure memory allocation was successful
    
    // Allocate memory for each row that c points to
    for (i = 0; i < 10; i++) {
        c[i] = malloc(20 * sizeof(int)); // Allocate space for 20 integers
        assert(c[i]); // Ensure memory allocation was successful
    }
    
    for(i = 0; i < 10; i++){
        for(j = 0; j < 20; j++){
            /* This fills a and b with the numbers 0 -> 199 */
            a[i][j] = i*20 + j;
            b[i][j] = i*20 + j;
            c[i][j] = i*20 + j;
        }
    }
    
    for(i = 0; i < 10; i++){
        for(j = 0; j < 20; j++){
            /* Only prints when i == j to give less output, no real significance. */
            if(i == j){
                printf("a[%d][%d] = %d, b[%d][%d] = %d, c[%d][%d] = %d\n",i,j,a[i][j],i,j,b[i][j],i,j,c[i][j]);
            }
        }
    }
    
    return 0;
}

```

4. E2.11
```c

#include <stdio.h>
#include <stdlib.h>
#define PRIMECOUNT 1000

int main(int argc, char **argv){
    /* The primes 1 - 1000, if n is prime, 
        primes[n - 1] == 1 and 0 otherwise. */
    int primes[PRIMECOUNT];
    int i;
    
    for(i = 0; i < PRIMECOUNT; i++){
        primes[i] = 1;
    }
    
    /* Write a prime checking algorithm here. */
   
    // 0 and 1 are not primes
    primes[0] = 0;
    primes[1] = 0;
    
    // Sieve of Eratosthenes algorithm
    for (i = 2; i * i <= PRIMECOUNT; i++) {
        if (primes[i - 1] == 1) { // If i is a prime
            for (j = i * i; j <= PRIMECOUNT; j += i) {
                primes[j - 1] = 0; // Mark multiples of i as non-prime
            }
        }
    }
    
    /* -------------------------------------- */
    
    printf("All primes found from 1 - 1000:\n");
    for(i = 0; i < PRIMECOUNT; i++){
        if(primes[i]){
            printf("%d ",i + 1);
        }
    }
    printf("\n");
    
    return 0;
}

```