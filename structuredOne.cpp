// Augustus Gullett
// 6 October 2024
// CIS 1202.501
#include <iostream>
#include <string>
using namespace std;

// // The prototypes cannot return a Team or WinLoss if the following structure is anywhere else.
struct Team { 
	struct WinLoss {
		int wins;
		int losses;
	};// "Use nested structures as you develop this program"
	string name; // team name
	WinLoss homeStats;
	WinLoss awayStats;
};
// // function prototypes
int menu();
Team::WinLoss getWinLoss(string);//Because nested structures are required, I have to reference WinLoss as Team::WinLoss
void displayWinLoss(Team::WinLoss);
Team getTeam();
void displayTeam(Team);
void findTeam(Team[], int);



int main() {
	bool healthy = true;
	const int size = 16;
	Team teams[size]; // vectors would make more sense here given the screenshot example, but it says to use an array for whatever reason.
	int totalEle = 0; // can be used as index
	while (healthy) {
		switch (menu()) {
			case 1:
				teams[totalEle] = getTeam();
				totalEle++; // now equal to the next empty element index AND the number of elements
				break;
			case 2:
				cout << "Displaying teams" << endl;
				for (int i = 0; i < totalEle; i++) {
					displayTeam(teams[i]); // display every named team
				}
				break;
			case 3:
				findTeam(teams, totalEle);
				break;
			case 4:
				cout << "Exitting" << endl;
				healthy = false; // exit loop
				break;
			default: 
				cout << "Please restart." << endl;
				healthy = false;
			}
	}
	
	return 0;
}

int menu() {
	int choice;
	cout << "1. Enter a new team\n2. Display all teams\n3. Display a particular team\n4. Exit the program" << endl;
	cout << "#";
	while (!(cin >> choice) || cin.fail() || choice < 1 || choice > 4) {
		cout << "Please re-enter your choice: #";
	}
	return choice;
}

Team::WinLoss getWinLoss(string location) {
	Team::WinLoss tempWinLoss;
	cout << "Enter the " << location << " wins: ";
	cin >> tempWinLoss.wins;
	cout << "Enter the " << location << " losses: ";
	cin >> tempWinLoss.losses;
	return tempWinLoss;
}

void displayWinLoss(Team::WinLoss stats) {
	// called by displayTeam
	cout << stats.wins << "-" << stats.losses << endl;
}

Team getTeam() {
	// adding a team
	Team entry;
	cout << "Team name: ";
	cin.ignore();
	getline(cin, entry.name);
	entry.homeStats = getWinLoss("home");
	entry.awayStats = getWinLoss("away");
	return entry;
}

void displayTeam(Team team) {
	// called by findTeam
	cout << team.name << endl;
	cout << "Home record ";
	displayWinLoss(team.homeStats);
	cout << "Away record ";
	displayWinLoss(team.awayStats);
}

void findTeam(Team teams[], int count) {
	string name;
	bool found = false;
	cout << "Team name:";
	cin.ignore(); // just in case
	getline(cin, name);
	for (int i = 0; i < count; i++) {
		if (teams[i].name == name) {
			// Found!
			found = true;
			displayTeam(teams[i]);
			break; // End loop
		}
	}
	if (!found) {
		cout << "Failed to find " << name << endl;
	}
}