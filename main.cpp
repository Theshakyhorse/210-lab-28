// COMSC-210 | Lab 28 | Alexander Sierra
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20, W = 15;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;
    int choice;
    set<Goat> goats;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    cout << setw(W) << "*** GOAT MANAGER 3001***" << endl;
    choice = main_menu();
    //loop to keep program going until user quits
    while (choice != 5) {
        if (choice == 1) {
            add_goat(goats, names, colors);
        }
        if (choice == 2) {
            delete_goat(goats);
        }
        if (choice == 3) {
            display_trip(goats);
        }
        if (choice == 4) {
            goats.clear();
        }
        choice = main_menu();
    }
    return 0;
}

int main_menu() {
    int choice;
    //outputs options and asks user to decide
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Clear list of goats" << endl;
    cout << "[5] Quit" << endl;
    cout << "Choice --> ";
    cin >> choice;
    cout << endl;
    //validates
    while ((choice < 0) || (choice > 5)) {
        cout << "Please choose a valid choice: " << endl;
        cin >> choice;
        cout << endl;
    }
    return choice;
}

//adds a goat w/ random age, name, and color
void add_goat(set<Goat> &trip, string names[SZ_NAMES], string colors[SZ_COLORS]) {
    int age = rand() % (MAX_AGE+1);
    int c = rand () % SZ_COLORS;
    int n = rand () % SZ_NAMES;
    string name = names[n];
    string color = colors[c];
    Goat temp = Goat(name, age, color);
    trip.insert(temp);
}

//deletes a goat user selected
void delete_goat(set<Goat> &trip) {
    int choice = select_goat(trip);
    int i = 1;
    for (auto it = trip.begin(); it != trip.end();) {
        if (choice == i) {
            it = trip.erase(it);
        } 
        else {
            ++it;
        }
        ++i;
    }   
    
}

//user selects a goat
int select_goat (set<Goat> trip) {
    int choice;
    int i = 1;
    //outputs options and asks user to decide
    for (Goat g : trip) {
        cout << setw(W) << "[" << i << "] " << g.get_name() << " (";
        cout << g.get_age() << ", " << g.get_color() << ")" << endl;
        ++i;
    }
    cout << setw(W) << "Choice --> ";
    cin >> choice;
    cout << endl;
    //validates
    while ((choice < 1) || (choice >= i)) {
        cout << "Please choose a valid choice between 1 and " << i-1 << endl;
        cin >> choice;
        cout << endl;
    }
    return choice;
}

//outputs goats list
void display_trip (set<Goat> trip) {
    for (Goat g : trip) {
        cout << setw(W) << g.get_name() << " (";
        cout << g.get_age() << ", " << g.get_color() << ")" << endl;
    }
    cout << endl;
}