#include "linkedmatrix.h"
#include<cstdlib>
#include<iomanip>
#include<iostream>
using namespace std;

LinkedMatrix::LinkedMatrix(){};//empty contructor

void LinkedMatrix::create(int numRows, int numCols)
{
	rowArray = new Node*[numRows](); // Initialize all elements to nullptr
	colArray = new Node*[numCols](); //initialize all the pointers to nullptr
	this->numRows=numRows;
	this->numCols=numCols;
	numNonZeroElements=0;
}

int LinkedMatrix::getNumRows() const
{
	return numRows; //returns number of rows
	
}

int LinkedMatrix::getNumCols() const
{
	return numCols; //returns number of columns
}

void LinkedMatrix::insertElement(int Row_Indx, int Col_Indx, int value) {
	// First, check and update a flag if the node already exists in the row
	Node* currentNode = rowArray[Row_Indx]; //initializing two cursors for the implementations
	Node* prevNode = nullptr;
	
	// Update the value if node exists by traversing through the row and finding matching column index
	while (currentNode != nullptr) {
		if (currentNode->column == Col_Indx) {
			currentNode->value = value;
			return; //terminates the function
		}
		prevNode = currentNode; //if matching column index is not found then advance the pointers to the next node
		currentNode = currentNode->next;
	}
	
	// If node doesn't exist, create it and insert it into the row
		Node* newNode = new Node(Row_Indx, Col_Indx, value); //initializes a new node
		numNonZeroElements++; //increments number of non zero element for every element added since it assumes only non-zero elements are added
		if (prevNode == nullptr) { // Insert at the beginning of the row if no row pointer points to null
			newNode->next = rowArray[Row_Indx];
			rowArray[Row_Indx] = newNode;
		} else { // Insert in the middle or end of the row in case there is already an element that the row points to.
			newNode->next = prevNode->next;
			prevNode->next = newNode;
		}
		
		//Insert the new node into the correct position in the column after doing for the row.
		currentNode = colArray[Col_Indx];
		prevNode = nullptr;
		//traverse through the column to find the element with matching row
		while (currentNode != nullptr && currentNode->row < Row_Indx) {
			prevNode = currentNode;
			currentNode = currentNode->down;
		}
		
		if (prevNode == nullptr) { // Insert at the beginning of the column if the column is empty
			newNode->down = colArray[Col_Indx];
			colArray[Col_Indx] = newNode;
		} else { // otherwise insert in the middle or end of the column
			newNode->down = prevNode->down;
			prevNode->down = newNode;
		}
	
}

void LinkedMatrix::removeElement(int Row_Indx, int Col_Indx) {
	Node* currentNode = rowArray[Row_Indx]; //initializing two cursors for the implementations
	Node* prevNode = nullptr;
	//traversing through the row the find the element
	while (currentNode != nullptr && currentNode->column < Col_Indx) {
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
	
	// If the node is found in the row
	if (currentNode != nullptr && currentNode->column == Col_Indx) {
		if (prevNode == nullptr) { // if the node to be removed is the first node in the row
			rowArray[Row_Indx] = currentNode->next;
		} else {
			prevNode->next = currentNode->next; //if not the the previous of the redundant node is set to point at the node next to it
		}
	} else {
		// Element not found in the row, so we return without removing
		return;
	}
	
	// Remove from the column list
	Node* colNode = colArray[Col_Indx]; //initializing pointers to traverse through the column
	Node* prevColNode = nullptr;
	
	//traverse through the column to find the element
	while (colNode != nullptr && colNode->row < Row_Indx) {
		prevColNode = colNode;
		colNode = colNode->down;
	}
	
	// If the node is found in the column
	if (colNode != nullptr && colNode->row == Row_Indx) {
		if (prevColNode == nullptr) { // if the node to be removed is the first node in the column
			colArray[Col_Indx] = colNode->down;
		} else {
			prevColNode->down = colNode->down; //else the node before the redundant node is set to point to the next node
		}
	}
	// now the node is disconnected from both the row and column, so we can safely delete it.
	delete currentNode;
}

void LinkedMatrix::display() const
{
	//displays the required variable
	cout << "NumRows = "<< numRows<<setw(14) << "NumCols = " << numCols <<setw(25) << "NumNonZeroElements = " << numNonZeroElements << endl;
	
	
	Node* p; //initializing a pointer and traversing through each row
	for(int i = 0; i < numRows; i++) {
		p = rowArray[i];
		while (p != nullptr) {
			cout << '(' << p->row << ',' << p->column << ')' << " = " << p->value << endl; //displaying the element in required formatd
			p = p->next;
		}
	}
	
	cout<<"Done! \n";
}

void LinkedMatrix::display2D() const {
	for (int i = 0; i < numRows; i++) {
		Node* p = rowArray[i];
		int lastColPrinted = -1; // Tracks the last column index for which an element (zero or non-zero) was printed
		
		while (p != nullptr) {
			// Print zeros for columns before the current non-zero element's column
			for (int j = lastColPrinted + 1; j < p->column; j++) {
				cout << setw(15) << '0';
			}
			// Prints the current non-zero element
			cout << setw(15) << p->value;
			lastColPrinted = p->column; // Update the last printed column index
			
			p = p->next; // Move to the next node in the row
		}
		
		// Fill in zeros for any remaining columns after the last non-zero element
		for (int j = lastColPrinted + 1; j < numCols; j++) {
			cout << setw(15) << '0';
		}
		cout << endl; // Move to the next row
	}
}

int LinkedMatrix::getValue(int Row_Indx, int Col_Indx) const
{
	if (Row_Indx < 0 || Row_Indx >= numRows || Col_Indx < 0 || Col_Indx >= numCols) {
		throw runtime_error("Index out of bounds"); //throws runtime error in case the requested row and column index is out of bounds
	}
	//traverse through the row to find the node with matching column and return the value of theat node
	Node* p;
	p=rowArray[Row_Indx];
	while(p!=nullptr)
	{
		if(p->column==Col_Indx)return p->value;
		else p=p->next;
	}
	
	
	return 0; //returns 0 if the element doesnt exist
}

LinkedMatrix::~LinkedMatrix() { //destructor
	Node* p;
	Node* q;
	//iterates over each row and deleting every elements
	for (int i = 0; i < numRows; i++) {
		p = rowArray[i];
		while (p != nullptr) {
			q = p->next; // Save the pointer to the next node
			delete p; // Delete the current node
			p = q; // Move to the next node
		}
	}
	
	// deleting the rowArray and colArray pointers
	delete[] rowArray;
	delete[] colArray;
}
