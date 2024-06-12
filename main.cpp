//============================================================================
// Name         : DS Assignment#1
// Author       : Ashmit Mukherjee
// Version      : 1.0
// Date Created : 28-02-2023
// Date Modified:
// Description  : Matrix Computation - Main Program
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
#include<iomanip>

#include "linkedmatrix.h"
#include "matcomp.h"
using namespace std;

//=====================================
void listCommands()
{
	cout<<" ===================================================================================="<<endl
		<<" Welcome to the Matrix Computation system!\n"<<endl
		<<" List of available Commands:"<<endl
		<<" import <file_name>                      : Read a matrix from <filename>"<<endl
		<<" export <MatrixID1 file_name>                      : Write a matrix into <filename>"<<endl
		<<" add  <MatrixID1 MatrixID2>              : Add 2 matrices A and B and store the result in matrix A"<<endl
		<<" multi-by-const <MatrixID const>         : Multiply a matrix by a constant and update the matrix"<<endl
		<<" multi-by-matrix <MatrixID1 MatrixID2>   : Multiply a matrix by another matrix and return the resultant"<<endl
		<<" display  <<MatrixID>                    : Display a matrix in the optimized structure"<<endl
		<<" display2D <<MatrixID>                   : Display a matrix in the optimized structure"<<endl
		<<" help                                    : Display the list of available commands"<<endl
		<<" exit                                    : Exit the Program"<<endl
		<<" ====================================================================================\n"<<endl;
		
}

// define the needed methods to execute the operations in the system (import, export, add, ...)





//=======================================
// main function
int main()
{

	MatComp matCompSys;

	listCommands();
	string user_input;
	string command;
	string parameter1;
	string parameter2;

	do
	{
		try
		{
			cout<<"> ";
			getline(cin,user_input);
			
			// parse userinput into command and parameter(s)
			stringstream sstr(user_input);
			getline(sstr,command,' ');
			getline(sstr,parameter1,' ');
			getline(sstr,parameter2);
			
			//add code as necessary
			if(command == "import")
			{
				matCompSys.importMatrix(parameter1);

			}
			else if(command == "export")
			{
				matCompSys.exportMat(parameter1[0],parameter2);
			}
			else if(command == "add")
			{
				matCompSys.add(parameter1[0],parameter2[0]);
			}
			else if(command == "multi-by-const")
			{
				matCompSys.multi(parameter1[0],stoi(parameter2));
			}
			else if(command == "multi-by-matrix")
			{
				matCompSys.multi(parameter1[0],parameter2[0]);
			}
			else if(command == "display")	matCompSys.display(parameter1[0]);
			else if(command == "display2D")	matCompSys.display2D(parameter1[0]);

			else if(command == "help")			listCommands();
			else if(command == "exit")			break;
			else 							cout<<"Invalid Command!"<<endl;
			fflush(stdin);
		}
		catch(exception &ex)
		{
			cout<<ex.what()<<endl;
		}
	}while(true);



	return EXIT_SUCCESS;
}
