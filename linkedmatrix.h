//============================================================================
// Name         : DS Assignment#1
// Author       : Ashmit Mukherjee
// Version      : 1.0
// Date Created : 14-02-2023
// Date Modified:
// Description  : Linked List-based Matrix class for an optimized structure
//============================================================================
#ifndef LINKEDMATRIX_H //include guards
#define LINKEDMATRIX_H
#include<cstdlib>
#include<iomanip>
#include<iostream>
using namespace std;
class Node
{
private:
	int row; //the row index
	int column; //the column index
	int value; //the value of the element
	Node* next; //pointer to the next node within the same row
	Node* down; //pointer to the next node within the same column
	
public:
	friend class LinkedMatrix;
	friend class MatComp;
	Node(int row, int column, int value) : row(row), column(column), value(value), next(NULL), down(NULL)
	{}
	
	//add any other necessary code here
};
//=============================================================================
class LinkedMatrix
{
private:
	int numRows; //the number of rows
	int numCols; //the number of columns
	int numNonZeroElements;
	Node** rowArray;
	Node** colArray;
	
public:
	friend class MatComp;
	LinkedMatrix();
	void create(int numRows, int numCols); // creates an empty matrix given the provided dimensions
	int getNumRows() const; // returns the total number of rows
	int getNumCols() const; // returns the total number of columns
	void display() const; // display the matrix dimensions, number of non-zero members, and the non-zero members' cardinalities+values
	void display2D() const; // display the matrix dimensions, number of non-zero members, and the non-zero members' cardinalities+values
	void insertElement(int Row_Indx, int Col_Indx, int value);
	void removeElement(int Row_Indx, int Col_Indx);
	int getValue(int Row_Indx, int Col_Indx) const;
	~LinkedMatrix(); // destructor to properly delete the matrix and deallocate all nodes
	
	//add any other necessary code here
	
};


#endif
