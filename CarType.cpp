#include "CarType.h"
#include <stdexcept>

EconomCar::EconomCar() : Car() {}

EconomCar::EconomCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage)
    : Car(brand, model, type, year, mileage) {}

double EconomCar::calculate_price(const double& distance) {
    if (distance <= 0) {
        throw std::invalid_argument("Write correct distance.");
    }
    return distance * 2.0;
}

std::unique_ptr<Car> EconomCar::clone() const {
    return std::make_unique<EconomCar>(*this);
}


ComfortCar::ComfortCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage)
    : Car(brand, model, type, year, mileage) {}

double ComfortCar::calculate_price(const double& distance) {
    if (distance <= 0) {
        throw std::invalid_argument("Write correct distance.");
    }
    return distance * 3.5;
}

std::unique_ptr<Car> ComfortCar::clone() const {
    return std::make_unique<ComfortCar>(*this);
}


BusinessCar::BusinessCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage)
    : Car(brand, model, type, year, mileage) {}

double BusinessCar::calculate_price(const double& distance) {
    if (distance <= 0) {
        throw std::invalid_argument("Write correct distance.");
    }
    return distance * 5.0;
}

std::unique_ptr<Car> BusinessCar::clone() const {
    return std::make_unique<BusinessCar>(*this);
}
