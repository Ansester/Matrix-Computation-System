#include "matcomp.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


MatComp::MatComp()
{
	matrix_list = new LinkedMatrix*[26](); //initializes dynamically stored array of pointers pointing to 26 matricess
	matrix_count=0; //resets the matrix count to zero
	
}

MatComp::~MatComp()
{
	for(int i = 0; i < matrix_count; i++)
	{
		delete matrix_list[i]; // This calls the destructor of the elements of LinkedMatrix automatically
	}
}


void MatComp::importMatrix(string filename) {
	ifstream file(filename); //creates a input file stream for the given filename
	if (!file.is_open()) {
		throw runtime_error("Failed to open file"); //throws exception if there is an error opening the file
	}
	
	int rows(0), columns(0);
	[[maybe_unused]]int nonZeroElements(0); //creating a maybe unused integer so that g++ can ignore it. this only exists to help pointer advance while reading the while
	string line;
	
	// Read matrix dimensions by parsing the strings read from the file
	getline(file, line); // Reads the row info
	rows = stoi(line.substr(line.find('=') + 1));
	getline(file, line); // Reads the column info
	columns = stoi(line.substr(line.find('=') + 1));
	getline(file, line); // Reads the number of non-zero elements (not used but necessary to move the file pointer)
	nonZeroElements = stoi(line.substr(line.find('=') + 1));
	
	matrix_list[matrix_count] = new LinkedMatrix(); //initializes new linked matrix
	matrix_list[matrix_count]->create(rows, columns); //creates row and column arrays
	char matrixCode = 'A' + matrix_count; // Calculate the alphabetic code
	
	// Process the list of non-zero elements
	int rowIndex, colIndex, value;
	while (getline(file, line)) {
		stringstream ss(line); //reads through each line of the file
		char discard;
		ss >> discard >> rowIndex >> discard >> colIndex >> discard; // Discard the brackets and punctuations
		ss.ignore(10, '='); // Ignore until '='
		ss >> value; // Read the value
		matrix_list[matrix_count]->insertElement(rowIndex, colIndex, value); //insert element in the given indices and value
	}
	cout << "Done! This is matrix '" << matrixCode << "'" << endl;
	matrix_count++;
	file.close(); //closes file
}

void MatComp::add(char matrix1_ID, char matrix2_ID) {
	if(!isValid(matrix1_ID)||!isValid(matrix2_ID)) throw runtime_error("Matrix with the given IDs do not exist"); //check if the given argument matrices are valid
	int matrix1Index = toupper(matrix1_ID) - 'A'; //convert the matrix code to integer. force it to be upper case
	int matrix2Index = toupper(matrix2_ID) - 'A';
	
	// Ensure the matrices have the same dimensions
	if (matrix_list[matrix1Index]->getNumRows() != matrix_list[matrix2Index]->getNumRows() ||
		matrix_list[matrix1Index]->getNumCols() != matrix_list[matrix2Index]->getNumCols()) {
		throw runtime_error("Matrices have different dimensions and cannot be added!"); //throw runtime error if the matrices are of different dimensions
	} else {
		for (int i = 0; i < matrix_list[matrix1Index]->getNumRows(); i++) {
			Node* q = matrix_list[matrix2Index]->rowArray[i]; // Pointer for traversing the second matrix's row
			
			while (q != nullptr) {
				int existingValue = matrix_list[matrix1Index]->getValue(q->row, q->column);
				int sum = q->value + existingValue;
				
				if (sum != 0) {
					// If the sum is not zero, update or insert the element
					matrix_list[matrix1Index]->insertElement(q->row, q->column, sum);
				} else {
					// If the sum is zero, remove the element if it exists
					matrix_list[matrix1Index]->removeElement(q->row, q->column);
				}
				
				q = q->next; // Move to the next node in the row
			}
		}
	}
	cout<<"Done! \n";
}


void MatComp::multi(char matrix_ID, int a)
{	if(!isValid(matrix_ID)) throw runtime_error("No matrix with this ID exists in the system"); //checks if the matrix exists in the system throws runtime error
	Node* p;
	int index = toupper(matrix_ID) - 'A'; //convert matrix code to integer
	for(int i = 0; i < matrix_list[index]->numRows; i++) {
		p = matrix_list[index]->rowArray[i]; //iterate through each node and multiply the value by the constant
		while (p != nullptr) {
			p->value*=a;
			p = p->next;
		}
	}
	cout<<"Done! \n";
}


void MatComp::exportMat(char matrix1_ID, string filename)
{
	if(!isValid(matrix1_ID))throw runtime_error("Matrix with given ID does not exist in the system"); //check if the argument matrix is valid
	int index = toupper(matrix1_ID) - 'A'; //convert the given matrix ID to integer
	
	ofstream outfile (filename,ios::out); //creates output file stream
	if (outfile.fail()) {
		throw runtime_error("Failed to open file"); //throws exception if there is an error opening the file
	}
	
	outfile<<"Rows=" <<matrix_list[index]->numRows <<endl <<"Columns="<<matrix_list[index]->numCols <<endl<<"Non-ZeroElements="<<matrix_list[index]->numNonZeroElements<<endl; //prints the basic template along with their values
	
	Node* p;
	for(int i = 0; i < matrix_list[index]->numRows; i++) { //iterate through each row, printing the elements in the given format
		p = matrix_list[index]->rowArray[i];
		while (p != nullptr) {
			outfile << '(' << p->row << ',' << p->column << ')' << "=" << p->value << endl;
			p = p->next;
		}
	}
	
	cout<<"Done! \n";
	outfile.close(); //closes file
	
}

void MatComp::display(char matrix_ID)
{
	if(!isValid(matrix_ID)) //checks if matrix exists in the list
	{
		throw runtime_error("No matrix with this ID exists in the system"); //throws runtime error
	}
	
	int index = toupper(matrix_ID) - 'A';
	matrix_list[index]->display(); //calls display function
	
}

void MatComp::display2D(char matrix_ID)
{
	if(!isValid(matrix_ID)) //checks if matrix exists in the list
	{
		throw runtime_error("No matrix with this ID exists in the system"); //throws runtime error
	}
	int index = toupper(matrix_ID) - 'A';
	matrix_list[index]->display2D(); //calls display2D function
}

bool MatComp::isValid(char matrix_ID) {
	int index = toupper(matrix_ID) - 'A'; //converts matrix code
	return matrix_list[index] != nullptr; //checks if the pointer points to null
}


void MatComp::multi(char matrix1_ID, char matrix2_ID) {
	if(!isValid(matrix1_ID)|| !isValid(matrix2_ID)) {
		//checks if the matrix index is valid and exists
		throw runtime_error("No matrix with this ID exists in the system");
	}
	
	int index1 = toupper(matrix1_ID) - 'A'; //converting to integers
	int index2 = toupper(matrix2_ID) - 'A';
	int nonzero(0);
	
	LinkedMatrix* mat1 = matrix_list[index1]; //creating a pointer to the matrices for easy implementations
	LinkedMatrix* mat2 = matrix_list[index2];
	
	if (mat1->numCols != mat2->numRows) {
		throw runtime_error("Matrix dimensions mismatch for multiplication"); //throws runtime error if the matrix dimensions are not compatible
	}
	
	matrix_list[matrix_count] = new LinkedMatrix(); //create new matrix to store the result
	matrix_list[matrix_count]->create(mat1->numRows, mat2->numCols); //creating the row and column arrays
	char matrixCode = 'A' + matrix_count; //give the matrix a code
	
	for (int i = 0; i < mat1->numRows; i++) { //iterate for each row of matrix 1
		for (int j = 0; j < mat2->numCols; j++) { //iterate for each column of matrix 2
			int sum = 0;
			for (int k = 0; k < mat1->numCols; k++) {
				int mat1Val = mat1->getValue(i, k);
				int mat2Val = mat2->getValue(k, j);
				sum += mat1Val * mat2Val; //add the sum of the required elements
			}
			if (sum != 0) {
				matrix_list[matrix_count]->insertElement(i, j, sum); //insert the element only if the sum is nonzero
				nonzero++; //increment number of nonzeroelements
			}
			// No else branch needed for removing or handling zero sums
		}
	}
	
	matrix_list[matrix_count]->numNonZeroElements=nonzero; //edit the number of nonzero elements
	cout << "Done! This is matrix '" << matrixCode << "'" << endl;
	matrix_count++; //increment matrix count
}
