#ifndef SHOWROOM_H
#define SHOWROOM_H

#include <string>
#include <vector>
#include "Vehicle.h"
#include <iostream>

class Showroom{
private:
    std::string name_Showroom;
    std::vector<Vehicle> vehicles;
    unsigned int capacity;
public:
    Showroom();
    Showroom(std::string name_Showroom, unsigned int capacity);

    std::vector<Vehicle> GetVehicleList() const;

    void AddVehicle(const Vehicle& v);
    void ShowInventory() const;
    float GetInventoryValue() const;
};

#endif