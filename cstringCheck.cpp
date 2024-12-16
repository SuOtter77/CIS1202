//Augustus Gullett
//27 September 2024
//CIS 1202.501

#include <cstring>
#include <iostream>
using namespace std;

bool valid(char[]);
void origin(char[], char[]);
int year(char[]);
// presumably origin() analyzes the first char and inserts the result into the second char
// meanwhile year() decides to return something inside of putting it into a reference var like origin() does.... These are inconsistent design choices.

int main() {
	const int SIZE = 18;
	char vehicleIdenNum[SIZE];// = "1FTRW14W84KC76110"; // one extra character to include the \0 terminator
	bool validity;
	char originHolder[SIZE];
	int yearHolder; // naming convention to signify that these 

	strcpy_s(vehicleIdenNum, "1FTRW14W84KC76110"); // Will abort if the length is larger than the buffer

	//// TESTING BELOW // you *could* rename main and create a new main that calls this function repeatedly
	//char temp[100];
	//cout << "VIN:";
	//cin >> temp;
	//for (int i = 0; i < 17; i++) {
	//	vehicleIdenNum[i] = temp[i];
	//	// basic truncated copy
	//}
	//vehicleIdenNum[17] = '\0'; // note to self: cout will keep printing characters until it finds a null terminator ('\0')... if you don't null-terminate your array, it will just keep going and print whatever garbage is in memory next...
	// TESTING ABOVE //
	
	cout << "Testing the VIN " << vehicleIdenNum << endl;
	validity = valid(vehicleIdenNum);
	if (!validity) { // guard clause
		cout << "VIN is invalid" << endl;
		return 1;
	}

	origin(vehicleIdenNum, originHolder); // assigns
	cout << "Origin: " << originHolder << endl;
	yearHolder = year(vehicleIdenNum); // assigns
	cout << "Year: " << yearHolder << endl;
	return 0;
}

bool valid(char vin[]) {
	// check for I, O, Q, Z, lowercase
	// I can't use regex for this?? :')
	for (int i = 0; i < 17; i++) {//char in vin
		//cout << "DEBUG: Processing " << vin[i] << endl;
		if (vin[i] == '\0') {
			if (i < 17) {
				//cout << "DEBUG: VIN is too short" << endl;
				return false; // VIN is too short
			}
			break; // reached the end
			// without this guard clause, every VIN would be invalid since \0 is not alphanumeric
		}
		if (!isalnum(vin[i]) || (isalpha(vin[i]) && islower(vin[i]))) {
			//cout << "DEBUG: Contained a symbol or a lowerwcase letter" << endl;
			return false;
		}
		else { // otherwise, is the character invalid?
			switch (vin[i]) {
			case 'I': return false;
			case 'O': return false;
			case 'U': return false; // "A VIN never contains the letter U because it looks similar to the letter V."
			case 'Q': return false;
			case 'Z': return false;
			default: break;
				// not worried about fall-through due to the function returning immediately
				// the loop will also stop immediately
			}
		}
	}
	return true; // any invalid characters would have returned false already
	// it is safe to assume all characters have passed validation, which makes this VIN valid.
}

void origin(char vin[], char originReference[]) {
	//cout << "DEBUG: Origin is " << vin[0] << endl;
	
	if (vin[0] <= '5' && vin[0] > 0) {
		strcpy_s(originReference, 16, "North America");
	} // numbers are at a lower index in the ASCII table.
	else if (vin[0] <= '7') {
		strcpy_s(originReference, 16, "Oceania");
	}
	else if (vin[0] <= 9 || vin[0] == 0) {
		strcpy_s(originReference, 16, "South America"); // 8, 9, and... 0 ?! Not cool.
	}
	else if (vin[0] <= 'H') {
		strcpy_s(originReference, 16, "Africa");
	}
	else if (vin[0] <= 'R') {
		strcpy_s(originReference, 16, "Asia");
	}
	else if (vin[0] <= 'Y') {
		strcpy_s(originReference, 16, "Europe");
	}
	else {
		cout << "No match for Origin" << endl;
	}
	return;
}

int year(char vin[]) {
	// here we go again!
	//cout << "DEBUG: Year is at " << vin[9] << endl;
	if (vin[9] >= 'A' && vin[9] <= 'M') {
		return (vin[9] - 'A' + 2010);
	}
	else if (vin[9] >= 'P' && vin[9] <= 'Y') {
		switch (vin[9]) {
		case 'P': return 1993; 
		case 'R': return 1994;
		case 'S': return 1995;
		case 'T': return 1996;
		case 'V': return 1997;
		case 'W': return 1998;
		case 'X': return 1999;
		case 'Y': return 2000;
		}
		//return (vin[9] - 'P' + 1993);
		// use ascii math they said... it'll work fine they said...
	}
	else if (vin[9] >= '1' && vin[9] <= '9') {
		return (vin[9] - '1' + 2001);
	}
	return 0; // Characters '0' and'N' give you year 0
}