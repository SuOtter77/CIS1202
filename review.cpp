// Augustus Gullett
// CIS 1202 section 501; C++ Review
// 9/1/2024

#include <string>
#include <iostream> // printing to terminal
#include <fstream> // reading file
#include <iomanip> // for limiting decimal places
using namespace std;

// prototypes
void loadArrays(string[], int[], float[], int&);
void calculateValues(int[], float[], float[], int);
void displayTable(string[], int[], float[], float[], int);

// functions
int main() {
	const int SIZE = 20;
	int count = SIZE;
	// variables
	string product[SIZE];
	int quantity[SIZE];
	float cost[SIZE];
	float value[SIZE]; // equals quantity x cost
	// apparently very important to remember that these are paassed as pointers to functions.

	loadArrays(product, quantity, cost, count);
	calculateValues(quantity, cost, value, count);
	displayTable(product, quantity, cost, value, count);

	return 0;
}

void loadArrays(string products[], int quantities[], float costs[], int &count) {
	const int SIZE = count; //sneak size in without redefining
	const int lenRow = 3;
	string data[lenRow];
	count = 0; //reset count
	char delimiter = ' ';
	// load from file stream
	string filename = "Inventory.txt";
	fstream file(filename, ios::in);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}
	for (int i = 0; i < SIZE && file.good(); ++i) {
		//cout << "looping";
		// only loop while file stream is open and EOF has not been reached
			string line;
			getline(file, line);
			//cout << "Line : " << line << endl;
			int j = 0;
			int g = 0;
			// process the delimiters... very tedious.
			string placeholder = "";
			while (j < line.length()+1 && g < lenRow && line.length() > 1) {
				if (line[j] == delimiter or j >line.length()-1) { // guard clause
					data[g] = placeholder;
					//cout << "Placeholder" << placeholder << endl;
					placeholder = "";
					j++;
					g++;
					continue; // skip this round
				}
				//cout << "Pushing " << line[j] << endl;
				placeholder.push_back(line[j]);
				j++;
			}
			//cout << "Listing data" << endl;
			// append data for each line
			for (int i = 0; i < 3; i++) {
				//cout << " data: " << data[i] << endl;
			}
			string strint = data[1];
			string strflt = data[2];
			products[i] = data[0];
			quantities[i] = stoi(strint);
			costs[i] = stof(strflt);
		count = i;
	}
	file.close();
}

void calculateValues(int quantities[], float costs[], float values[], int count) {
	for (int i = 0; i < count; i++) {
		// assign the product of quantity and cost to the value
		values[i] = quantities[i] * costs[i];
	}
}

void displayTable(string products[], int quantities[], float costs[], float values[], int count) {
	float sum = 0.0;
	string item = "";
	float max = 0.0;
	
	// print values with setprecision and setw
	cout << setw(18) << "Product code";
	cout << setw(18) << "Qty on Hand";
	cout << setw(18) << "Cost each";
	cout << setw(18) << "Total value" << endl;
	for (int i = 0; i < count; i++) {
		cout << setw(14) << products[i];
		cout << setw(14) << quantities[i];
		cout << setw(14) << "$" /*<< setprecision(2)*/ << costs[i];
		cout << setw(14) << "$" /*<< setprecision(2) */<< values[i];
		if (values[i] > 9000) {
			cout << " !!"; // indicator if over $9000 value
		}
		cout << endl;
		sum += costs[i];
		if (values[i] > max) {
			item = products[i];
			max = values[i];
		}
	}
	float average = sum / count;
	cout << endl << "The product with the highest inventory value was " << item << endl;
	cout << "The average cost of an inventory item was " << setprecision(2) << average << endl;
}