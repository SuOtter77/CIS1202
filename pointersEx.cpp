// This is a SAMPLE program
// NOT FOR SUBMISSION
// If submitted, it is a mistake
#include <iostream>
#include <string>
using namespace std;

int main() {
    int num = 24;
    cout << "The number is " << num << endl;

    //use the reference operator to find the primitive variable's memory address 

    cout << "It's memory address is " << &num << endl;

    
    int* intPtr = nullptr;  //I'M MAKING A VARIABLE THAT WILL ONLY STORE MEMORY ADDRESSES
    float* floatPtr = nullptr;

    intPtr = &num; //the PTR is now equal the the memory address of num

    cout << "The memory address is " << intPtr;
    *intPtr *= 2;
    cout << "\nThe number is " << *intPtr;   //let's look at the value stored in that memory address

    /*why??
        use one variable for all occurances of int = easier coding and less memory
        dynamic memory allocation (allocate memory for arrays based upon USER's input)
        More efficient method of passing arrays and strings to functions

    */

    //DYNAMIC MEMORY ALLOCATION = ALLOCATING A NEW DATA STRUCTURE OBJECT AT THE TIME IT'S NEEDED
    cout << "\n\nHow many pets in your house? ";
    int nbrPets = 0;
    cin >> nbrPets;

    intPtr = new int[nbrPets]; //since ptrs automatically store memory address of first element of data structures
    //we can dynamically allocate a new data structure using the user's input
    if (intPtr == nullptr) {
        cout << "\nError: cannot allocate memory!";
    }
    else cout << "\nMemory allocated successfully";

    //now to save memory, delete your pointer to an array when no longer needed.
    //release (free) the memory!  
    delete[] intPtr;

    cout << "\n\nHow many pets in your house? ";
    int nbrNoPets = 0;
    cin >> nbrNoPets;

    intPtr = new int[nbrNoPets]; //since ptrs automatically store memory address of first element of data structure
    // intPtr points to an anonymous array 

    //we can dynamically allocate a new data structure using the user's input
    if (intPtr == nullptr) {
        cout << "\nError: cannot allocate memory!";
    }
    else cout << "\nMemory allocated successfully";

    //populate the array
    for (int i = 0; i < nbrPets; i++) {
        intPtr[i] = nbrNoPets += 4 + 2;
    }

    //display it
    for (int i = 0; i < nbrPets; i++) {
        cout << "\n" << intPtr[i];
    }

    //send to swap function to swap values in elements 2 and 3
    swap(*(intPtr+2), *(intPtr+1));

    //display
    for (int i = 0; i < nbrPets; i++) {
        cout << "\n\n\n" << intPtr[i];
    }
    return 0;
}
