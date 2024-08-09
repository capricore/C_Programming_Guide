### Time Complexity of a Sorted Array

#### Insert One Item
- **Time Complexity:**  O(n) 
- **Explanation:** Inserting an item into a sorted array requires finding the correct position for the new item and then shifting all the subsequent elements to make space for the new item. This shifting operation takes linear time in the worst case.

#### Find an Item
- **Time Complexity:**  O(log n) 
- **Explanation:** Finding an item in a sorted array can be done efficiently using binary search, which has a logarithmic time complexity.

### Time Complexity of a Sorted Linked List

#### Insert One Item
- **Time Complexity:**  O(n) 
- **Explanation:** Inserting an item into a sorted linked list requires traversing the list to find the correct insertion point, which takes linear time. Once the insertion point is found, the insertion itself is  O(1) .

#### Find an Item
- **Time Complexity:**  O(n) 
- **Explanation:** Finding an item in a sorted linked list requires a linear traversal of the list, as linked lists do not support efficient random access like arrays do.

### Summary

- **Sorted Array:**
  - Insert one item:  O(n) 
  - Find an item:  O(log n) 
- **Sorted Linked List:**
  - Insert one item:  O(n) 
  - Find an item:  O(n) 


### Sorted or unsorted?
### Unsorted Array with Linear Search

- **Insertion Time Complexity**:  O(n) 
- **Lookup Time Complexity**:  O(n)  per lookup
- **Total Time Complexity for m Lookups**:  O(m * n) 

### Sorted Array with Binary Search

- **Insertion Time Complexity**:  O(n^2)  (due to the need to maintain order)
- **Lookup Time Complexity**:  O(log n)  per lookup
- **Total Time Complexity for m Lookups**:  O(m * log n) 

### Efficiency Comparison

- **For Insertion**:
  - **Unsorted Array**:  O(n)  for each insertion, so  n  insertions take  O(n^2)  in total.
  - **Sorted Array**:  O(n^2)  for each insertion due to maintaining order.

  If you are primarily concerned with insertion, an unsorted array is more efficient because its insertion time complexity is linear relative to the number of elements, while a sorted array involves more complex operations.

- **For Lookup**:
  - **Unsorted Array**: Each lookup takes  O(n) , so  m  lookups take  O(m * n) .
  - **Sorted Array**: Each lookup takes  O(log n) , so  m  lookups take  O(m * log n) .

  If you are primarily concerned with lookup performance, a sorted array is more efficient because binary search has logarithmic time complexity, which is significantly faster than linear search for large  n .

### Overall Efficiency

- **For Frequent Lookups**: The sorted array with binary search is generally more efficient for lookups, especially when  m  is large relative to  n . The total complexity for lookups  O(m * log n)  is usually much better than  O(m * n)  of an unsorted array.

- **For Frequent Insertions**: The unsorted array is more efficient if the number of insertions is high, as its insertion complexity is lower than that of a sorted array.

**Summary**:
- **If you need to perform many lookups and fewer insertions**, the sorted array with binary search is typically more efficient.
- **If you need to perform many insertions and fewer lookups**, the unsorted array is usually more efficient.

### Singly Linked List

- **Description:** Each node contains data and a pointer to the next node.
- **Structure:**
  ```plaintext
  [data | next] -> [data | next] -> [data | next] -> NULL


### Doubly Linked List

- **Description:** Each node contains data, a pointer to the next node, and a pointer to the previous node.
- **Structure:**
  ```plaintext
  NULL <- [prev | data | next] <-> [prev | data | next] <-> [prev | data | next] -> NULL

### Abstract Data Structures

#### Stack
- **Description:** A stack is a data structure that follows the Last In, First Out (LIFO) principle.
- **Operations:**
  - **Push:** Add an item to the top of the stack.
  - **Pop:** Remove and return the item from the top of the stack.
  - **Peek/Top:** Return the item at the top of the stack without removing it.
- **Example Use Cases:** undo mechanisms in applications.

#### Queue
- **Description:** A queue is a data structure that follows the First In, First Out (FIFO) principle.
- **Operations:**
  - **Enqueue:** Add an item to the end of the queue.
  - **Dequeue:** Remove and return the item from the front of the queue.
  - **Front/Peek:** Return the item at the front of the queue without removing it.
- **Example Use Cases:** Task scheduling

#### Dictionary
- **Description:** A dictionary (or map) is a data structure that stores key-value pairs and allows access to items by key.
- **Operations:**
  - **Insert:** Add a key-value pair to the dictionary.
  - **Search:** Retrieve the value associated with a given key.
  - **Delete:** Remove a key-value pair from the dictionary.
  - **Update:** Modify the value associated with a given key.
- **Example Use Cases:** Symbol tables, caching

### Dictionary Operations
- **Search for an Arbitrary Key**
  - **Description:** Find an item by its key in the dictionary.

- **Insert Item**
  - **Description:** Add a new key-value pair to the dictionary.

- **Delete Item**
  - **Description:** Remove a key-value pair from the dictionary using the key.

- **Return the Maximum (or Minimum) Key**
  - **Description:** Retrieve the key with the highest (or lowest) value in the dictionary.

- **Return the (Previous / Next) Key**
  - **Description:** Retrieve the in-order predecessor or successor key, which is the previous or next key in sorted order.