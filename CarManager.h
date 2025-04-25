#pragma once
#include <vector>
#include "Car.h"
class CarManager
{
private:
    std::vector<Car*> cars;
public:
    CarManager();
    CarManager(std::vector<Car*> cars);
    CarManager(const CarManager& other);
    CarManager& operator=(const CarManager& other);
    CarManager(CarManager&& other) noexcept;
    CarManager& operator=(CarManager&& other) noexcept;

    void redact_car(unsigned int index, std::string brand, std::string model, std::string type, unsigned short year, unsigned int mileage);

    bool maintence(int index);
};