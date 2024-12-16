// Augustus Gullett
// CIS 1202.501
// 15 September 2024
#include <iostream>
using namespace std;

int getMenuItem();
void enterRents(float[], int);
void displayRents(float*, int);
void displayMemoryLocations(float[], int);
void selectionSort(float[], int);

int main() {
	float* rentPtr = nullptr; // new int[count]
	const int size = 5; // default size
	float rents[size]; //required for entering rents... not really
	while (true) {
		switch (getMenuItem()) {
			case 1: 
				cout << "Enter rent prices" << endl;
				enterRents(rents, size);
				rentPtr = rents; // sets ptr to   rents + 0   aka	&rents[0]
				cout << endl;
				break;
			case 2: 
				cout << "Displaying rent prices" << endl;
				displayRents(rentPtr, size);
				cout << endl;
				break;
			case 3: 
				cout << "Sorting rent prices in ascending order" << endl;
				selectionSort(rents, size); // sorts in place
				cout << endl;
				break;
			case 4:
				cout << "Displaying memory locations" << endl;
				displayMemoryLocations(rentPtr, size);
				cout << endl;
				break;
			case 5: 
				exit(0);
			default:
				cout << "Congrats! You made something impossible happen" << endl;
				exit(1); 
				// In case someone modifies the memory directly;
				// Normally, this would be impossible because of input validation;
				// In a game, you might have a second variable with the previous value to verify % changes :))
		}
	}
	
	return 0;
}

int getMenuItem() {
	int attmpt = 0;
	int choice;
	do {
		cout << "1. Enter rent amounts" << endl;
		cout << "2. Display rents" << endl;
		cout << "3. Sort rent amounts; low to high" << endl;
		cout << "4. Display memory locations" << endl;
		cout << "5. Exit" << endl;
		cout << "Select #";
		cin >> choice;
		attmpt++;
	} while ( (choice < 1 || choice > 5) && attmpt < 10); // retry until the choice is valid
	if (attmpt > 9) {
		cout << "Infinite loop detected" << endl;
		exit(1); // quit program if there's an infiniite loop
	}
	return choice;
}

void enterRents(float rents[], int size) {
	//Uses a for loop to input the rent amounts into an array using standard array subscript notation.
	cout << "Input -1 to autofill the rest with zeros." << endl;
	int temp = 0;
	for (int i = 0; i < size; i++) {
		cout << "\tRent " << i + 1 << ". ";
		cin >> temp;
		if (temp == -1) {
			for (int j = i; j < size; j++) {
				cout << "Filling " << j << endl;
				rents[j] = 0; // fill the rest of the array
			}
			break; // exit outer loop
		}
		else {
			rents[i] = temp;
		}
	}
}

void displayRents(float* ptr, int size) {
	//Uses a for loop to display the contents of the rents array using pointers(not subscripts) to access the array elements.
	if (ptr == nullptr) {
		cout << "No address assigned to pointer." << endl;
		return; // exit function
	}
	cout << "Rents" << endl;
	for (int i = 0; i < size; i++) {
		cout << *(ptr + i) /*<< " at " << (&ptr + i) */ << endl; // optionally dipslay the locations to prove it sorted in place for debugging
	}

}

void displayMemoryLocations(float ptr[], int size) { // here, we're passing the pointer *as* the array
	if (ptr == nullptr) {
		cout << "No address assigned to pointer." << endl;
		return; // exit function
	}
	for (int i = 0; i < size; i++) {
		cout << i << ": " << (&ptr + i) << endl;
	} // only need ampersand for clarity

}


void selectionSort(float rents[], int size) {
	for (int i = 0; i < size - 1; i++) { 
		int smallest = i;
		for (int k = i + 1; k < size; k++) {
			if (rents[k] < rents[smallest]) {
				smallest = k;
			}
		}
		if (smallest != i) {
			swap(rents[smallest], rents[i]);
			// swap the lowest valued index this cycle with the current index
		}
	}
}