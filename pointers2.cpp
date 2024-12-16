// Augustus Gullett
// CIS 1202.501
// 22 September 2024
#include <iostream>
#include <iomanip>
using namespace std;

int getMenuItem();
void enterRents(float*, int);
void displayRents(float*, int);
float sumRents(float*, int);
void displayMemoryLocations(float*, int);
void selectionSort(float*, int);

int main() {
	float* rentPtr = nullptr; // point to 0 first
	const int size = 7; // not dynamic in this assignment
	int choice; // so we don't have have redundant case 6;

	do {
		choice = getMenuItem();
		switch (choice) {
		case 1:
			if (rentPtr != nullptr) {
				cout << "You've already entered data. It will be overwritten." << endl;
			}
			rentPtr = new float[size]; // assign it a memory location
			enterRents(rentPtr, size);
			cout << endl;
			break;
		case 2:
			displayRents(rentPtr, size);
			cout << endl;
			break;
		case 3:
			selectionSort(rentPtr, size);
			cout << endl;
			break;
		case 4:
			cout << "The sum is $" << fixed << setprecision(2) << sumRents(rentPtr, size) << endl;
			cout << endl;
			break;
		case 5:
			displayMemoryLocations(rentPtr, size);
			cout << endl;
			break;
		// Exit condition covered by loop
		}
	} while (choice != 6);
}

int getMenuItem() {
	int numTry = 0;
	int choice;
	cout << "1. Enter rent amounts" << endl;
	cout << "2. Display rents" << endl;
	cout << "3. Sort rent amounts; low to high" << endl;
	cout << "4. Calculate the total rents" << endl;
	cout << "5. Display memory locations" << endl;
	cout << "6. Exit" << endl;
	do {
		cout << "Select #";
		cin >> choice;
		numTry++;
	} while ((choice < 1 || choice > 6 || cin.fail()) && numTry < 5); // validate the whole thing
	if (numTry > 4) {
		cout << "Possible infinite loop. Quitting" << endl;
		return 6; // satisfy condition to stop main loop and exit program.
	}
	return choice;
}

void enterRents(float* ptr, int size) {
	float temp = 0.0; // To prevent invalid datatypes
	for (int i = 0; i < size; i++) {
		cout << "\tRent #" << i + 1 << ". ";
		do {
			cin >> temp;
		} while (cin.fail() || temp < 0); // just repeat if the input is invalid
		*(ptr+i) = temp;
		// i wanted to do (&ptr + i) = &temp but it didn't work
	}
}

void displayRents(float* ptr, int size) {
	if (ptr == nullptr) {
		cout << "No address assigned to pointer." << endl;
		return; // again, simply exit early
	}
	cout << "Rents" << endl;
	for (int i = 0; i < size; i++) {
		cout << "$ " << fixed << setprecision(2) << *(ptr + i) << endl;
	}

}

float sumRents(float* ptr, int size) {
	if (ptr == nullptr) {
		cout << "No address assigned to pointer." << endl;
		return 0.0; // again, simply exit early
	}
	float sum = 0;
	for (int i = 0; i < size; i++) {
		sum += *(ptr + i);
	}
	return sum;
}


void displayMemoryLocations(float* ptr, int size) {
	if (ptr == nullptr) {
		cout << "No address assigned to pointer." << endl;
		return; // again, simply exit early
	}
	cout << "The memory address are" << endl;
	for (int i = 0; i < size; i++) {
		cout << i << ". " << (&ptr + i) << endl;
	}
}

void selectionSort(float* ptr, int size) {
	if (ptr == nullptr) {
		cout << "No address assigned to pointer." << endl;
		return; // again, simply exit early
	}
	cout << "Sorting" << endl;
	for (int i = 0; i < size - 1; i++) { 
		int smallest = i;
		for (int j = i + 1; j < size; j++) {
			if (*(ptr + j) < *(ptr + smallest)) {
				smallest = j;
			}
		}
		if (smallest != i) {
			swap(*(ptr + smallest), *(ptr + i));
			// swap them. It's really annoying that I have to dereference the pointers to swap them.
		}
	}
}