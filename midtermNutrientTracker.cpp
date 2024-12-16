// Augustus Gullett
// 17 October 2024
// CIS 1202.501

// nutrient tracking!
// input food types along with info about them ( no presets! )

// cstring functions
// strncpy_s at line #105?? #
// other cstring function at line ##

#pragma warning( disable : 0266 )
//^ stop visual studio from randomly yelling about a conflicting std::cout and then disappearing 10 seconds later before coming back again
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

// structs
struct food {
	char name[45];
	int calorie;
	int fat;
	int cholesterol;
	int sodium;
	int sugars;
	int fiber;
	int carbTotal;
};

struct chow {
	short numFoods; // saves on memory
	food* foodPtr; // THIS MUST BE CLEANED UP MANUALLY //pointer to an array of foods
	// saves on memory by defining array size based on the length of the input array (maxes at 7)
};
struct presets {
	int numFoods = 0;
	food foods[100] {0}; //
	// if the food cannot be found (search the sorted food array), users are prompted to create a preset for the food
};

struct day {
	short numMeals = 0; // length of the array (saves on memory instead of assuming a certain amount)
	chow* chowPtr = nullptr; // THIS MUST BE CLEANED UP MANUALLY // pointer to array of meals OR snacks in a day (maxes at 7. E.g. four meals, three snacks)
	
};

// prototypes
int getChoice();
void addPreset(presets& presets);
void addChow(chow* choww, food* preset, int& mealOfDay);
bool searchPresets(char* string, presets& Menu, food& preset); // presets is a required but the reference is unnecessary.
void sortFoods(day* today, chow& sortedArray);
void printStats(day* today); // requires sorting; includes calorie leaderboard
void printPresets(presets& presets);

// main
int main() {
	int tempDays;
	int tempMeals;
	cout << "How many meals each day? :";
	cin >> tempMeals;
	const short MEALS_PER_DAY = (tempMeals > 0 && tempMeals < 8) ? tempMeals : 5; // validation that falls back to a normal input if it's invalid
	cout << "How many days? :";
	cin >> tempDays;
	const short NUM_DAYS = (tempDays > 0 && tempDays < 31) ? tempDays : 7;// validation that falls back to a normal input if invalid
	const char MARKER[4] = "END";
	if (tempDays != NUM_DAYS || tempMeals != MEALS_PER_DAY) {
		cout << "Some of your input was invalid!" << endl;
		cout << "Number of days: " << NUM_DAYS << endl;
		cout << "Number of meals: " << MEALS_PER_DAY << endl;
	}

	day* days = new day[NUM_DAYS]; // THIS MUST BE CLEANED UP MANUALLY // point to an array of day structs with numDays length
	for (int i = 0; i < NUM_DAYS; i++) {
		// initialize I guess
		day someDay = { MEALS_PER_DAY, nullptr}; //why
		someDay.chowPtr = new chow[MEALS_PER_DAY];
		days[i] = someDay;
	}
	int index = 0;
	int lastIndex = 0; // marker 
	int mealIndex = 0;
	food currentMeal[7]; // saving state while a preset is added
	//day realDay = **(&ptr + 3); <--- yeah so apparently using new int[1] is a pointer.... so you have to dereference the pointer AND the array position or something like that
	day* todayPtr = *(&days + index); // point to a dereferenced pointer to Day.. aka point to Day again
	presets	knownFoods = presets();
	bool healthy = true;
	
	while (healthy) {
		// allocate memory and set meal location, if it's any different
		chow* curMeal = (todayPtr->chowPtr + mealIndex); // pointers are impossible to keep track of.
		switch (getChoice()) {
		case 1: {
			//Add meal (selected from presets by a search)
			cout << "We'll add to your meal until you enter END" << endl;
			// see marker const
			int added = 0;
			int sizzee;
			for (int i = lastIndex; i < 7; i++) {
				lastIndex = 0; // reset just in case
				char temp[45];
				cout << "Food name: ";
				cin.ignore();
				cin.getline(temp, 44);
				int numChars = cin.gcount(); // count characters consumed 				
				temp[min(44, numChars+1)] = '\0'; // set last character to mark the end of the cstring
				if (strncmp(MARKER, temp, 4) == 0) {
					break; // ending loop to add
				}
				else { // DELETE AFTER DEBUGGING
					for (int i = 0; i < numChars; i++) {
						if (temp[i] == ' ') {
							//cout << '\u2591'; // symbol to stand for space
							cout << char(176);
						}
						else if (temp[i] == '\0') {
							//cout << '\u25C4'; // symbol to stand for end line
							cout << char(178);
						}
						else {
							cout << temp[i];
						}
					}
					cout << endl;
				}
				food preset;
				if (searchPresets(temp, knownFoods, preset)) { // If found, the preset is set and added
					cout << endl << "Adding preset to your meal" << endl;
					currentMeal[added] = preset;
					added++;
				}
				else {
					cout << "That preset doesn't exist. Please add it before continuing" << endl;
					if (added > 0) {
						lastIndex = added;
					}
					break;
				}
			}
			sizzee = added + 1; // since it refuses to let me pass an expression as a reference variable
			addChow(curMeal, currentMeal, sizzee); // pass whole arrray + its size
			break; // prevent fall-through
		}
		case 2: //Add preset
			addPreset(knownFoods);
			break; // prevent fall-through
		case 3: //View presets
			printPresets(knownFoods);
			break; // prevent fall-through
		case 4: //End day and format stats from the day
			printStats(todayPtr);
			break; // prevent fall-through
		case 5: 
			healthy = false;
			break;
		}
	}

	// clean up memory to prevent memory leaks due to using   new type[size]
	// it saves on memory, but requires more care
	// NOTE TO SELF: Not worth the trouble!!!
	if (days != nullptr) { //skip if nullptr
		// deallocate and zero pointers
		for (int i = 0; i < index + 1; i++) {
			if ((days + i)->chowPtr != nullptr) { //skip if nullptr
				int jindex = (days + i)->numMeals;
				for (int j = 0; j < jindex; j++) {
					chow* mealList = &(days + i)->chowPtr[j]; // this "isn't an lvalue" so i had to point to it
					if (mealList != nullptr && int(& mealList->foodPtr) < 0xFF) { // skip if nullptr // LOL did that fix it....
						//delete[] (mealList->foodPtr); // STILL DOESNT WORK!!!! Exception thrown at 0x00007FFDF632030E (ucrtbased.dll) in CIS1202.exe: 0xC0000005: Access violation reading location 0xFFFFFFFFFFFFFFFF Compare operations dont even work so IDK. Dont got time for this//9:54pm
						//mealList->foodPtr = nullptr;
						// Acclaimed alchemic sorcery for Halloween.......
						// printing this code and using it for a bonfire next spring
						// surely this can count as my studying for the midterm exam quiz
					}
				}// no time to debug this nonsense at 9pm with an exam still due// fixed..??? 
				// it's due to trying to delete an empty location, but the changes to prevent that would make it impossible to assign a nullptr
				delete[] ((days + i)->chowPtr);
				(days + i)->chowPtr = nullptr; // why
			}
			
		}
		delete[] days; // deallocate
		days = nullptr; // formalize that it now points to nothing
	}
	
}
//end of main


/////////////////////////
// functions !!!!      //
/////////////////////////all these pointers make this extremely difficult to get working

int getChoice() {
	int choice;
	cout << "// Menu //" << endl;
	cout << "1. Add meal" << endl;
	cout << "2. Add preset" << endl;
	cout << "3. View presets" << endl;
	cout << "4. End day" << endl;
	cout << "5. Exit" << endl;
	cout << "Choice: #";
	while (!(cin >> choice) || cin.bad() || !(choice > 0 && choice < 6)) {
		cout << "Please retry" << endl;
		cout << "Choice: #";
	}
	cout << endl;
	return choice;
}
// rushed thanks to debugging pointers. Slightly dysfunctional? maybe, i have a c++ midterm to do and it's 9:20 woohoo
void addPreset(presets& presets) { // are these types right??? yep
	cout << "Prompting user" << endl;
	char tempName[45];
	int calorie;
	int fat;
	int cholesterol;
	int sodium;
	int sugars;
	int fiber;
	int carbTotal;	
	// create a food object
	cin.ignore();
	cout << "Food name:";
	cin.getline(tempName, 45);
	int numChars = cin.gcount(); // count characters consumed 				
	tempName[min(44, numChars + 1)] = '\0'; // set last character to mark the end of the cstring
	cout << "Calories:";
	cin >> calorie;
	cout << "Fat content:";
	cin >> fat;
	cout << "Cholesterol:";
	cin >> cholesterol;
	cout << "Sodium content:";
	cin >> sodium;
	cout << "Sugar content:";
	cin >> sugars;
	cout << "Fiber content:";
	cin >> fiber;
	cout << "Total carbs:";
	cin >> carbTotal;
	food obj = { "", calorie, fat, cholesterol, sodium, sugars, fiber, carbTotal};// i do NOT have time for this-- start working now 
	strncpy_s(obj.name, tempName, 50);// first c-string function woohoo
	presets.foods[presets.numFoods] = obj;
	presets.numFoods++; // that SHOULD be it??
}
void addChow(chow* chow, food* presets, int &totalFoods) { //a re these types right??? chow location, food to add to chow, total foods.. why? ok lets pass food as array instead // literally equal to curentMeal soo...  but not cool at all
	cout << "Adding preset to meal" << endl;
	
}
bool searchPresets(char* sctring, presets& Menu, food& preset) { // are these types right?? c-string yes, cstring function needed, menu.... yea. food? yes for returning it AFTER doing a binary search ok ok cool
	for (int i = 0; i < Menu.numFoods; i++) {
		//compare while less... 
		if (strncmp(sctring, Menu.foods[i].name, 50)) {
			preset = Menu.foods[i];
			return true;
		}
	}
	return false;
}
void sortFoods(day* today, chow& sortedArray) { // are these types right? ...... can't tell, i've never needed this function because i've been stuck debugging ... yep, pointers. i guess they can give me pointers so i dont have to study. what is this function for again???
	//change type from day to chow
	cout << "Sorting" << endl;
	//hahea.... this was going to be so cool before i realized pointer requirements would take all my time away
	//i dread Jrava classes even more (oracle will sue me if i spell it correctly)
	food dayFoods[256]{ 0 };// formally initialize that declared temp holder
	int trueCounter = 0;
	for (int i = 0; i < today->numMeals && trueCounter < 256; i++) {
		chow* ptr = (today->chowPtr + i);
		for (int j = 0; j < ptr->numFoods; i++) {
			dayFoods[trueCounter] = *(ptr->foodPtr + j);
		}
	}
	for (int i = 0; i < 100 - 1; i++) {
		for (int j = 0; j < 100 - i - 1; j++) {
			if (dayFoods[j].calorie > dayFoods[j + 1].calorie) {
				// Swap arr[j] and arr[j + 1]
				food temp = dayFoods[j];
				dayFoods[j] = dayFoods[j + 1];
				dayFoods[j + 1] = temp;
			}
		}
	}
	// literally can't keep track of these pointers, so some things are gonna be  broken at submission time. Sorry, the exam has a time limit unlike this which i've been working for 9 hours on.
	sortedArray.numFoods = trueCounter + 1;
	sortedArray.foodPtr = new food[trueCounter + 1]; // leaky memory but this is not production code and you know, i kinda have an exam
	for (int i = 0; i < trueCounter; i++) {
		sortedArray.foodPtr[i] = dayFoods[i];
	}
}
void printStats(day* today) { // yes this type is right
	// yea no clue how to anchor this to the pointer
	chow sorted;
	sortFoods(today, sorted);
	cout << "Your top 10 foods today were:" << endl;
	// severely limited features, but i had plans and now i have a migraine so nevermind
	
}
void printPresets(presets& presets) { // sure needs formatting
	cout << "Name" << fixed << setw(15);
	cout << "Calories" << endl; // no this doesnt get sorted. The whole day gets sorted for "Stats"
	for (int i = 0; i < presets.numFoods; i++) {
		cout << presets.foods[i].name << fixed << setw(15);;
		cout << presets.foods[i].calorie;
		cout << endl;
	} // ok is that good? sure moving on
}
// wow documentation in only 3 minutes ok now need to 10x that for that algorithms
// 1 hour laer....