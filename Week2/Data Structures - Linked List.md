### Arrays

#### Advantages:
- **Compact:** Items are stored in contiguous memory locations.
- **Convenient Access:** Allows direct access to any item, e.g., `x = A[4];`.
- **O(1) Access:** Provides constant time access to any item.

#### Disadvantages:
- **Homogeneous Items:** All items need to be of the same type.
- **Fixed Size:** Arrays are static structures with a fixed size.
  - **Workaround:** Use `realloc()` to allocate more space when needed.

### Linked Lists

- **Description:** 
  - Each item is located in an arbitrary place in memory.
  - Each item contains a link (pointer) to the next item.

#### Advantages:
- **Flexibility:** Items can be easily inserted or removed as the list grows and shrinks dynamically.

#### Disadvantages:
- **Memory Overhead:** Requires extra memory to store pointers for each item.
- **Time Overhead:** Takes additional time to allocate space for each new item.

### Arrays vs. Linked Lists

#### Space Requirement
- **Array:**
  - **Time Complexity:**  O(n) 
  - **Explanation:** An array requires a contiguous block of memory of size proportional to the number of elements  n .

- **Linked List:**
  - **Time Complexity:**  O(n) 
  - **Explanation:** A linked list requires space for both the data and pointers (or references). While it uses more space per element compared to an array, the space complexity is still  O(n)  because the extra space is a constant factor.

#### Time Complexity to Build an Unsorted Data Structure
- **Array:**
  - **Time Complexity:**  O(n) 
  - **Explanation:** Building an array by adding  n  elements requires  O(n)  time.

- **Linked List:**
  - **Time Complexity:**  O(n) 
  - **Explanation:** Building a linked list by adding  n  elements also requires  O(n)  time. Although there are more steps per insertion compared to an array, this results in a constant factor, so the time complexity remains  O(n) .

#### Time Complexity to Find One Item in an Unsorted Data Structure
- **Array:**
  - **Time Complexity:**  O(n) 
  - **Explanation:** Finding an item in an unsorted array requires a linear search, which takes  O(n)  time.

- **Linked List:**
  - **Time Complexity:**  O(n) 
  - **Explanation:** Finding an item in an unsorted linked list also requires a linear search, which takes  O(n)  time.
