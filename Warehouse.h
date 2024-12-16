#pragma once
#ifndef WAREHOUSE
#define WAREHOUSE

class warehouseProduct {
private:
	char company[30];
	char productName[45];
	int stock;
public:
	//warehouseProduct();
	//warehouseProduct(char company[30], char product[45], int stock);
	char* getCompany();
	void setCompany(char company[30]);
	char* getProduct();
	void setProduct(char product[45]);
	int getStock();
	void setStock(int stock);
	void display();
}; // Normally, i'd do something more advanced with the parent class. However, C++ restricts me a lot more than Python.

class item : public warehouseProduct {
private:
	int productID;
	double price; // supposing there's varying demand, prices may flucuate often
	// This assumes a distributor is paying for the products
	// Caveat: I cannot actually implement this with C++ restrictive classes without a ridiculous amount of void pointers
	// I'm not doing that, so the batchNumber is now the productID
public:
	//item();
	int getID();
	double getPrice();
	void setID(int id);
	void setPrice(int price);
	void setPrice(float price);
	void setPrice(double price);
	void display();
	void input(); // use protected status to use Product setters
};
#endif