// Augustus Gullett
// CIS 1202.501
// 11/8/2024

#include <iostream>
#include <string>
#include "Publication.h"

using namespace std;

// implementations

void Publication::storePublication(string itemTitle, string itemPublisher, double itemPrice, int itemYear, PublicationType itemType, int itemStock) {
    title = itemTitle;
    publisher = itemPublisher;
    price = itemPrice;
    year = itemYear;
    type = itemType;
    stock = itemStock;// why does this function exist? So this is why I made the publication vars private.
}

void Publication::displayInfo() {
	// Displays all variables, but never called. Why?
	cout << "Title: " << title << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Price: $" << price << endl;
    cout << "Year: " << year << endl;
    cout << "Type: ";
    switch (type) { // thanks c++ for throwing out the enum names...
    case BOOK:
        cout << "Book" << endl;
        break; // prevent fallthrough
    case MAGAZINE:
        cout << "Magazine" << endl;
        break;
    case NEWSPAPER:
        cout << "Newspaper" << endl;
        break;
    case AUDIO:
        cout << "Audio" << endl;
        break;
    case VIDEO:
        cout << "Video" << endl;
        break;
    }
    cout << "Stock: " << stock << endl;
}
void Publication::checkOut() {
	if (stock > 0) {
		stock--; // self explanatory
	}
	else {
		cout << "None left!" << endl;
	}
}
void Publication::checkIn() {
	stock++;// self explanatory
}
string Publication::getTitle() {
	return title;// self explanatory
}
int Publication::getStock() {
	return stock;// ... take the private variable "stock" and return it
}