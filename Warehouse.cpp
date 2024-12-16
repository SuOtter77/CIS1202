/// Augustus Gullett
// 12-15-2024
// CIS 1202.501
// warehouse.h implementations
#include "Warehouse.h"
#include <cstring>
#include <iostream>
using namespace std;

// Base class implementations
/*warehouseProduct::warehouseProduct() {
	company = "";

}*/
char* warehouseProduct::getCompany() {
	return company;
}
void warehouseProduct::setCompany(char companyC[30]) {
	strcpy_s(company, 30, companyC);
}
char* warehouseProduct::getProduct() {
	return productName;
}
void warehouseProduct::setProduct(char product[45]) {
	strcpy_s(productName, 45, product);
}
int warehouseProduct::getStock() {
	return stock;
}
void warehouseProduct::setStock(int stockC) {
	stock = stockC;
}
void warehouseProduct::display() {
	cout << "Warehouse Product" << endl;
	cout << "Company: " << getCompany() << endl;
	cout << "Product: " << getProduct() << endl;
	cout << "Stock: " << getStock() << endl;
}

// Derived class implementations
/*item::item() : warehouseProduct::warehouseProduct() {

}*/
int item::getID() {
	return productID;
}
double item::getPrice() {
	return price;
}
void item::setID(int id) {
	productID = id;
}
void item::setPrice(int priceC) {
	price = static_cast<double>(priceC);
}
void item::setPrice(float priceC) {
	price = static_cast<double>(priceC);
}
void item::setPrice(double priceC) {
	price = static_cast<double>(priceC);
}
void item::display() {
	warehouseProduct::display();
	cout << "ID: " << getID() << endl;
	cout << "Pricing: $" << getPrice() << endl;
}
void item::input() {
	int totalll;
	cin.ignore();
	cout << "Company: ";
	char tempStr[100];
	cin.getline(tempStr, 29);
	totalll = cin.gcount();
	tempStr[totalll] = '\0';
	warehouseProduct::setCompany(tempStr);
	cout << "Product name: ";
	cin.getline(tempStr, 44);
	totalll = cin.gcount();
	tempStr[totalll] = '\0'; // right after last char
	warehouseProduct::setProduct(tempStr);
	cout << "Product ID (int): ";
	int tempi;
	while (!(cin >> tempi) || tempi < 1) {
		cout << "Retry: $";
	};
	setID(tempi);
	cout << "Product price: $";
	double tempdb;
	while (!(cin >> tempdb) || tempdb < 0.01) {
		cout << "Retry: $";
	}
	setPrice(tempdb);
	cout << "Product stock: ";
	int stock;
	while (!(cin >> stock) || stock < 0) {
		cout << "Retry: $";
	}
	setStock(stock);
}