// Augustus Gullett
// CIS 1202 501
// September 3, 2024

// Professor's feedback
//-.5 With > 3 options, a switch is a better selection structure.  
//-.5 case 5 in the switch is redundant as the exit condition is while choice!=5.  
//-2 No attempt made to validate user has entered an appropriate number.  
//-2 program does not exit if the file doesn't open, causing the program to continue to attempt to run.
// -1 Lookup doesn't exit once item is found, leading to unnecessary processing time. 
// 
// while centering is cute, a simple left command for the console name, and right for the prices works perfect ;)
// you are correct cin.ignore doesn't fix any letters causing integer overflow. That's why using cin >> choice outside 
// a while loop is not desirable.  while (!(cin >> choice) || cin.fail() || or choice <1 || choice >5 works perfectly here..
// May correct for higher grade.


// As noted in my email, lookup exits once found.
// My Corrections
// Exits if file won't open
// Changed exit condition to while (choice != 5) and removed the redundant case 5
// Yes, centering is quite cute.

#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Function prototypes
void loadArrays(string[], float[], int &);
void showArrays(string[], float[], int);
void lookUpPrice(string[], float[], int);
void sortPrices(string[], float[], int);
void highestPrice(string[], float[], int);
int showMenu();

int main() {
	const int SIZE = 20;
	int count = SIZE; // temporary number of items
	string consoles[SIZE];
	float prices[SIZE];
	loadArrays(consoles, prices, count);
	int errCount = 0;
	int choice;
	do {
		choice = showMenu();
		switch (choice) {
		case 1:
			cout << "Displaying all prices" << endl;
			showArrays(consoles, prices, count);
			cout << endl;
			break;
		case 2:
			cout << "Look up the price of a console" << endl;
			lookUpPrice(consoles, prices, count);
			cout << endl;
			break;
		case 3:
			cout << "Sort prices in descending order" << endl;
			sortPrices(consoles, prices, count);
			cout << endl;
			break;
		case 4:
			cout << "Display the most expensive console" << endl;
			highestPrice(consoles, prices, count);
			cout << endl;
			break;
		// removed now-redundant case 5
		default:
			if (choice == -858993460) {
				cout << "Congrats! The choice integer has overflowed. Exiting to prevent infinite loop." << endl;
				choice = 5; // satisfy new exit condition
			}
			break; // if still invalid despite showMenu validation, 
		}
	} while (choice != 5); //
}

// Functions
void loadArrays(string consoles[], float prices[], 
	int& count) {
	fstream file("02prices.txt", ios::in);
	// Check if file is bad
	if (file.bad()) {
		cout << "File won't open" << endl;
		cout << "Shutting down" << endl;
		exit(1);
	}
	int i = 0;
	// FIX ME
	while (i < count && file.peek() != EOF) {
		// this will take two lines per iteration.
		// without consuming the stream, it checks if a new iteration will hit EOF
		getline(file, consoles[i]); // Get the full name of the console
		file >> prices[i]; // grab the price next
		file.ignore(); // literally just consume the newline that >> skips over
		i++;
	}
	count = i;
	/*for (int i = 0; i < count && file.peek() != EOF; i++) {
	Deleted to access 'I' outside of the loop
	}*/
}

void showArrays(string consoles[], float prices[],
	int count) {
	// pretty printed arrays
	cout << setw(20) << "Console" << setw(19) << "Price" << endl;
	for (int i = 0; i < count; i++) {
		int conLen = consoles[i].length();
		int width = 16 + floor(conLen / 2); // this took so long! It's centered!!!!!
		cout << setw(width) << consoles[i];
		cout << setw(35-width) << "$" << fixed << setprecision(2) << prices[i] << endl;
		// i have nothing to say about this
	}
}

void lookUpPrice(string consoles[], float prices[],
	int count) {
	int j;
	bool found = false;
	string name;
	for (int i = 0; i < count; i++) {
		cout << consoles[i] << ", ";
	} // display the consoless as a list
	cout << endl << "Console name: ";
	getline(cin, name);
	for (int i = 0; i < count; i++) {
		// a hashmap would be way better, probably
		if (name == consoles[i]) {
			cout << name << " costs " << "$" << fixed << setprecision(2) << prices[i] << endl;
			found = true;
			break;
		}
	}
	if (!found) {
		cout << name << " was not found in our inventory" << endl;
		// for larger arrays, you would first use a bloom filter to check if it's in the array first.
		// from there, a hashmap would enable you to jump to its data structure.
	}
	
}

void sortPrices(string consoles[], float prices[],
	int count) {
	//./ Bubble sort
	for (int max = count - 1; max > 0; max--) {
		for (int i = 0; i < max; i++) {
			if (prices[i] < prices[i + 1]) {
				swap(prices[i], prices[i + 1]);
				swap(consoles[i], consoles[i + 1]);
			} // irreversible action!
		}
	}
	// even if we use insertion sort, the consoles/prices arrays would have to be updated to reflect the change
	// So, bubble sort is fastest especially as the arrays get larger.
}

void highestPrice(string consoles[], float prices[],
	int count) {
	int index = count-1;
	for (int i = 0; i < count; i++) {
		if (prices[i] > prices[index]) {
			index = i; // slower because we cannot assume the list is sorted yet
		}
	}
	cout << consoles[index] << " was the most expensive console at $" << prices[index] << endl;
}

int showMenu() {
	cout << "1. Display consoles and their prices." << endl;
	cout << "2. Look up the price of a console." << endl;
	cout << "3. Sort prices in descending order." << endl;
	cout << "4. Display the highest priced console." << endl;
	cout << "5. Exit progarm." << endl;

	int choice;
	do {
		cout << "Choice: #";
		cin >> choice;
		cout << endl;
	} while (choice < 1 || choice > 5 || cin.fail()); // Corrected to add validation

	return choice; // entering any letters will cause integer overflow on the next cin input. Cin ignore doesn't fix this.
}