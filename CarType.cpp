#include "CarType.h"
#include <stdexcept>  

EconomCar::EconomCar() : Car() {}

EconomCar::EconomCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage)
    : Car(brand, model, type, year, mileage) {}

double EconomCar::calculate_price(const double& distance) {
    if (distance <= 0) {
        throw std::invalid_argument("Write correct distance.");
    }
    double one_km_price = 2.0;
    return distance * one_km_price;
}


ComfortCar::ComfortCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage)
    : Car(brand, model, type, year, mileage) {}

double ComfortCar::calculate_price(const double& distance) {
    if (distance <= 0) {
        throw std::invalid_argument("Write correct distance.");
    }
    double one_km_price = 3.5;
    return distance * one_km_price;
}


BusinessCar::BusinessCar(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage)
    : Car(brand, model, type, year, mileage) {}

double BusinessCar::calculate_price(const double& distance) {
    if (distance <= 0) {
        throw std::invalid_argument("Write correct distance.");
    }
    double one_km_price = 5.0;
    return distance * one_km_price;
}
