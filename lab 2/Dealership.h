#ifndef DEALERSHIP_H
#define DEALERSHIP_H

#include <string>
#include <vector>
#include "Showroom.h"

class Dealership{
private:
    std::string name_Dealership;
    std::vector<Showroom> showrooms;
    unsigned int capacity;
public:
    Dealership();
    Dealership(std::string name_Dealership, unsigned int capacity);

    void AddShowroom(const Showroom& s);
    float GetAveragePrice() const;
    void ShowInventory() const;
};

#endif