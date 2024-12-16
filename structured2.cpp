// Augustus Gullett
// 13 October 2024
// CIS 1202.501
#include <iostream>
#include <string>

using namespace std;

// Enums
enum suits { HEARTS, DIAMONDS, SPADES, CLUBS };
enum ranks { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Structs
struct cards {
    suits suit;
    ranks rank;
};

// Functional prototypes
void createDeck(cards deck[]);
void printDeck(cards deck[]);
string cardName(cards card);
cards deal(cards deck[]);
string winner(cards card1, cards card2);

int main() {
    srand(time(0)); // obtain the actual randomness. Ugh.
    // originally i was rushing to finish this, but then it hit 12:00 so... now i get to tell you what all of this does
    cards deck[52];
    createDeck(deck);
    cards card1 = deal(deck);
    cards card2 = deal(deck); // randomly select it :l
    cout << "Entire Deck:" << endl; // double so we have spacing
    printDeck(deck);
    cout << endl; // spacing :l
    cout << "Card 1: " << cardName(card1) << endl;
    cout << "Card 2: " << cardName(card2) << endl;
    cout << "Woohoo! " << winner(card1, card2) << endl;
    return 0;
}

void createDeck(cards deck[]) {
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck[index].suit = static_cast<suits>(i);
            deck[index].rank = static_cast<ranks>(j); // essentially converting into the enum value at that location
            index++;
        }
    }
}

void printDeck(cards deck[]) {
    for (int i = 0; i < 52; i++) {
        cout << cardName(deck[i]) << endl;
    }
}

string cardName(cards card) {
    const string rankNames[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
    const string suitNames[] = { "Hearts", "Diamonds", "Spades", "Clubs" }; // cause it's painful using the actual enums
    string catName = rankNames[card.rank] + " of " + suitNames[card.suit]; // conCATenation
    return catName;
}

cards deal(cards deck[]) {
    int index = rand() % 52; // random... hopefully!!!
    return deck[index];
}

string winner(cards card1, cards card2) {
    // return a winning message! Orrr a tie message....
    if (card1.rank > card2.rank) {
        return cardName(card1) + " won!!"; // where's the reward?!?!
    }
    else if (card1.rank < card2.rank) {
        return cardName(card2) + " won!?"; // this is unexpected!
    }
    else {
        return "It's a tie! :o";
    } // adding a little personality since it's 15mins late anywayss...
}
