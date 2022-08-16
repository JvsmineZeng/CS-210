#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;


/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}


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
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
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


/**
 * The printMenu function prints a menu for prompting user input.
 */
void printMenu() {
	cout << " --------------------------------------------------------" << endl;			// Divider
	cout << "|           CORNER GROCER INVENTORY SOFTWARE              |" << endl;			// Header
	cout << "|                                                         |" << endl;
	cout << "|  1: Generate an itemized list of today's purchases      |" << endl;			// Choice 1
	cout << "|  2: Generate the quantity sold of a given item today    |" << endl;			// Choice 2
	cout << "|  3: Generate a histogram of today's purchases           |" << endl;			// Choice 3
	cout << "|  4: Exit                                                |" << endl;			// Choice 4
	cout << "|                                                         |" << endl;
	cout << "|  Enter your selection as a number 1, 2, 3, or 4.        |" << endl;			// Print valid menu choices
	cout << " --------------------------------------------------------" << endl;			// Divider
}


/**
 * The itemLookup function looks for an item per user request. Then, it calls Python function findQuantitySold and prints the according sales information
 * for the day.
 */
void itemLookup() {
	
	string itemSearch;
	int quantitySold;

	cout << "Which item are you looking for?" << endl;						// Prompt user to enter item search inquiry
	cin >> itemSearch;														// Get item search

	quantitySold = callIntFunc("findQuantitySold", itemSearch);	// Set quantitySold to int value returned by called Py function findQuantitySold

	if (quantitySold == 0) {												// If quantitySold is 0
		cout << "No " << itemSearch << " were sold today." << endl;			// Notify user none of their item sold for the day
	}
	else {																			// If quantitySold is not 0
		cout << quantitySold << " " << itemSearch << " were sold today." << endl;	// Notify user quantity of their item sold for the day
	}

}


/**
 * The printHistogram method calls Python function buildHistogram and uses data file frequency.dat to generate a histogram representation of itemized sales
 * for the day.
 */
void printHistogram() {

	ifstream salesData;
	string item;
	int quantity;

	CallProcedure("buildHistogram");		// Call Py function buildHistogram

	salesData.open("frequency.dat");	// Open frequency.dat file
	salesData >> item;							// Get item name
	salesData >> quantity;						// Get quantity sold

	cout << " ------------------------------" << endl;			// Divider
	cout << "|     TOTAL INVENTORY SOLD     |" << endl;			// Print header
	cout << " ------------------------------" << endl;			// Divider
	cout << endl;												// Print space
	cout << left << setw(15) << "    ITEM" << left << "  QUANTITY SOLD" << endl;	// Print header
	cout << "------------   -----------------" << endl;			// Divider

	while (!salesData.fail()) {					// While file contains remaining data
		cout << left << setw(15) << item;		// Print item
		for (int i = 0; i < quantity; i++) {	// For each single digit increment from 0 until quantity sold
			cout << left << "*";				// Print an asterisk
		}
		cout << endl;							// Print space
		salesData >> item;						// Get next item name
		salesData >> quantity;					// Get next quantity sold
	}

	cout << endl;								// Print space

	salesData.close();							// Close frequency.dat file

}


/**
 * The runMenu method runs the menu and program according to user input while user does not choose to exit.
 */
void runMenu() {

	int userChoice;

	do {																				

		printMenu();											// Call printMenu method													

		try {													// Try

			cin >> userChoice;									// Get userChoice				

			if (userChoice > 4 || userChoice < 1) {				// If userChoice is not between 1 and 4 inclusive		
				throw runtime_error("ERROR");					// Print error message
			}

			switch (userChoice) {								// userChoice decision branching								
			case 1:												// Choice 1
				system("cls");							// Clear screen
				CallProcedure("organizeItemsSold");		// Call Python method organizeItemsSold
				system("pause");							// Prompt user to enter any key to continue
				system("cls");							// Clear screen
				break;											// Break				
			case 2:												// Choice 2				
				system("cls");							// Clear screen
				itemLookup();									// Call itemLookup method
				system("pause");							// Prompt user to enter any key to continue
				system("cls");							// Clear screen
				break;											// Break			
			case 3:												// Choice 3
				system("cls");							// Clear screen
				printHistogram();								// Call printHistogram method
				system("pause");							// Prompt user to enter any key to continue
				system("cls");							// Clear screen
				break;											// Break
			case 4:												// Choice 4			
				system("cls");							// Clear screen		
				cout << "Thank you for using Corner Grocer's inventory software!" << endl;		// Print goodbye message
				break;											// Break					
			}
		}

		catch (runtime_error& exception) {							// If user choice is not between 1 and 4 inclusive
			system("cls");									// Clear screen
			cout << exception.what() << endl;						// Identify exception
			cout << "Input must be 1, 2, 3, or 4." << endl;			// Print error message
			system("pause");									// Prompt user to enter any key to continue
			system("cls");									// Clear screen
		}

	} while (userChoice != 4);										// End do loop; do while user menu choice is not 4

}


/**
 * The main method calls the runMenu method.
 */
void main() {
	runMenu();		// Call runMenu method
}