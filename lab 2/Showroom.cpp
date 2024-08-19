#include "Showroom.h"
#include <iostream>
#include <string>

using namespace std;

//Define default constructor
Showroom::Showroom() {
    this->name_Showroom = "Unnamed Showroom";
    this->capacity = 0;
}

//define parameterized constructor
Showroom::Showroom(std::string name_Showroom, unsigned int capacity) {
    this->name_Showroom = name_Showroom;
    this->capacity = capacity;
}

//Accessor
std::vector<Vehicle> Showroom::GetVehicleList() const {
    return vehicles;
}

//display function
void Showroom::AddVehicle(const Vehicle& v) {
    if (vehicles.size() < capacity) {
        vehicles.push_back(v);
    } else {
        std::string car = v.GetYearMakeModel();
        std::cout<<"Showroom is full! Cannot add "<<car<<std::endl;
    }
}
void Showroom::ShowInventory() const {
    if (vehicles.size() == 0){
        std::cout<<"Unnamed Showroom is empty!"<<endl;
    } else{
      std::cout<<"Vehicles in "<< name_Showroom <<std::endl;
      for (const auto& Vehicle : vehicles) {
        Vehicle.Display();
    }
  }
}
float Showroom::GetInventoryValue() const {
    float total = 0.0f;
    for (const auto& Vehicle : vehicles) {
        total += Vehicle.GetPrice();
    }
    return total;
}