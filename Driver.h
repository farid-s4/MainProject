#pragma once

#include <fstream>
#include <sstream>

#include "User.h"
#include "Car.h"
#include "CarType.h"
#include "string"
#include  <vector>
#include "User.h"
#include "Car.h"
#include <memory>
#include <string>

class Driver : public User {
private:
    std::unique_ptr<Car> _car;
    std::string _license_number;

public:
    Driver();
    Driver(std::unique_ptr<Car> car, const std::string& user_name, const std::string& login,
           const std::string& password, const std::string& UUID, unsigned short rating, unsigned short ratingCount);

    Driver(const Driver& other);
    Driver& operator=(const Driver& other);

    Driver(Driver&& other) noexcept;
    Driver& operator=(Driver&& other) noexcept;

    void set_license_number(const std::string& number);
    void set_car(std::unique_ptr<Car> car);
    const std::string& get_license_number() const;
    Car* get_car() const;

    void generate_license_number();
    void printinfo() const;
};
void read_drivers(const std::string& filename, std::vector<Driver>& data);
void write_drivers(const std::string& filename, const std::vector<Driver>& data);