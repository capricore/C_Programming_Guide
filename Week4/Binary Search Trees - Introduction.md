### Complete Binary Trees

A **Complete Binary Tree** is a type of binary tree with the following properties:

1. **Every level, except possibly the last, is completely filled**:
   - This means that all nodes at every level are maximized. For instance, level 0 has 1 node, level 1 has 2 nodes, level 2 has 4 nodes, and so forth.

2. **All nodes are as far left as possible**:
   - On the last level, nodes are filled from left to right without gaps, ensuring the tree remains compact.

### Characteristics of a Complete Binary Tree

- **Levels are Fully Filled**:
  - For a tree with height `h`, all levels up to `h-1` are fully populated with `2^i` nodes at level `i`.

- **Nodes at the Last Level**:
  - If the last level is not completely filled, the nodes are packed as far left as possible.

### Example

**Complete Binary Tree Example**:
```
       1
     /   \
    2     3
   / \   / 
  4   5 6   
```
   - Level 0: 1 node (1)
   - Level 1: 2 nodes (2, 3)
   - Level 2: 3 nodes (4, 5, 6)
   - The last level nodes (4, 5, 6) are as far left as possible.

**Non-Complete Binary Tree Example**:
```
       1
     /   \
    2     3
   / \     \
  4   5     6   
```
   - Level 0: 1 node (1)
   - Level 1: 2 nodes (2, 3)
   - Level 2: 3 nodes (4, 5, 6)
   - The last level nodes (4, 5, 6) are not packed as far left as possible (node 6 is not leftmost).

### Properties of a Complete Binary Tree
The height of a complete binary tree with `n` nodes can be calculated, but it's important to note the exact definition of a complete binary tree and how the height is determined:

### Height of a Complete Binary Tree

1. **Definition of Height**:
   - The height of a tree is defined as the length of the longest path from the root to a leaf node.
   - In a tree with a height `h`, the number of levels is `h + 1`, where level 0 is the root level.

2. **Complete Binary Tree**:
   - A complete binary tree is a type of binary tree where all levels, except possibly the last, are completely filled, and all nodes are as far left as possible.

### Calculation of Height

For a complete binary tree:
- **Minimum Nodes at Height `h`**: \(2^h\)
- **Maximum Nodes at Height `h`**: \(2^{h+1} - 1\)

Given `n` nodes in a complete binary tree:

- **Height `h`** can be calculated as:
  h = $\lfloor \log_2(n) \rfloor$

  This formula comes from the fact that the number of nodes in a complete binary tree of height `h` can range from \(2^h\) (the minimum number of nodes) to \(2^{h+1} - 1\) (the maximum number of nodes).

### Example

If you have a complete binary tree with `n = 7` nodes:

- **Height Calculation**:
  h = $\lfloor \log_2(7) \rfloor$ = $\lfloor 2.807 \rfloor$ = 2

- **Tree Structure**:
  The tree will look like:
  ```
       1
     /   \
    2     3
   / \   / \
  4   5 6   7
  ```

  This tree has a height of `2` (with levels `0`, `1`, and `2`).

### Summary

- The height of a complete binary tree with `n` nodes is given by \(\lfloor \log_2(n) \rfloor\).
- This formula helps determine the maximum height based on the number of nodes and is useful for understanding the structure and properties of complete binary trees.
### Use Cases

- **Heap Data Structures**:
  - Binary Heaps (Min-Heaps and Max-Heaps) are often implemented as complete binary trees for efficient operations.

- **Array Representation**:
  - Complete binary trees can be efficiently represented in arrays due to their compact structure.

### Conclusion

A complete binary tree maintains a compact and balanced structure with every level fully filled except possibly the last, and nodes on the last level positioned as far left as possible. This property makes them efficient and suitable for various applications requiring balanced and compact data structures.

### Finding the Smallest and Largest Items in a Binary Search Tree (BST)

In a **Binary Search Tree (BST)**, finding the smallest and largest items is straightforward due to the inherent properties of BSTs:

### Finding the Smallest Item

In a BST, the smallest item is always the leftmost node. By definition:
- The left child of a node contains a value less than the node’s value.
- By continually moving to the left child, you eventually reach the node with the smallest value.

**Algorithm to Find the Smallest Item:**
1. Start at the root node.
2. Continuously move to the left child until you reach a node that has no left child.
3. The node you end up at is the smallest node in the BST.

**Example Code (C):**
```c
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
```

### Finding the Largest Item

In a BST, the largest item is always the rightmost node. By definition:
- The right child of a node contains a value greater than the node’s value.
- By continually moving to the right child, you eventually reach the node with the largest value.

**Algorithm to Find the Largest Item:**
1. Start at the root node.
2. Continuously move to the right child until you reach a node that has no right child.
3. The node you end up at is the largest node in the BST.

**Example Code (C):**
```c
struct Node* findMax(struct Node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}
```

### Example Usage

For a BST like:
```
        15
       /  \
      10   20
     / \    \
    5  12   25
```
- **Smallest Item**:
  - Starting at 15, move to the left to 10.
  - Move further left to 5.
  - Node 5 has no left child, so it is the smallest item.

- **Largest Item**:
  - Starting at 15, move to the right to 20.
  - Move further right to 25.
  - Node 25 has no right child, so it is the largest item.

### Summary

- **Smallest Item**: Move left from the root until you reach a node with no left child.
- **Largest Item**: Move right from the root until you reach a node with no right child.

These operations are efficient with a time complexity of O(h), where h is the height of the tree.

### Time Complexity of Binary Search Trees (BSTs)

The time complexity of operations in a BST depends on the tree’s structure:

#### Best Case: Balanced Tree
- **Height of Tree**: For balanced BSTs (e.g., AVL Trees, Red-Black Trees), the height is approximately log_2(n), where n is the number of nodes.
- **Operations**: Search, insertion, and deletion all have a time complexity of O(log n) in the best case.
  
**Explanation**: 
- A balanced tree maintains a logarithmic height, which ensures efficient operations due to its compact and balanced nature.

#### Worst Case: Degenerate Tree (Linked List)
- **Height of Tree**: In the worst case, where the BST degenerates into a linked list, the height is n, the number of nodes.
- **Operations**: Search, insertion, and deletion all have a time complexity of O(n) in the worst case.
  
**Explanation**: 
- When nodes are inserted in sorted order, each new node becomes a right child of the previous node, resulting in a linear height similar to a linked list.

### Summary

- **Balanced Tree**: Height log_2(n)
  - **Operations**: O(log n) for search, insertion, and deletion.
  - **Path Length**: Longest and average paths are both log_2(n).

- **Degenerate Tree**: Height n
  - **Operations**: O(n) for search, insertion, and deletion.
  - **Path Length**: Longest path is n, average path is approximately \frac{n}{2}.

### Traversal in Data Structures

Traversal involves visiting each node in a data structure exactly once and performing some operation. The method of traversal depends on the data structure:

### 1. **Traversal in Trees**

**Binary Trees** and **Binary Search Trees (BSTs)** use various traversal methods:

#### a. **In-Order Traversal**
- **Description**: Visit the left subtree, then the node, then the right subtree.
- **Properties**: For BSTs, produces nodes in non-decreasing order.
- **Algorithm**:
  ```c
  void inOrderTraversal(struct Node* root) {
      if (root != NULL) {
          inOrderTraversal(root->left);
          printf("%d ", root->key);
          inOrderTraversal(root->right);
      }
  }
  ```

#### b. **Pre-Order Traversal**
- **Description**: Visit the node, then the left subtree, then the right subtree.
- **Properties**: Useful for copying the tree or prefix notation.
- **Algorithm**:
  ```c
  void preOrderTraversal(struct Node* root) {
      if (root != NULL) {
          printf("%d ", root->key);
          preOrderTraversal(root->left);
          preOrderTraversal(root->right);
      }
  }
  ```

#### c. **Post-Order Traversal**
- **Description**: Visit the left subtree, then the right subtree, then the node.
- **Properties**: Useful for deleting or freeing nodes, or postfix notation.
- **Algorithm**:
  ```c
  void postOrderTraversal(struct Node* root) {
      if (root != NULL) {
          postOrderTraversal(root->left);
          postOrderTraversal(root->right);
          printf("%d ", root->key);
      }
  }
  ```

#### d. **Level-Order Traversal**
- **Description**: Visit nodes level by level from top to bottom and left to right.
- **Properties**: Requires a queue; useful for breadth-first operations.
- **Algorithm**:
  ```c
  void levelOrderTraversal(struct Node* root) {
      if (root == NULL) return;
      Queue* queue = createQueue();
      enqueue(queue, root);
      while (!isEmpty(queue)) {
          struct Node

* node = dequeue(queue);
          printf("%d ", node->key);
          if (node->left != NULL) enqueue(queue, node->left);
          if (node->right != NULL) enqueue(queue, node->right);
      }
  }
  ```

### 2. **Traversal in Graphs**

#### a. **Depth-First Search (DFS)**
- **Description**: Explore as far down a branch as possible before backtracking.

#### b. **Breadth-First Search (BFS)**
- **Description**: Explore all neighbors at the present depth level before moving on to nodes at the next depth level.

### 3. **Traversal in Lists**

#### a. **Singly Linked List**
- Traverse from the head node to the end by following each node's next pointer.

#### b. **Doubly Linked List**
- Traverse forward from the head node or backward from the tail node using previous and next pointers.

### Summary

Traversal techniques vary based on the data structure and the operation required. In trees, common methods include in-order, pre-order, post-order, and level-order traversals. In graphs, DFS and BFS are used, while linked lists are typically traversed linearly.
