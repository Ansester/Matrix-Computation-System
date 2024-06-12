# Matrix Computation System

## Overview

This project is a matrix computation system developed as part of a Data Structures assignment. It provides functionalities to perform various matrix operations such as import, export, addition, multiplication, and display of matrices.

## Author

- **Name**: Ashmit Mukherjee
- **Version**: 1.0
- **Date Created**: 28-02-2023

## Description

The Matrix Computation System allows users to perform different matrix operations through a command-line interface. The operations supported include importing matrices from files, exporting matrices to files, adding and multiplying matrices, and displaying matrices in different formats.

## Features

- **Import Matrix**: Read a matrix from a specified file.
- **Export Matrix**: Write a matrix to a specified file.
- **Add Matrices**: Add two matrices and store the result in the first matrix.
- **Multiply Matrix by Constant**: Multiply a matrix by a constant and update the matrix.
- **Multiply Matrices**: Multiply two matrices and return the resultant matrix.
- **Display Matrix**: Display a matrix in an optimized structure.
- **Display Matrix in 2D**: Display a matrix in a 2D structure.
- **Help**: Display the list of available commands.
- **Exit**: Exit the program.

## Commands

Here is the list of available commands:

- `import <file_name>`: Read a matrix from `<file_name>`.
- `export <MatrixID file_name>`: Write a matrix to `<file_name>`.
- `add <MatrixID1 MatrixID2>`: Add two matrices and store the result in the first matrix.
- `multi-by-const <MatrixID const>`: Multiply a matrix by a constant.
- `multi-by-matrix <MatrixID1 MatrixID2>`: Multiply a matrix by another matrix.
- `display <MatrixID>`: Display a matrix in the optimized structure.
- `display2D <MatrixID>`: Display a matrix in a 2D structure.
- `help`: Display the list of available commands.
- `exit`: Exit the program.

## Technical Details

### File Structure

- `main.cpp`: The main program file containing the entry point and command handling logic.
- `linkedmatrix.h`: Header file for the linked matrix implementation.
- `linkedmatrix.cpp`: Implementation file for the linked matrix operations.
- `matcomp.h`: Header file for matrix computation logic.
- `matcomp.cpp`: Implementation file for matrix computation operations.

### Classes and Methods

#### LinkedMatrix Class (linkedmatrix.h/.cpp)

This class manages the storage and operations of matrices using a linked list representation.

- **Methods**:
  - `LinkedMatrix()`: Constructor to initialize an empty matrix.
  - `~LinkedMatrix()`: Destructor to clean up allocated resources.
  - `importMatrix(std::string fileName)`: Method to import matrix data from a file.
  - `exportMatrix(std::string fileName)`: Method to export matrix data to a file.
  - `addMatrix(LinkedMatrix& other)`: Method to add another matrix to the current matrix.
  - `multiplyByConstant(double constant)`: Method to multiply the matrix by a constant.
  - `multiplyByMatrix(LinkedMatrix& other)`: Method to multiply the matrix by another matrix.
  - `display()`: Method to display the matrix in an optimized structure.
  - `display2D()`: Method to display the matrix in a 2D structure.

#### MatComp Class (matcomp.h/.cpp)

This class manages the overall computation system, handling user commands and coordinating operations on matrices.

- **Methods**:
  - `MatComp()`: Constructor to initialize the computation system.
  - `void listCommands()`: Method to list all available commands.
  - `void executeCommand(std::string command)`: Method to execute a given command.
