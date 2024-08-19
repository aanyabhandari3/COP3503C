#include "extrafile.h"
#include <limits> 
#include <algorithm> 

int Ship::totalFirepower() const {
    int firepower = 0;
    for (const auto &weapon : weapons) {
        firepower += weapon.powerRating;
    }
    return firepower;
}

string readString(ifstream &file) {
    unsigned int length;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));

    if (file.fail()) {
        cerr << "Error reading string length from file." << endl;
        return "";
    }

    char* buffer = new(nothrow) char[length];
    if (!buffer) {
        cerr << "Memory allocation failed for length: " << length << endl;
        return "";
    }

    file.read(buffer, length);
    if (file.fail()) {
        cerr << "Error reading string from file." << endl;
        delete[] buffer;
        return "";
    }

    string result(buffer);
    delete[] buffer;
    return result;
}

Ship readShip(ifstream &file) {
    Ship ship;
    
    ship.name = readString(file);
    ship.shipClass = readString(file);

    file.read(reinterpret_cast<char*>(&ship.length), sizeof(ship.length));
    file.read(reinterpret_cast<char*>(&ship.shieldCapacity), sizeof(ship.shieldCapacity));
    file.read(reinterpret_cast<char*>(&ship.warpSpeed), sizeof(ship.warpSpeed));

    unsigned int weaponCount;
    file.read(reinterpret_cast<char*>(&weaponCount), sizeof(weaponCount));
    
    for (unsigned int i = 0; i < weaponCount; ++i) {
        Weapon weapon;
        weapon.name = readString(file);
        file.read(reinterpret_cast<char*>(&weapon.powerRating), sizeof(weapon.powerRating));
        file.read(reinterpret_cast<char*>(&weapon.powerConsumption), sizeof(weapon.powerConsumption));
        ship.weapons.push_back(weapon);
    }

    return ship;
}

vector<Ship> loadShipsFromFile(const string &filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return {};
    }

    vector<Ship> ships;
    
    unsigned int shipCount;
    file.read(reinterpret_cast<char*>(&shipCount), sizeof(shipCount));

    for (unsigned int i = 0; i < shipCount; ++i) {
        ships.push_back(readShip(file));
    }

    file.close();
    return ships;
}

void printShip(const Ship &ship, bool isLastShip) {
    cout << "Name: " << ship.name << endl;
    cout << "Class: " << ship.shipClass << endl;
    cout << "Length: " << ship.length << endl;
    cout << "Shield capacity: " << ship.shieldCapacity << endl;
    cout << "Maximum Warp: " << ship.warpSpeed << endl;
    cout << "Armaments: ";
    if (ship.weapons.empty()) {
        cout << "Unarmed" << endl;
    } else {
        cout << endl;
        for (const auto &weapon : ship.weapons) {
            cout << weapon.name << ", " << weapon.powerRating << ", " << weapon.powerConsumption << endl;
        }
        cout << "Total firepower: " << ship.totalFirepower() << endl;
    }
    if (!isLastShip) {
        cout << endl;
    }
}

Ship findShipWithStrongestWeapon(const vector<Ship> &ships) {
    Ship strongestShip;
    int maxWeaponPower = numeric_limits<int>::min();

    for (const auto &ship : ships) {
        for (const auto &weapon : ship.weapons) {
            if (weapon.powerRating > maxWeaponPower) {
                maxWeaponPower = weapon.powerRating;
                strongestShip = ship;
            }
        }
    }

    return strongestShip;
}

Ship findStrongestShipOverall(const vector<Ship> &ships) {
    return *max_element(ships.begin(), ships.end(), [](const Ship &a, const Ship &b) {
        return a.totalFirepower() < b.totalFirepower();
    });
}

Ship findWeakestShipIgnoringUnarmed(const vector<Ship> &ships) {
    Ship weakestShip;
    int minFirepower = numeric_limits<int>::max();

    for (const auto &ship : ships) {
        if (!ship.weapons.empty() && ship.totalFirepower() < minFirepower) {
            minFirepower = ship.totalFirepower();
            weakestShip = ship;
        }
    }

    return weakestShip;
}

void printUnarmedShips(const vector<Ship> &ships) {
    for (const auto &ship : ships) {
        if (ship.weapons.empty()) {
            printShip(ship, false);
        }
    }
}