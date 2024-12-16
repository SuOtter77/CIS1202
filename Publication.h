#pragma once // why is this here visual studio?
#ifndef PUB_HEADER // header guard
#define PUB_HEADER // define that it's been loaded already, i think
#include <string> // so it doesn't yell at us
enum PublicationType {BOOK, MAGAZINE, NEWSPAPER, AUDIO, VIDEO};

class Publication {
private: 
	// member variables defined as private for clarity and necessity, 
	// since they should be accessed by the functions only
	std::string title;
	std::string publisher;
	float price;
	int year;
	PublicationType type;
	int stock;
public:
	// accessible functions
	void storePublication(std::string itemTitle, std::string itemPublisher, double itemPrice, int itemYear, PublicationType itemType, int itemStock);
	void displayInfo();
	void checkOut();
	void checkIn();
	std::string getTitle();
	int getStock();
};

#endif // end of header, skips if already defined


// Random thought. It's likely that Rust will slowly fall out of favor if hardware memory tagging becomes popularized.
// However, it's still likely to be used in high security applications that can't just trust the kernel
// Moreover, the ecosystem and error approach of Rust is very liked. It's possible that other critical bugs are prevented by Rust's compilation checks.
// These kind of tradeoffs are important in modern development. Rust development can end up being a lot slower than C or Cpython, anyways.
// I'm going to gravitate to using Golang... and ZigLang if its ecosystem improves