// Augustus Gullett
// 12-15-2024
// CIS 1202.501
// Warehouse inventory program

#include "Warehouse.h"
#include <iostream>
#include <fstream>
using namespace std;

int getChoice();
int getWhole();

// Documentation
// Run the program and maybe press enter if Visual Studio is pretending to debug again. Usually this is unneeded.
// Enter options as needed
// Don't overload the input buffer when you're asked for a price or number. Simple enough, right? Type a normal number and not 939393939939393939393939393939399i393939393i39393ii3i3iiiiii
// Exit by typing 5 so your data gets saved into the binary file.

int main() {
	int place = -1;
	int wanted_ID;
	int input = 0;
	int curNumberItems = 0;
	int tempNum;
	int maxIndex;
	double total;
	double price;
	const int arrSize = 8; // small for demonstration purposes
	item Items[arrSize]; // anything beyond 25 is insane for this.
	// User will work with a warehouse inventory to get or set an Item derived from Inventory
	ifstream ifile("inv.bin", ios::binary);
	if (ifile.good()) {
		// read it
		item tempItem{};
		for (int i = 0; i < arrSize; i++) {
			ifile.read((char*)&Items[i], sizeof(tempItem));
			double curPriceHeuristic = Items[i].getPrice();
			if (!ifile.bad() && curPriceHeuristic > 0) {
				Items[i];
				curNumberItems += 1; // this is not ++
			}
			else if (Items[i].getPrice() < 0)
				break;
		}
		
		
	}
	if (ifile.is_open()) {
		ifile.close();
		// maybe do something?
	}

	// main loop
	do {
		cout << "1: View existing inventory\n2: Add to inventory\n3: Remove from inventory\n4: Calculate average pricing.\n5. Exit" << endl;
		input = getChoice();
		switch (input) {
		case 1:
			// view ( loop over Items and .display() each one )
			//for (i in range(items.length)) this is what c++/python does to me
			if (curNumberItems == 0)
				cout << "Nothing to display!" << endl;
			for (int i = 0; i < curNumberItems; i++) {
				Items[i].display();
			}
			break;
		case 2:
			// add (input function)
			if (curNumberItems == arrSize) {
				cout << "Sorry, no more items can be added" << endl;
				break;
			}
			tempNum;
			cout << "Number of items to input: #";
			cin >> tempNum;
			maxIndex = min(curNumberItems + tempNum, arrSize); // reduce to the maximum space, if necessary
			cout << "You will be adding #" << maxIndex - curNumberItems << "items" << endl;
			for (int i = curNumberItems; i < maxIndex; i++) { // curNumberItems is one greater than the filled index, so... it IS an empty index
				item myItem = item();
				myItem.input();
				Items[i] = myItem;
				curNumberItems++;
			}
			break;
		case 3:
			// remove ID (linear search and destroy)
			place = -1;
			cout << "Please enter an ID to delete: ";
			wanted_ID = getWhole();
			for (int i = 0; i < curNumberItems; i++) {
				if (Items[i].getID() == wanted_ID) {
					place = i;
					break;
				}
			}
			if (place == -1) {
				cout << "That ID doesn't exist in our inventory." << endl;
			}
			else {
				for (int i = place; i < curNumberItems - 1; i++) {
					Items[i] = Items[i + 1];
				}
				Items[curNumberItems - 1] = item(); // empty Item
				curNumberItems--;
				cout << "Removed " << wanted_ID << endl << endl;
			}
			break;
		case 4:
			// display the average price
			// ceil each price
			// lround the result
			cout << "Calculating averages" << endl;
			total = 0.0;
			for (int i = 0; i < curNumberItems; i++) {
				price = ceil(Items[i].getPrice());
				total += price;
			}
			cout << "The rounded average price is $" << lround(total / curNumberItems) << endl << endl;
		}

	} while (input != 5); // continue until user exits

	ofstream ofile("inv.bin", ios::binary);
	if (ofile && curNumberItems > 0) {
		for (int i = 0; i < curNumberItems; i++) {
			ofile.write((char*)&Items[i], sizeof(Items[i]));
		}
	}// write it
	else
		cout << "Failed to write" << endl;
	ofile.close();
	return 0;
}

int getChoice() {
	int choice;
	cout << "Select #";
	while (!(cin >> choice) || choice < 1 || choice > 5) {
		cout << "Retry: #";
	}
	cout << endl;
	return choice; // validated choice
}

int getWhole() {
	int num;
	while (!(cin >> num) || num < 1) {
		cout << "Retry: #"; // make sure it's a whole number
	}
	cout << endl;
	return num;
}