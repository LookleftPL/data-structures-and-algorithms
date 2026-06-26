# Data Structures, Algorithms and Design Patterns in C++

This repository contains a comprehensive collection of academic implementations of fundamental data structures, graph algorithms, and object-oriented design patterns written in C++. The focus of these projects is to understand low-level memory management, pointer manipulation, and foundational computer science concepts from scratch without relying on complex external libraries.

## Repository Structure

### 1. Data Structures
* **Lists** (`ImplementacjaListy`, `ImplementacjaListyWskaznikowej`): Implementations covering both array-based representations and pointer-based linked lists to analyze sequential memory reallocation versus dynamic node chaining.
* **Stacks** (`ImplementacjaStosuTablicowego`): A sequential, array-based implementation of the Last In, First Out (LIFO) data structure with standard allocation tracking.
* **Queues** (`KolejkaCyklicznaTablicowa`, `KolejkaWskaznikowa`, `KolejkaPriorytetowa`): Implementations of cyclic array-based buffers, pointer-based FIFO structures, and priority queues handling element sorting based on designated weights.
* **Hash Tables** (`Haszowanie`): Custom data storage utilizing hashing algorithms and fundamental collision resolution strategies.
* **Sets** (`ImplementacjaZbioru`): Custom low-level implementation handling standard mathematical set properties and elements encapsulation.
* **Binary Trees** (`DrzewoBinarne`): Standard node-based pointer implementations covering binary tree generation, element insertion, and tree traversals.

### 2. Graph Algorithms
* **Graph Traversals** (`GrafyZBFS`, `GrafyZBFSzWizytatorem`): Graph exploration utilities leveraging the Breadth-First Search (BFS) routing mechanism.
* **Spanning Trees** (`DFSdrzewoROZPINAJACE`): Computation of spanning trees through deep path edge classification based on the Depth-First Search (DFS) algorithm.
* **Graph Topology & Connectivity** (`GrafySPOJNOSC`, `Grafy`, `GrafyzIteratorami`): Modules evaluating graph structure soundness, path verification, and iterator-driven abstraction for graph element navigation.

### 3. Behavioral Design Patterns
* **Iterator Pattern** (`Iterator`): Decoupling container architecture from sequential navigation logic.
* **Visitor Pattern** (`WizytatorOdd`, `WizytatorSUM`, `Wizytatorzy`): Utilizing double-dispatch mechanisms to execute external operations on graph and tree data structures, specifically handling odd element filtering and summary math calculations.

### 4. Advanced Applications
* **Reverse Polish Notation Utility** (`OdwrotnaNotacjaPolska`): A complete text-interfaced calculation application that parses standard infix expressions, converts them to postfix notation via the Shunting-yard algorithm, and evaluates numerical results using an operand stack.
* **Skarbonki** (`Skarbonki`): Algorithmic problem solver utilizing structural optimization techniques based on custom data graphs.

---

## Computational Complexity & Performance Analysis

The underlying operations rely heavily on core C++ Standard Library containers (`std::stack`, `std::vector`), ensuring predictable asymptotic boundaries.

### Core Data Structures Performance
* **Stack Operations** (`PUSH`, `POP`, `TOP`, `EMPTY`): Guaranteed $O(1)$ constant time complexity. Complete stack reset (`MAKENULL`) operates at $O(n)$ linear complexity due to sequential element eviction.
* **Vector Buffers**: Constant access time $O(1)$ via internal array indices (`RETRIEVE`), and amortized $O(1)$ performance for trailing insertions (`PUSH_BACK`). Sequential clears run in $O(n)$ space-releasing cycles.

### Application Complexity: Reverse Polish Notation
* **Infix-to-Postfix (Shunting-yard)**:
  * **Time Complexity**: $O(n)$ — Processes the input string token-by-token in a single pass. Since each operator enters and leaves the internal operator stack at most once, nested verification cycles remain strictly bounded linearly.
  * **Space Complexity**: $O(n)$ — Memory usage scales linearly relative to expression size due to intermediate token storage within auxiliary vectors and stacks.
* **Postfix Evaluation**:
  * **Time Complexity**: $O(n)$ — Iterates through the RPN representation exactly once, executing constant-time $O(1)$ basic mathematical operations per operand pairing.
  * **Space Complexity**: $O(n)$ — In the worst-case scenario, the arithmetic execution stack holds a proportional allocation of operands bounded by the overall character length.

---

## Getting Started

### Prerequisites
* A C++ compiler compliant with at least the C++11 standard (such as GCC, Clang, or MSVC).

### Compilation and Execution Example
To compile any standard standalone console module (e.g., the Reverse Polish Notation binary), navigate to its directory via your command-line interface and use G++:

```bash
g++ main.cpp -o program
