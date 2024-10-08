A binary tree is a hierarchical data structure where each node has at most two children, known as the left child and the right child. Here's a more detailed explanation:

### Structure of a Binary Tree

1. **Node**: The fundamental part of a binary tree. Each node contains:
   - A value or data.
   - A pointer/reference to the left child.
   - A pointer/reference to the right child.
```plaintext
      10
     /  \
    5    15
   / \   / \
  3   7 12  20
```
2. **Root**: The topmost node of the binary tree, serving as the starting point of the tree.

3. **Children**: Nodes that are connected to another node (parent node) in a tree structure.

4. **Leaf Nodes**: Nodes that do not have any children. They are the end nodes of the tree.

5. **Internal Nodes**: Nodes that have at least one child.

6. **Subtree**: Any node in a tree along with its descendants can be considered a subtree.

### Properties of Binary Trees

1. **Height of a Tree**: The length of the longest path from the root to a leaf. The height of a tree with a single node is 0.

2. **Depth of a Node**: The number of edges from the root to the node.

3. **Level of a Node**: The number of edges from the root to the node plus one.

### Types of Binary Trees

1. **Full Binary Tree**: A binary tree in which every node other than the leaves has exactly two children.
```plaintext
       1
      / \
     2   3
        / \
        4  5 
```
2. **Complete Binary Tree**: A binary tree in which all levels, except possibly the last, are fully filled, and all nodes are as far left as possible.
```plaintext
       1
      / \
     2   3
    / \ / \
   4  5 6
```
4. **Perfect Binary Tree**: A binary tree in which all internal nodes have exactly two children and all leaf nodes are at the same level.

5. **Balanced Binary Tree**: A binary tree where the height of the left and right subtrees of every node differ by at most one.

6. **Binary Search Tree (BST)**: A binary tree in which the left subtree of a node contains only nodes with values less than the node’s value, and the right subtree contains only nodes with values greater than the node’s value.

## Binary Search Trees (BSTs)

A Binary Search Tree (BST) is a type of binary tree where each node contains a comparable key (and an associated value) and satisfies the binary search property:

- **Binary Tree**: A tree where each node has at most two children.
- **Binary Search Property**: For every node n:
  - All keys in the left subtree are less than n.key.
  - All keys in the right subtree are greater than n.key.

Here is the BST example:
```plaintext
        50
       /  \
      30   70
     / \   / \
    20 40 60 80
```

### Operations on a BST

- **Insertion**: Adding a new node while maintaining the binary search property.
Insert 65:
```plaintext
        50
       /  \
      30   70
     / \   / \
    20 40 60 80
           \
           65
```
- **Deletion**: Removing a node and ensuring the tree continues to satisfy the binary search property.
Delete 70:
```plaintext
        50
       /  \
      30   80
     / \   / 
    20 40 60
           \
           65
```
- **Search**: Finding a node with a given key.
- **Traversal**: Visiting all nodes in a specific order (in-order, pre-order, post-order).

### Time Complexity of Binary Search Trees

The time complexity of operations on BSTs varies depending on the tree's structure.

#### Best Average Case Behavior: O(log n)

- **Balanced BSTs**: When a BST is balanced (e.g., AVL Tree, Red-Black Tree), the height of the tree is log n. This balance ensures that insertion, deletion, and search operations all have an average-case time complexity of O(log n).

#### Worst Case Behavior: O(n)

- **Degenerate (Unbalanced) Tree**: In the worst case, a BST can become unbalanced, resembling a linked list. This can occur if nodes are inserted in sorted order, leading to a tree where each node has only one child.
- **Time Complexity**: In this scenario, the tree's height becomes n, and the time complexity for insertion, deletion, and search operations degrades to O(n).

#### Summary of Time Complexities

- **Search**:
  - Average Case: O(log n)
  - Worst Case: O(n)
- **Insertion**:
  - Average Case: O(log n)
  - Worst Case: O(n)
- **Deletion**:
  - Average Case: O(log n)
  - Worst Case: O(n)

### Considering Worst Case Time Complexity

When analyzing algorithms, the worst-case time complexity is often considered to ensure efficient performance in unfavorable scenarios. For BSTs, the worst-case time complexity is O(n) when the tree is unbalanced.

### Ensuring Balanced Trees

To prevent the worst-case behavior, self-balancing BSTs like AVL Trees and Red-Black Trees can be used. These trees automatically adjust their structure during insertions and deletions to maintain balance, ensuring that the height remains O(log n) and operations have optimal time complexity.

#### AVL Trees

An AVL Tree is a self-balancing BST where the height difference between the left and right subtrees (the balance factor) is at most one.

**Key Operations**:

- **Insertion**: Updates balance factors and performs rotations (single or double) if a node becomes unbalanced.
```plaintext
  20
 /  \
10  40
    /  \
   30  50
```
Insert 25:
```plaintext
  20
 /  \
10  40
    /  \
   30  50
  /
 25
```
- **Deletion**: Updates balance factors and performs rotations as needed to restore balance.

**Rotations**:
Here's a summary of the different types of rotations used in AVL trees to maintain balance, including Left Rotation, Right-Left Rotation, and Left-Right Rotation:

### 1. **Right Rotation (RR Rotation)**

**Purpose:** To balance an AVL tree when the tree becomes unbalanced due to an insertion in the right subtree of the right child.

**Diagram:**
```plaintext
    A
     \
      B
       \
        C
```

**After Right Rotation:**
```plaintext
    B
   / \
  A   C
```

**Steps:**
- Node B becomes the new root.
- Node A becomes the left child of Node B.
- Node C remains the right child of Node B.

---

### 2. **Left Rotation (LL Rotation)**

**Purpose:** To balance an AVL tree when the tree becomes unbalanced due to an insertion in the left subtree of the left child.

**Diagram:**
```plaintext
    A
   /
  B
 /
C
```

**After Left Rotation:**
```plaintext
    B
   / \
  C   A
```

**Steps:**
- Node B becomes the new root.
- Node C becomes the left child of Node B.
- Node A becomes the right child of Node B.

---

### 3. **Left-Right Rotation (LR Rotation)**

**Purpose:** To balance an AVL tree when the tree becomes unbalanced due to an insertion in the right subtree of the left child.

**Diagram:**
```plaintext
    A
   /
  B
   \
    C
```

**Steps:**
1. **Left Rotation on Node B:**
   - Perform a left rotation on Node B to convert it into an LL case:
```plaintext
    A
   /
  C
 /
B
```

2. **Right Rotation on Node A:**
   - Perform a right rotation on Node A:
```plaintext
       C
      / \
     B   A
```

**Result:**
- Node C becomes the new root.
- Node B becomes the left child of Node C.
- Node A becomes the right child of Node C.

---

### 4. **Right-Left Rotation (RL Rotation)**

**Purpose:** To balance an AVL tree when the tree becomes unbalanced due to an insertion in the left subtree of the right child.

**Diagram:**
```plaintext
    A
     \
      B
     /
    C
```

**Steps:**
1. **Right Rotation on Node B:**
   - Perform a right rotation on Node B to convert it into an RR case:
```plaintext
    A
     \
      C
       \
        B
```

2. **Left Rotation on Node A:**
   - Perform a left rotation on Node A:
```plaintext
       C
      / \
     A   B
```

**Result:**
- Node C becomes the new root.
- Node A becomes the left child of Node C.
- Node B becomes the right child of Node C.

---

### Summary

- **Right Rotation (RR Rotation)**: Balances the tree when an insertion causes the right subtree of the right child to be deeper.
- **Left Rotation (LL Rotation)**: Balances the tree when an insertion causes the left subtree of the left child to be deeper.
- **Left-Right Rotation (LR Rotation)**: Balances the tree when an insertion causes the right subtree of the left child to be deeper.
- **Right-Left Rotation (RL Rotation)**: Balances the tree when an insertion causes the left subtree of the right child to be deeper.

Each rotation type helps maintain the AVL tree's balance property, ensuring that the tree remains balanced for efficient operations.

**Example Implementation in C**:

```c
#include <stdio.h>
#include <stdlib.h>

// Definition of a tree node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Utility function to get the height of a node
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Utility function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor of node N
int getBalance(struct Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert a key into the AVL tree
struct Node* insert(struct Node* node, int key) {
    // Perform the normal BST insertion
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance factor to check for imbalance
    int balance = getBalance(node);

    // Perform rotations based on balance factor

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// In-order traversal of the tree
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    // Construct the AVL Tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("In-order traversal of the constructed AVL tree is:\n");
    inorder(root);

    return 0;
}
```

#### Red-Black Trees

A Red-Black Tree is a self-balancing BST with the following properties:

1. Each node is either red or black.
2. The root is always black.
3. Red nodes cannot have red children (no two adjacent red nodes).
4. Every path from a node to its descendant leaves has the same number of black nodes.
5. Newly inserted nodes are red.

**Key Operations**:

- **Insertion**: Insert the new node as in a regular BST and color it red. Adjust the tree to maintain Red-Black properties through recoloring and rotations.
- **Deletion**: Perform standard BST deletion and adjust the tree to maintain properties by recoloring and rotating as needed.

Red-Black Trees offer efficient performance with fewer rotations compared to AVL Trees and are commonly used in practice.

### Conclusion

- **AVL Trees**: Maintain strict balance with a balance factor and perform rotations to ensure O(log n) time complexity for insertions, deletions, and searches.
- **Red-Black Trees**: Ensure balance with node coloring and provide efficient performance, usually requiring fewer rotations compared to AVL Trees.

Both AVL and Red-Black Trees ensure balanced structures, offering O(log n) time complexity for key operations, regardless of input data order. These self-balancing trees are widely used in practice due to their efficiency and performance guarantees.
