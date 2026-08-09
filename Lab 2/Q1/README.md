# Dictionary Operations — DAA Lab

## 1. Problem Statement

Consider a Dictionary abstract data type (ADT) that permits access to data items by their key.

The primary operations are:

- `Search(D, k)` — Search for an item with key `k`.
- `Insert(D, x)` — Insert item `x` into the dictionary.
- `Delete(D, x)` — Delete the item pointed to by `x`.
- `Maximum(D)` — Retrieve the item with the largest key.
- `Minimum(D)` — Retrieve the item with the smallest key.
- `Predecessor(D, x)` — Retrieve the item whose key is immediately smaller than the key of `x`.
- `Successor(D, x)` — Retrieve the item whose key is immediately larger than the key of `x`.

The objective is to determine the **asymptotic worst-case running time** of these operations when the dictionary is implemented using:

1. Unsorted array
2. Sorted array
3. Singly linked unsorted list
4. Singly linked sorted list
5. Doubly linked unsorted list
6. Doubly linked sorted list

The C program uses **Raylib** to simulate the operations, count basic operations/comparisons, and visualize their growth.

---

## 2. Objective

- Implement dictionary operations using six different data structures.
- Analyze the worst-case asymptotic complexity of the seven operations.
- Simulate the operations for increasing values of `n`.
- Count operation/comparison steps.
- Plot the measured growth using Raylib.
- Compare experimental behavior with theoretical Big-O complexity.

---

## 3. Data Structures

### 3.1 Unsorted Array

Elements are stored in an arbitrary order.

Typical behavior:

- Search requires scanning the array.
- Insert can be done at the end if free space is available.
- Delete may require shifting elements.
- Minimum, maximum, predecessor, and successor require scanning.

### 3.2 Sorted Array

Elements are maintained in increasing key order.

Typical behavior:

- Search can use binary search.
- Insert requires shifting elements.
- Delete requires shifting elements.
- Minimum and maximum are directly available at the first and last positions.
- Predecessor and successor are adjacent positions when the position of `x` is known.

### 3.3 Singly Linked Unsorted List

Nodes are linked using one `next` pointer and are not sorted.

Typical behavior:

- Search requires traversal.
- Insertion at the head is constant time.
- Deletion given only a node pointer may require finding its predecessor.
- Minimum, maximum, predecessor, and successor generally require traversal.

### 3.4 Singly Linked Sorted List

Nodes are maintained in increasing key order.

Typical behavior:

- Search can stop early when a larger key is encountered.
- Insert requires finding the correct position.
- Minimum is the first node.
- Maximum requires traversing to the last node.
- Predecessor generally requires traversal because there is no `prev` pointer.
- Successor can be obtained directly once the node `x` is known.

### 3.5 Doubly Linked Unsorted List

Each node contains both `prev` and `next` pointers.

Typical behavior:

- Search requires traversal.
- Insertion at the head is constant time.
- Deletion is constant time when a pointer to the node is already available.
- Minimum and maximum require traversal.
- Predecessor and successor are constant time when `x` is already available.

### 3.6 Doubly Linked Sorted List

Nodes are maintained in sorted order and contain both `prev` and `next` pointers.

Typical behavior:

- Search requires traversal.
- Insert requires finding the correct position.
- Delete is constant time when `x` is already available.
- Minimum and maximum are directly available from the ends if maintained.
- Predecessor and successor are constant time when `x` is already available.

---

## 4. Worst-Case Complexity

The following table gives the expected worst-case asymptotic running times.

| Data Structure | Search | Insert | Delete | Maximum | Minimum | Predecessor | Successor |
|---|---:|---:|---:|---:|---:|---:|---:|
| Unsorted Array | O(n) | O(1)* | O(n) | O(n) | O(n) | O(n) | O(n) |
| Sorted Array | O(log n) | O(n) | O(n) | O(1) | O(1) | O(1)† | O(1)† |
| Singly Unsorted List | O(n) | O(1)* | O(n) | O(n) | O(n) | O(n) | O(n) |
| Singly Sorted List | O(n) | O(n) | O(n) | O(n) | O(1) | O(n) | O(1)† |
| Doubly Unsorted List | O(n) | O(1)* | O(1)† | O(n) | O(n) | O(1)† | O(1)† |
| Doubly Sorted List | O(n) | O(n) | O(1)† | O(1)‡ | O(1)‡ | O(1)† | O(1)† |

### Notes

`*` Insert assumes insertion at an available end/head position and no resizing cost.

`†` The operation is constant time **when the required item/pointer is already available**, as specified by the dictionary ADT. In particular, `Delete(D, x)`, `Predecessor(D, x)`, and `Successor(D, x)` receive a pointer `x`.

`‡` Maximum and minimum are `O(1)` when pointers to both ends of the sorted doubly linked list are maintained. If only a head pointer is maintained, finding the maximum requires `O(n)` traversal.

The exact implementation and assumptions should be considered when comparing experimental results with the theoretical table.

---

## 5. Project Structure

```text
Q1/
├── src/
│   └── main.c
└── README.md
```

The main source file contains:

- Dictionary data structures
- Dictionary operations
- Operation-count measurement
- Raylib graph generation
- Keyboard controls

---

## 6. Raylib Simulation

The program tests increasing input sizes:

```text
n = 50, 100, 150, ..., 1000
```

For every value of `n`, the program executes the selected dictionary operation and records a basic operation/comparison count.

The results are then plotted on the Raylib window.

### Controls

| Key | Action |
|---|---|
| `RIGHT` | Next dictionary operation |
| `LEFT` | Previous dictionary operation |
| Window close | Exit program |

The operations are displayed in this order:

```text
Search
Insert
Delete
Maximum
Minimum
Predecessor
Successor
```

---

## 7. Graph Interpretation

The graph plots:

- **X-axis:** Input size `n`
- **Y-axis:** Measured operation/comparison count
- **Each curve:** One of the six dictionary implementations

The program uses measured values rather than directly drawing theoretical functions.

Therefore, the graph demonstrates the **experimental order of growth** of the implementations.

### Important observation

When multiple implementations have the same asymptotic complexity, their curves may overlap or appear very close.

For example, several implementations of `Search` have:

```text
O(n)
```

while sorted arrays can achieve:

```text
O(log n)
```

using binary search.

Similarly, an `O(1)` curve can appear almost flat compared with an `O(n)` curve on a normal linear Y-axis.

This is expected behavior.

---

## 8. Why Some Curves Are Difficult to See

Different growth rates can have very different magnitudes.

For example:

```text
O(1)       ≈ constant
O(log n)   ≈ slowly increasing
O(n)       ≈ linear
```

At `n = 1000`, a linear curve can be around hundreds or thousands of operations while a logarithmic curve may be only around a few tens of operations.

Consequently, the smaller curves can appear compressed near the X-axis.

This does **not** mean that the smaller curves are missing.

---

## 9. Experimental vs Theoretical Analysis

The purpose of the simulation is to compare measured behavior with theoretical asymptotic analysis.

For example:

### Unsorted Array Search

The worst case requires checking every element:

```text
T(n) = O(n)
```

The graph should therefore show approximately linear growth.

### Sorted Array Search

Binary search repeatedly divides the search range:

```text
T(n) = O(log n)
```

The graph should increase much more slowly than a linear search.

### Doubly Linked List Predecessor/Successor

Given a pointer to `x`, the neighboring node can be accessed directly:

```text
Predecessor(x) → x->prev
Successor(x)   → x->next
```

Therefore:

```text
T(n) = O(1)
```

The search required to obtain `x` must not be included when analyzing these operations because the dictionary operation is defined as receiving the pointer `x`.

---

## 10. Compilation

The project requires:

- C compiler such as GCC/MinGW
- Raylib
- Raylib development libraries

For MinGW/GCC on Windows, a typical command is:

```bash
gcc src/main.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm -lm
```

If Raylib is installed in a custom directory, specify the include and library paths:

```bash
gcc src/main.c -o main.exe ^
-I"C:\path\to\raylib\include" ^
-L"C:\path\to\raylib\lib" ^
-lraylib -lopengl32 -lgdi32 -lwinmm -lm
```

Adjust the paths according to the local Raylib installation.

---

## 11. Running the Program

After compilation:

```bash
main.exe
```

The Raylib window opens with the graph for `Search`.

Use:

```text
RIGHT → next operation
LEFT  → previous operation
```

---

## 12. Expected Results

The experimental results should broadly demonstrate:

- Linear operations produce approximately linear growth.
- Binary search on a sorted array grows logarithmically.
- Constant-time operations remain approximately flat.
- Operations requiring shifting in arrays grow linearly.
- Linked-list operations requiring traversal grow linearly.
- Doubly linked predecessor/successor operations are constant time when the node pointer is already available.
- Curves with the same asymptotic complexity can overlap.

The exact measured values depend on the operation-counting method and implementation details.

---

## 13. Limitations

The graph measures selected basic operations/comparisons rather than actual wall-clock execution time.

Therefore, the simulation is intended to validate **order of growth**, not processor-level execution speed.

Factors such as:

- compiler optimization,
- memory allocation,
- cache behavior,
- hardware,
- operating-system scheduling

are not the focus of this experiment.

---

## 14. Conclusion

The Raylib simulation provides an experimental visualization of dictionary operations implemented using arrays and linked lists.

The results can be compared with the theoretical worst-case complexity table to understand how the choice of data structure affects:

- Searching
- Insertion
- Deletion
- Minimum/maximum retrieval
- Predecessor/successor operations

The experiment demonstrates that there is no single best dictionary representation for every operation. The appropriate data structure depends on which operations are expected to be performed most frequently.
