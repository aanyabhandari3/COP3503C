#ifndef EXTRAFILE_H
#define EXTRAFILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Weapon {
    string name;
    int powerRating;
    float powerConsumption;
};

struct Ship {
    string name;
    string shipClass;
    unsigned short length;
    unsigned int shieldCapacity;
    float warpSpeed;
    vector<Weapon> weapons;
    int totalFirepower() const;
};

string readString(ifstream &file);
Ship readShip(ifstream &file);
vector<Ship> loadShipsFromFile(const string &filename);
void printShip(const Ship &ship, bool isLastShip);
Ship findShipWithStrongestWeapon(const vector<Ship> &ships);
Ship findStrongestShipOverall(const vector<Ship> &ships);
Ship findWeakestShipIgnoringUnarmed(const vector<Ship> &ships);
void printUnarmedShips(const vector<Ship> &ships);

#endif