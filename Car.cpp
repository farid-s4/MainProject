#include "Car.h"
Car::Car() : _brand("Unknown"), _model("Unknown"), _type("Unknown"), _year(0), _mileage(0) {}

Car::Car(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage)
    : _brand(brand), _model(model), _type(type), _year(year), _mileage(mileage) {}

Car::Car(const Car& other)
    : _brand(other._brand), _model(other._model), _type(other._type), _year(other._year), _mileage(other._mileage) {}

Car::Car(Car&& other) noexcept
    : _brand(std::move(other._brand)), _model(std::move(other._model)), _type(std::move(other._type)),
      _year(other._year), _mileage(other._mileage) {
    other._year = 0;
    other._mileage = 0;
}

Car& Car::operator=(Car&& other) noexcept {
    if (this != &other) {
        _brand = std::move(other._brand);
        _model = std::move(other._model);
        _type = std::move(other._type);
        _year = other._year;
        _mileage = other._mileage;

        other._year = 0;
        other._mileage = 0;
    }
    return *this;
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        _brand = other._brand;
        _model = other._model;
        _type = other._type;
        _year = other._year;
        _mileage = other._mileage;
    }
    return *this;
}


const std::string& Car::getBrand() const { return _brand; }
const std::string& Car::getModel() const { return _model; }
const std::string& Car::getType() const { return _type; }
unsigned short Car::getYear() const { return _year; }
unsigned int Car::getMileage() const { return _mileage; }


void Car::setBrand(const std::string& brand) { _brand = brand; }
void Car::setModel(const std::string& model) { _model = model; }
void Car::setType(const std::string& type) { _type = type; }
void Car::setYear(unsigned short year) { _year = year; }
void Car::setMileage(unsigned int mileage) { _mileage = mileage; }


double Car::calculate_price(const double& distance) {
    return distance; 
}

void Car::update_car_info(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage) {
    _brand = brand;
    _model = model;
    _type = type;
    _year = year;
    _mileage = mileage;
}

bool Car::maintence()
{
    if (_mileage > 50000)
    {
        return true;
    }
    return false;
}
