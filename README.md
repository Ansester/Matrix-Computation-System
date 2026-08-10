# Matrix Computation System

A C++ command-line application for sparse-matrix computation using linked list data structures.

---

## Context & Provenance

* **Project Context**: Course project for Data Structures (NYU Abu Dhabi).
* **Author**: Ashmit Mukherjee.

---

## Technical Details

* **Linked Storage**: Represents sparse matrices using non-zero linked nodes rather than dense 2D arrays to conserve memory for large sparse matrices.
* **Supported Operations**:
  * `import <file_name>` / `export <MatrixID file_name>`: Reads and writes sparse matrix state.
  * `add <MatrixID1 MatrixID2>`: Adds two sparse matrices using pointer traversal.
  * `multi-by-const <MatrixID const>`: Scales non-zero matrix elements.
  * `multi-by-matrix <MatrixID1 MatrixID2>`: Sparse matrix-matrix multiplication.
  * `display2D <MatrixID>`: Formatted 2D grid rendering.

---

## Running Locally

```bash
# Compile
make

# Run
./matcomp
```

---

## License

This repository's source code is licensed under the [MIT License](LICENSE).
