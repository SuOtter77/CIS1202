// Augustus Gullett
// CIS 1202 501
// 3 November 2024
#include <iostream>	// general io
#include <fstream> // file stream io
#include <cstring>
using namespace std;

// structures
struct Product {
	long number;
	char name[40]; // outside of this, arrays are not allowed
	double price;
	int quantity;
};

// prototypes
int showMenu();
void createFile(fstream&);
void displayFile(fstream&);
void displayRecord(fstream&, int);
void modifyRecord(fstream&);

int main() {
	// menu
	int choice = -1; 
	int index = 0;
	fstream starter("inventory.dat", ios::out | ios::binary);
	// open file
	createFile(starter);
	fstream file("inventory.dat", ios::in | ios::out | ios::binary);
	//fstream file("inventory.dat", ios::in | ios::out | ios::binary);
	// loop while 
	do { // intentionally skipping at first
		switch (choice) {
		case 1: // Display inventory
			displayFile(file);
			break;
		case 2: // Display a product
			//int index = 0;
			cout << "Enter a record number:"; // replace max index after testing
			while (!(cin >> index) || index < 0 || index > 10) {
				cout << "Enter a record number:"; // retry until valid
			}
			displayRecord(file, index);
			break; // prevent fallthrough
		case 3:	// Modify a product
			modifyRecord(file);
			break;
		}
		choice = showMenu();
	} while (choice != 4); // have to use this structure to ensure it immediately stops after an exit command is received.
	file.close(); // close on exit or on fail
	return 0;
}

int showMenu() {
	int choice = 4; // default quit, but quickly changed by user input
	cout << "1. Display entire inventory" << endl;
	cout << "2. Display a product" << endl;
	cout << "3. Modify a product" << endl;
	cout << "4. Exit program" << endl;
	cout << "Choice: #";
	while (!(cin >> choice) || choice < 1 || choice > 4) {
		cout << "Retry: #";
	}
	cout << endl;
	return choice; // validated choice
}

void createFile(fstream& file) {
	// called once to populate the file
	for (int i = 0; i < 10; i++) {
		Product temp;
		temp.number = 101;
		strcpy_s(temp.name, 40, "Cookie variety");
		temp.price = 1.27;
		temp.quantity = 4;
		file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	}
	file.close();
}
void displayFile(fstream& file) {
	if (file.eof()) {
		file.clear();
	}
	file.seekg(0, ios::beg); //start

	Product temp;
	int index = 0;
	cout << index << endl;
	while (!file.bad() && index < 10) {
		file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		cout << "Record " << index << endl;
		cout << "Product number: #" << temp.number << endl;
		cout << "Product name: " << temp.name << endl;
		cout << "Price: $" << temp.price << endl;
		cout << "Quantity: " << temp.quantity << endl;
		cout << '\n';
		index++;
	}
	if (file.bad()) {
		cout << "File may be unreadable" << endl;
	}
}
void displayRecord(fstream& file, int index) {
	file.clear(); // reset EOF flag
	Product tempProduct;
	file.seekg(index * sizeof(tempProduct), ios::beg); //start
	for (int i = 0; i < index; i++) {
		file.read(reinterpret_cast<char*>(&tempProduct), sizeof(tempProduct));
	}
	file.read(reinterpret_cast<char*>(&tempProduct), sizeof(tempProduct)); // wizardry
	cout << "Record" << endl;
	cout << "Name " << tempProduct.name << endl;
	cout << "Number #" << tempProduct.number << endl;
	cout << "Price $" << tempProduct.price << endl;
	cout << "Quantity" << tempProduct.quantity << endl;
	cout << endl;
	
}
void modifyRecord(fstream& file) {
	file.clear(); // clear EOF state
	file.seekg(0, ios::beg); // go to start
	
	// collect index
	int index = 0;
	Product temp;
	cout << "Enter product index: ";
	while (!(cin >> index) || index < 0 || index > 10) {
		cout << "Enter valid index:";
	}
	cout << endl;

	//modify it
	cout << "New product number: ";
	cin >> temp.number;
	cout << "New product name: ";
	cin.ignore();
	cin.getline(temp.name, 40); // getline adds \0, hopefully
	cout << endl << "New price $";
	cin >> temp.price;
	cout << "New quantity ";
	cin >> temp.quantity;
	file.seekp(index * sizeof(temp), ios::beg); // go to the index
	file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	cout << endl;
}