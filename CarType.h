#pragma once
#include "Car.h"
#include <string>

class EconomCar : public Car
{
public:
    EconomCar();
    EconomCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage);
    double calculate_price(const double& distance) override;
    std::unique_ptr<Car> clone() const override;
};

class ComfortCar : public Car
{
public:
    ComfortCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage);
    double calculate_price(const double& distance) override;
    std::unique_ptr<Car> clone() const override;
};

class BusinessCar : public Car
{
public:
    BusinessCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage);
    double calculate_price(const double& distance) override;
    std::unique_ptr<Car> clone() const override;
};
