### Deleting a Node from a Binary Search Tree (BST)

Deleting a node from a BST requires careful handling to maintain the tree's properties. Here are the main cases to consider:

#### 1. **Node is a Leaf Node (No Children)**

- **Operation**: Simply remove the node.
- **Example**:
  ```plaintext
    30
   /  \
  20   40
 / \
10  25
  ```
  Deleting node 10 (a leaf node):
  ```plaintext
    30
   /  \
  20   40
   \
   25
  ```

#### 2. **Node has One Child**

- **Operation**: Replace the node with its single child.
- **Example**:
  ```plaintext
    30
   /  \
  20   40
      / 
     35
  ```
  Deleting node 40 (has one child 35):
  ```plaintext
    30
   /  \
  20   35
  ```

#### 3. **Node has Two Children**

- **Operation**: Replace the node with its in-order successor (or predecessor), then delete the successor (or predecessor) from its original position.

**Steps to Find and Replace with In-Order Successor**:
1. **Find the In-Order Successor**:
   - The in-order successor is the node with the smallest value in the right subtree of the node to be deleted.

2. **Replace the Node**:
   - Replace the node to be deleted with its in-order successor.

3. **Delete the Successor**:
   - The in-order successor will have at most one child (right child if any), which is then deleted.

**Steps to Find and Replace with In-Order Predecessor**:
1. **Find the In-Order Predecessor**:
   - The in-order predecessor is the node with the largest value in the left subtree of the node to be deleted.

2. **Replace the Node**:
   - Replace the node to be deleted with its in-order predecessor.

3. **Delete the Predecessor**:
   - The in-order predecessor will be a leaf or have at most one child (left child if any), which is then deleted.

**Example of Deleting a Node with Two Children**:

Consider this BST:
```plaintext
   30
  /  \
 20   40
 / \   \
10  25  50
```
Deleting node 20:
1. **Find In-Order Successor**:
   - The in-order successor of 20 is 25 (the smallest value in 20's right subtree).

2. **Replace Node 20 with 25**:
   ```plaintext
   30
  /  \
 25   40
 /     \
10     50
   ```

3. **Delete Node 25**:
   - Node 25 is now a leaf node and can be simply removed.

**Final Tree**:
```plaintext
   30
  /  \
 25   40
 /     \
10     50
```

### Time Complexity of Deletion

The time complexity for deletion in a BST depends on the tree's balance.

#### 1. **Worst Case Time Complexity**

**Scenario**: The BST is unbalanced (degenerated into a linked list).

- **Time to Find the Node**: \( O(n) \)
  - Finding a node involves traversing the entire height of the tree, which is \( n \) in the worst case.

- **Time to Find In-Order Predecessor/Successor**: \( O(n) \)
  - Finding the in-order predecessor or successor can also take \( O(n) \) time.

- **Total Time Complexity**: \( O(n) \)
  - Summing the time for finding the node and the in-order predecessor/successor gives a worst-case time complexity of \( O(n) \).

#### 2. **Average Case Time Complexity**

**Scenario**: The BST is balanced or nearly balanced (e.g., AVL trees, Red-Black trees).

- **Time to Find the Node**: \( O(\log n) \)
  - In a balanced BST, the height is \( \log_2(n) \), so finding a node takes \( O(\log n) \) time.

- **Time to Find In-Order Predecessor/Successor**: \( O(\log n) \)
  - The in-order predecessor or successor can be found in \( O(\log n) \) time due to the height constraint.

- **Total Time Complexity**: \( O(\log n) \)
  - Both finding the node and the in-order predecessor/successor are \( O(\log n) \), leading to a total time complexity of \( O(\log n) \).

### Summary

- **Worst Case**: \( O(n) \)
  - **Finding the Node**: \( O(n) \)
  - **Finding In-Order Predecessor/Successor**: \( O(n) \)
  - **Total**: \( O(n) \)

- **Average Case**: \( O(\log n) \)
  - **Finding the Node**: \( O(\log n) \)
  - **Finding In-Order Predecessor/Successor**: \( O(\log n) \)
  - **Total**: \( O(\log n) \)

Maintaining a balanced BST structure is essential to ensure optimal \( O(\log n) \) time complexity for operations.