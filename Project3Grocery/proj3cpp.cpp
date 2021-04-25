#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"proj3py");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"proj3py");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Reads frequency.dat file and generates a colored histogram
void histogramReader() {
	// file frequency.dat's ifstream object
	ifstream frequency;
	// fileLine string holds grocery item's name
	string fileLine;
	// temp string temporarily holds quantity of grocery item purchased
	string temp;
	// numPurchased int hods integer value for quantity purchased
	int numPurchased = 0;
	// creates HANDLE object for console's output
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// opens frequency.dat
	frequency.open("frequency.dat");
	
	// if file is open, read file
	if (frequency.is_open()) {
		// while lines are readable and not end of file
		while (!frequency.fail() && !frequency.eof()) {
			// reads line until ' ' character encountered, sets fileLine to that string
			std::getline(frequency, fileLine, ' ');
			// reads remainder of line, sets temp to that string
			std::getline(frequency, temp);
			// sets numPurchased to the integer value of temp string
			numPurchased = std::stoi(temp);

			// if numPurchased is 3 or fewer, set console color to red
			if (numPurchased <= 3) {
				SetConsoleTextAttribute(hConsole, 12);
			}
			// if numPurchased is 5 or fewer, set console color to yellow
			else if (numPurchased <= 5) {
				SetConsoleTextAttribute(hConsole, 14);
			}
			// if numPurchased is 8 or fewer, set console color to teal
			else if (numPurchased <= 8) {
				SetConsoleTextAttribute(hConsole, 11);
			}
			// if numPurchased other, set console color to green
			else {
				SetConsoleTextAttribute(hConsole, 10);
			}
			// output fileLine string with a space
			std::cout << fileLine << " ";
			// for numPurchased times, output "+"
			for (int i = 0; i < numPurchased; i++) {
				std::cout << "+";
			}
			// output newline
			std::cout << std::endl;
		}
		// reset console color to default grey
		SetConsoleTextAttribute(hConsole, 7);
		// if while loop fails without being end of file, report error
		if (!frequency.eof()) {
			std::cout << "Input error before end of file" << std::endl;
		}
	}

	// close frequency.dat file
	frequency.close();
}

// Gets user's choice of options regarding grocery list and calls corresponding functions
void listOptions() {

	// userChoice string holds user's input from 1-4
	string userChoice = "";
	// userItem string holds user's grocery item choice
	string userItem = "";

	// ask for user input and call functions while userChoice isn't "4"
	do {
		// output user's available choices and descriptions
		std::cout << "Enter the number corresponding to your choice" << std::endl;
		std::cout << "1: Full Grocery List With Number of Times Purchased" << std::endl;
		std::cout << "2: Specific Item's Number of Times Purchased" << std::endl;
		std::cout << "3: Histogram of Grocery List With Number of Times Purchased" << std::endl;
		std::cout << "4: Exit Program" << std::endl;
		// store user's choice in userChoice string
		std::getline(cin, userChoice);

		// if user chooses option 1, call Python "OpenList" function with "" parameter to list grocery items and quantity purchased
		if (userChoice == "1") {
			callIntFunc("OpenList", "");
			std::cout << std::endl;
		}
		// if user chooses option 2, call Python "OpenList" function with userItem parameter to list that item's purchased quantity
		else if (userChoice == "2") {
			std::cout << "Enter the grocery item to count" << std::endl;
			std::getline(cin, userItem);
			callIntFunc("OpenList", userItem);
			std::cout << std::endl;
		}
		// if user chooses option 3, call Python "OpenList" function with "\n\n" parameter to create frequency.dat file of grocery list
		else if (userChoice == "3") {
			callIntFunc("OpenList", "\n\n");
			histogramReader();
		}
		// if user chooses option 4, break loop and end program
		else if (userChoice == "4") {
			break;
		}
		// if user chooses otherwise, output error
		else {
			std::cout << "Improper selection. Try again." << std::endl;
		}
	} while (userChoice != "4");
}

void main()
{
	// function to receive user's choice of options regarding the grocery list
	listOptions();
	
}