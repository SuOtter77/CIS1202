// Augustus Gullett
// CIS 1202.501
// 11/24/2024
#include "Publication.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void getPublicationInfo(Publication&);
void getPublications(Publication[], int&);
void showPublications(Publication[], int);
void showTitles(Publication[], int);
int findPublication(Publication[], int, string);
int getMenuChoice();

int main() {
    const short numPublication = 8;
    Publication publications[numPublication];
    // I've learned it is too difficult to dynamically utilize "new Publication[size]"
    int actualSize;
    getPublications(publications, actualSize); // read input file
    short choice; // declared here so the while loop can use it
    Publication curPub; // current publication
    do {
        // apparently Main is supposed to display the menu here.
        cout << "1. Display all publications\n2. Display publication titles\n3. Find a publication\n4. Check out\n5. Check in\n6. Exit" << endl;
        string input;
        int locatioin;
        choice = getMenuChoice(); // get user choice for the menu
        switch (choice) {
        case 1: 
            showPublications(publications, actualSize);
            break;
        case 2: 
            showTitles(publications, actualSize);
            break;
        case 3:
            cin.ignore();
            cout << "Get from title: ";
            getline(cin, input);
            locatioin = findPublication(publications, actualSize, input);
            if (locatioin != -1)
                publications[locatioin].displayInfo();
            break;
        case 4:
            // check-iout//
            cin.ignore();
            cout << "Get from title: ";
            getline(cin, input);
            locatioin = findPublication(publications, actualSize, input);
            if (locatioin != -1) {
                publications[locatioin].checkOut();
                cout << "Stock: " << publications[locatioin].getStock() << endl;
            }
            break;
        case 5:
            // check-in
            cin.ignore(); // i aspire to ban c++i aspire to ban c++i aspire to ban c++i aspire to ban c++i aspire to ban c++
            cout << "Get from title: ";
            getline(cin, input);
            locatioin = findPublication(publications, actualSize, input); // using int in the theoretical case that the array is hundreds of publications long or something
            if (locatioin != -1) {
                publications[locatioin].checkIn();
                cout << "Stock: " << publications[locatioin].getStock() << endl;
            }
            break;
        }
    } while (choice != 6);
    return 0;
}

// copy, although it'll never be used here
void getPublicationInfo(Publication& publication) {
    string title = "";//silence C26495
    string publisher = "";//silence C26495 
    PublicationType type = BOOK; //silence C26495 // why did i write that
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

void getPublications(Publication arr[], int& count) {
    // with open('file.ext') is better than fstream file("file.ext")
    fstream pubFile("11publications.txt");
    // temp publication vars
    string tempTitle, tempPublisher;
    int tempType;
    int tempYear;
    float tempStock;//static_cast to int
    float tempPrice;
    int i = 0;
    while (pubFile.good()) {
        // OK THIS DID NOT WORK OUT. wheres getline ??? // hahha still broke // fixed/???
        // which person put a float as the stock amount :)....
        getline(pubFile, tempTitle);//... am i good
        getline(pubFile, tempPublisher); // i actually put this after the price.... :(((
        //pubFile.ignore(); // please work c++ htis isnt cool\
        //pubFile >> tempPublisher;
        pubFile >> tempPrice; // not sure if there's a faster way to do this. Wait that might work // nevermind, reading directly won't coerce the types from str to int
        pubFile >> tempYear;
        pubFile >> tempType; // Why do C++ and C# exist when we have C supporting entire kernels
        pubFile >> tempStock;// after this, getline breaks?!?!?
        pubFile.ignore();
        arr[i].storePublication(tempTitle, tempPublisher, tempPrice, tempYear, static_cast<PublicationType>(tempType), static_cast<int>(tempStock));
        i++;
        // Ok, but this will surely error if the file ever gets truncated.
        // Why no class solely on error handling and advanced debugging instead?
        // Am I secretly being influenced to switch to game development? Haha
        // Would we need Rust if we were first taught optimization? I wonder
    }
    pubFile.close();
    count = i;
}
void showPublications(Publication arr[], int count) {
    // complaint: C++ requires too much effort to individually test functions
    // I end up only finding out at runtime that I messed up something obscure
    for (int i = 0; i < count; i++) {
        // I have to re-learn Python syntax every week haha :(
        arr[i].displayInfo();
    }
}
void showTitles(Publication arr[], int count) {
    // Dreading debugging
    // Get-Process self.soliloquy | Stop-Process
    // ERR: Permission deniSuccess. 4th wall break: this is a play on c-strings and reading out of bounds, sorry if it's not funny
    //SSBhcG9sb2dpemUgZm9y
    for (int i = 0; i < count; i++) {
        cout << arr[i].getTitle() << endl;
    } // IGdldHRpbmcg
}
int findPublication(Publication arr[], int count, string name) {
    // ZGlzdHJhY3RlZCBzbyBtdWNo
    for (int i = 0; i < count; i++) {
        if (arr[i].getTitle() == name)
            return i; //000000
    }
    // We (me, myself, and i) interrupt this message to encourage the reader to listen to K-Pop\0
    cout << "Couldn't find" << endl;
    return -1;
}
int getMenuChoice() {
    int choice;
    cout << "Select #";
    while (!(cin >> choice) || choice < 1 || choice > 6) {
        cout << "Retry: #";
    }
    cout << endl;
    return choice;
}