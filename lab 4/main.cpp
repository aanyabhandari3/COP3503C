#include <iostream>
#include <vector>
#include "extrafile.h"
using namespace std;

int main() {
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    vector<Ship> friendlyShips;
    vector<Ship> enemyShips;

    switch (option) {
        case 1:
            friendlyShips = loadShipsFromFile("friendlyships.shp");
            break;
        case 2:
            enemyShips = loadShipsFromFile("enemyships.shp");
            break;
        case 3:
            friendlyShips = loadShipsFromFile("friendlyships.shp");
            enemyShips = loadShipsFromFile("enemyships.shp");
            break;
        default:
            cerr << "Invalid option" << endl;
            return 1;
    }

    vector<Ship> allShips = friendlyShips;
    allShips.insert(allShips.end(), enemyShips.begin(), enemyShips.end());

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;

    cin >> option;

    switch (option) {
        case 1:
            for (size_t i = 0; i < allShips.size(); ++i) {
                printShip(allShips[i], i == allShips.size() - 1);
            }
            break;
        case 2: {
            Ship strongestWeaponShip = findShipWithStrongestWeapon(allShips);
            if (!strongestWeaponShip.name.empty()) {
                printShip(strongestWeaponShip, true);
            } else {
                cout << "No ships with weapons found." << endl;
            }
            break;
        }
        case 3: {
            Ship strongestOverallShip = findStrongestShipOverall(allShips);
            if (!strongestOverallShip.name.empty()) {
                printShip(strongestOverallShip, true);
            } else {
                cout << "No ships found." << endl;
            }
            break;
        }
        case 4: {
            Ship weakestShip = findWeakestShipIgnoringUnarmed(allShips);
            if (!weakestShip.name.empty()) {
                printShip(weakestShip, true);
            } else {
                cout << "No armed ships found." << endl;
            }
            break;
        }
        case 5:
            printUnarmedShips(allShips);
            break;
        default:
            cerr << "Invalid option" << endl;
            return 1;
    }

    return 0;
}