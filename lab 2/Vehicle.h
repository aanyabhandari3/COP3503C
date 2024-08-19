#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>
#include <iostream>

//declared a class Vehicle
class Vehicle {
private:
    // declaring private members of the class
    std::string make;
    std::string model;
    unsigned int year;
    float price;
    unsigned int mileage;
public:
    // declaring a default constructor
    Vehicle();
    // declaring a parameterized constructor
    Vehicle(std::string make, std::string model, int year, float price, int mileage);
    
    void Display() const;
    std::string GetYearMakeModel() const;
    float GetPrice() const;
};
#endif