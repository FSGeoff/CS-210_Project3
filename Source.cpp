#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <sstream>



using namespace std;



void CallProcedure(string pName) {

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

int callIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[proc.length() + 1];
	std::strcpy(paramval, proc.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	//Initialize Python Iterpreter
	Py_Initialize();
	//Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	//Load the module object
	pModule = PyImport_Import(pName);
	//pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	//pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);

	if (PyCallable_Check(pFunc)) {

		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {

		PyErr_Print();
	}

	//print("Result as %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	//Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	//Finish the python interpreter
	Py_Finalize();

	//clean
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

int callIntFunc(string proc, int param) {

	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;

	//Initialize python interpreter
	Py_Initialize();
	//Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	//Load the module object
	pModule = PyImport_Import(pName);
	//pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	//pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);

	if (PyCallable_Check(pFunc)) {

		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}

	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	//Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);

	//Finish the python interpreter
	Py_Finalize();

	//clean
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void DisplayMenu() {
	int input{};


	while (input != 4) {
		string item;
		cout << endl << endl << endl;
		cout << "1. Produce a list of items purchased in a given day along with the number of times purchased." << endl;
		cout << "2. produce a number representing how many times a specific item was purchased on a given day." << endl;
		cout << "3. Produce a text-based histogram listing all items purchased on a given day with representation of timnes each item was purchased" << endl;
		cout << "4. Exit the program" << endl << endl;

		cin >> input;

		switch (input) {
		case 1:
			CallProcedure("AllItems");
			break;
		case 2:
			cout << "Please enter a grocery item ";
			cin >> item;
			callIntFunc("SpecificItems", item);
			break;
		case 3:
			CallProcedure("Histogram");
			break;
		}
	}


}



int main() {

	DisplayMenu();

	return 0;