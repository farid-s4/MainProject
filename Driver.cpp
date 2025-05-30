﻿#include "Driver.h"
#include <iostream>
#include <fstream>
#include <windows.h>

Driver::Driver() : User(), _car(nullptr), _license_number("00000000-0000-0000-0000-000000000000") {}

Driver::Driver(std::unique_ptr<Car> car, const std::string& user_name, const std::string& login,
               const std::string& password, const std::string& UUID, unsigned short rating, unsigned short ratingCount)
    : User(user_name, login, password, rating, ratingCount),
      _car(std::move(car)), _license_number(UUID) {}

Driver::Driver(const Driver& other)
    : User(other),
      _car(other._car ? other._car->clone() : nullptr),
      _license_number(other._license_number) {}

Driver& Driver::operator=(const Driver& other) {
    if (this != &other) {
        User::operator=(other);
        _car = other._car ? other._car->clone() : nullptr;
        _license_number = other._license_number;
    }
    return *this;
}

Driver::Driver(Driver&& other) noexcept
    : User(std::move(other)),
      _car(std::move(other._car)),
      _license_number(std::move(other._license_number)) {}

Driver& Driver::operator=(Driver&& other) noexcept {
    if (this != &other) {
        User::operator=(std::move(other));
        _car = std::move(other._car);
        _license_number = std::move(other._license_number);
    }
    return *this;
}

void Driver::set_license_number(const std::string& number) {
    _license_number = number;
}

void Driver::set_car(std::unique_ptr<Car> car) {
    _car = std::move(car);
}

const std::string& Driver::get_license_number() const {
    return _license_number;
}

Car* Driver::get_car() const {
    return _car.get();
}

void Driver::generate_license_number() {
    UUID uuid;
    UuidCreate(&uuid);
    unsigned char* str;
    UuidToStringA(&uuid, &str);
    _license_number = reinterpret_cast<char*>(str);
    RpcStringFreeA(&str);
}
void Driver::printinfo() const 
{
    std::cout << _user_name << '\n' << _login
    <<'\n' << _password <<'\n' << _rating
    <<'\n' << _license_number << '\n' << _car->getBrand()
    << "," << _car->getModel() << "," << _car->getType()
    << "," << _car->getYear() << "," << _car->getMileage() << '\n' << "##########" << '\n';
}

void write_drivers(const std::string& filename, const std::vector<Driver>& data)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out)
    {
        throw std::runtime_error("Failed to open file for writing! / File created.");
    }

    for (const auto& driver : data)
    {
        size_t user_name_size = driver.get_name().size();
        size_t login_size = driver.get_login().size();
        size_t password_size = driver.get_password().size();
        size_t license_size = driver.get_license_number().size();
        
        out.write(reinterpret_cast<const char*>(&user_name_size), sizeof(size_t));
        out.write(driver.get_name().c_str(), user_name_size);

        out.write(reinterpret_cast<const char*>(&login_size), sizeof(size_t));
        out.write(driver.get_login().c_str(), login_size);

        out.write(reinterpret_cast<const char*>(&password_size), sizeof(size_t));
        out.write(driver.get_password().c_str(), password_size);

        out.write(reinterpret_cast<const char*>(&license_size), sizeof(size_t));
        out.write(driver.get_license_number().c_str(), license_size);

        unsigned short rating = driver.get_rating();
        out.write(reinterpret_cast<const char*>(&rating), sizeof(unsigned short));

        unsigned short ratingCount = driver.get_rating_count(); 
        out.write(reinterpret_cast<const char*>(&ratingCount), sizeof(unsigned short));

        size_t car_brand = driver.get_car()->getBrand().size();
        size_t car_model = driver.get_car()->getModel().size();
        size_t car_type = driver.get_car()->getType().size();
        
        out.write(reinterpret_cast<const char*>(&car_brand), sizeof(size_t));
        out.write(driver.get_car()->getBrand().c_str(), car_brand);
        
        out.write(reinterpret_cast<const char*>(&car_model), sizeof(size_t));
        out.write(driver.get_car()->getModel().c_str(), car_model);
        
        out.write(reinterpret_cast<const char*>(&car_type), sizeof(size_t));
        out.write(driver.get_car()->getType().c_str(), car_type);

        unsigned short year = driver.get_car()->getYear();
        out.write(reinterpret_cast<const char*>(&year), sizeof(unsigned short));

        unsigned int mileage = driver.get_car()->getMileage();
        out.write(reinterpret_cast<const char*>(&mileage), sizeof(unsigned int));
    }

    out.close();
}


void read_drivers(const std::string& filename, std::vector<Driver>& data)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        throw std::runtime_error("Failed to open file for reading!");
    }
    data.clear();
    while (in.peek() != EOF)
    {
        size_t user_name_size;
        in.read(reinterpret_cast<char*>(&user_name_size), sizeof(size_t));
        std::string name(user_name_size, '\0');
        in.read(&name[0], user_name_size);

        size_t login_size;
        in.read(reinterpret_cast<char*>(&login_size), sizeof(size_t));
        std::string login(login_size, '\0');
        in.read(&login[0], login_size);

        size_t password_size;
        in.read(reinterpret_cast<char*>(&password_size), sizeof(size_t));
        std::string password(password_size, '\0');
        in.read(&password[0], password_size);

        size_t license_size;
        in.read(reinterpret_cast<char*>(&license_size), sizeof(size_t));
        std::string license(license_size, '\0');
        in.read(&license[0], license_size);

        unsigned short rating;
        in.read(reinterpret_cast<char*>(&rating), sizeof(unsigned short));

        unsigned short ratingCount;
        in.read(reinterpret_cast<char*>(&ratingCount), sizeof(unsigned short)); 

        size_t brand_size;
        in.read(reinterpret_cast<char*>(&brand_size), sizeof(size_t));
        std::string brand(brand_size, '\0');
        in.read(&brand[0], brand_size);

        size_t model_size;
        in.read(reinterpret_cast<char*>(&model_size), sizeof(size_t));
        std::string model(model_size, '\0');
        in.read(&model[0], model_size);

        size_t type_size;
        in.read(reinterpret_cast<char*>(&type_size), sizeof(size_t));
        std::string type(type_size, '\0');
        in.read(&type[0], type_size);

        unsigned short year;
        in.read(reinterpret_cast<char*>(&year), sizeof(unsigned short));

        unsigned int mileage;
        in.read(reinterpret_cast<char*>(&mileage), sizeof(unsigned int));

        std::unique_ptr<Car> car;

        if (type == "econom") {
            car = std::make_unique<EconomCar>(brand, model, type, year, mileage);
        } else if (type == "comfort") {
            car = std::make_unique<ComfortCar>(brand, model, type, year, mileage);
        } else if (type == "business") {
            car = std::make_unique<BusinessCar>(brand, model, type, year, mileage);
        }

        Driver driver(std::move(car), name, login, password, license, rating, ratingCount);
        data.push_back(std::move(driver));
    }
    
    in.close();
    
}
