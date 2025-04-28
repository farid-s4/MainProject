#pragma once

#include <fstream>
#include <sstream>

#include "User.h"
#include "Car.h"
#include "CarType.h"
#include "string"
#include  <vector>

class Driver : public User {
private:
    Car* _car;
    std::string _license_number;

public:
    Driver();
    Driver(Car* car, const std::string& user_name, const std::string& login,
           const std::string& password, const std::string& UUID, unsigned short rating);
    Driver(const Driver& other);
    Driver(Driver&& other) noexcept;

    Driver& operator=(Driver&& other) noexcept;
    Driver& operator=(const Driver& other);

    void set_license_number(const std::string& number);
    void set_car(Car* car);

    const std::string& get_license_number() const;

    Car* get_car() const;
    void  generate_license_number();
    
    unsigned short count = 0;
    
    void printinfo();
};

void read_drivers(const std::string& filename, std::vector<Driver>& data);
void write_drivers(const std::string& filename, const std::vector<Driver>& data);