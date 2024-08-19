#include "Dealership.h"
#include <iostream>
#include <string>

using namespace std;

//Define default constructor
Dealership::Dealership() {
    this->name_Dealership = "Generic Dealership";
    this->capacity = 0;
}

//define parameterized constructor
Dealership::Dealership(std::string name_Dealership, unsigned int capacity) {
    this->name_Dealership = name_Dealership;
    this->capacity = capacity;
}


//behaviors
void Dealership::AddShowroom(const Showroom& s) {
    if (showrooms.size() < capacity) {
        showrooms.push_back(s);
    } else {
        std::cout<<"Dealership is full, can't add another showroom!"<<std::endl;
    }
}
float Dealership::GetAveragePrice() const {
    float total = 0.0f;
    int size = 0;
    for (const auto& Showroom : showrooms){
        total += Showroom.GetInventoryValue();
        size += Showroom.GetVehicleList().size();
    }
    float average = total/size;
    return average;
}
void Dealership::ShowInventory() const {
    float price = GetAveragePrice();
    if (showrooms.size() == 0){
        std::cout<<name_Dealership<<" is empty!"<<endl;
        std::cout<<"Average car price: $0.00";
    } else{
        for (const auto& Showroom : showrooms){
            Showroom.ShowInventory();
            std::cout<<endl;
        }
        std::cout<<"Average car price: $"<<price;

    }
}