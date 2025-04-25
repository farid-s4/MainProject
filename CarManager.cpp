#include "CarManager.h"

CarManager::CarManager() : cars(){}
CarManager::CarManager(std::vector<Car*> cars) : cars(cars){}
CarManager::CarManager(const CarManager& other) : cars(other.cars) {}
CarManager& CarManager::operator=(const CarManager& other) 
{
    if (this != &other)
    {
        cars = other.cars;
        return *this;
    }
    return *this;
}
CarManager::CarManager(CarManager&& other) noexcept : cars(std::move(other.cars)) {}
CarManager& CarManager::operator=(CarManager&& other) noexcept
{
    if (this != &other)
    {
        cars = std::move(other.cars);
        return *this;
    }
    return *this;
}

void CarManager::redact_car(unsigned int index, std::string brand, std::string model, std::string type, unsigned short year, unsigned int mileage)
{
    if (index < cars.size())
    {
        cars[index]->update_car_info(brand, model, type, year, mileage);
    }
    
}
bool CarManager::maintence(int index)
{
    if (index < cars.size())
    {
        if (cars[index]->maintence())
        {
            return true;
        }
        
    }
    return false;
}
