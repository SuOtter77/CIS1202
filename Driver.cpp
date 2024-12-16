#include "Publication.h"
#include <iostream>
#include <string>
using namespace std;

void getPublicationInfo(Publication&);

int main() {
    // Driver
    Publication betaPub;
    getPublicationInfo(betaPub); // is this initializing betaPub ????
    cout << betaPub.getTitle() << endl;
    betaPub.checkOut();
    cout << betaPub.getStock() << endl;
    betaPub.checkIn();
    cout << betaPub.getStock() << endl;
    return 0;
}

void getPublicationInfo(Publication& publication) {
    string title = "";//silence C26495
    string publisher = "";//silence C26495 
    PublicationType type = BOOK; //silence C26495
    double price = 0.00;//silence C26495
    int year = 0;
    int stock = 0;//silence C26495

    // self explanatory
    cout << "Enter title: ";
    getline(cin, title);

    cout << "Enter publisher: ";
    getline(cin, publisher);

    cout << "Enter price: $";
    cin >> price;

    cout << "Enter year: ";
    cin >> year;

    cout << "1. Book / 2. Magazine / 3. Newspaper / 4. Audio / 5. Video" << endl;
    cout << "Type: ";
    int temp;
    while (!(cin >> temp) || temp < 1 || temp > 5) {// just check if this is valid
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // great solution!!
        }
        cout << "Retry: "; // retry cin
    }
    type = static_cast<PublicationType>(temp); // we cant cast with an overflowed int. So we have to exit

    cout << "Enter stock: ";
    cin >> stock;

    publication.storePublication(title, publisher, price, year, type, stock); // send it to be added to the object
}