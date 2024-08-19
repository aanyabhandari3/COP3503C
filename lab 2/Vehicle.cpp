#include "Vehicle.h"
#include <iostream>
#include <string>

using namespace std;

//Define default constructor
Vehicle::Vehicle() {
    this->make = "COP3503";
    this->model = "Rust Bucket";
    this->year = 1900;
    this->price = 0;
    this->mileage = 0;
}

//define parameterized constructor
Vehicle::Vehicle(std::string make, std::string model, int year, float price, int mileage) {
    this->make = make;
    this->model = model;
    this->year = year;
    this->price = price;
    this->mileage = mileage;
}

//display function
void Vehicle::Display() const {
    std::cout<<year<<" "<<make<<" "<<model<<" "<<"$"<<price<<" "<<mileage<<std::endl;
}

//getter function
std::string Vehicle::GetYearMakeModel() const{
    std::string info = to_string(year) + " "+ make + " " + model;
    return info;
}

float Vehicle::GetPrice() const {
    return price;
}