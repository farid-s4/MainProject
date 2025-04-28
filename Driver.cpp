#include "Driver.h"

#include <iostream>
#include <windows.h>

Driver::Driver() : User(), _car(), _license_number("00000000-0000-0000-0000-000000000000") {}

Driver::Driver(Car* car, const std::string& user_name, const std::string& login,
       const std::string& password, const std::string& UUID, unsigned short rating): User(std::string(user_name),std::string(login), std::string(password), rating),
      _car(car), _license_number(UUID) {}

Driver::Driver(const Driver& other): User(other), _car(other._car), _license_number(other._license_number) {}

Driver::Driver(Driver&& other) noexcept : User(std::move(other))
{
    _car = std::move(other._car);
    _license_number = std::move(other._license_number);
}
Driver& Driver::operator=(Driver&& other) noexcept
{
    if (this != &other)
    {
        User::operator=(std::move(other));
        _car = std::move(other._car);
        _license_number = std::move(other._license_number);
        return *this;
    }
    return *this;
}
Driver& Driver::operator=(const Driver& other) 
{
    if (this != &other)
    {
        User::operator=(other);
        _car = other._car;
        _license_number = other._license_number;
    }
    return *this;
}
void Driver::set_license_number(const std::string& number)
{
    _license_number = number;
}
void Driver::set_car(Car* car)
{
    _car = car;
}
const std::string& Driver::get_license_number() const {
    return _license_number;
}

Car* Driver::get_car() const {
    return _car;
}
void  Driver::generate_license_number()
{
    UUID uuid;
    UuidCreate(&uuid);

    unsigned char* str;
    UuidToStringA(&uuid, &str);

    _license_number = reinterpret_cast<char*>(str); 
    
    RpcStringFreeA(&str); 
}
void Driver::printinfo()
{
    std::cout << _user_name << '\n' << _login
    <<'\n' << _password <<'\n' << _rating
    <<'\n' << _license_number << '\n' << _car->getBrand()
    << "," << _car->getModel() << "," << _car->getType()
    << "," << _car->getYear() << "," << _car->getMileage() << '\n' << "##########" << '\n';
}
unsigned short Driver::get_rating() const
{
    return _rating;
}

void write_drivers(const std::string& filename, const std::vector<Driver>& data)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out)
    {
        throw std::runtime_error("Failed to open file for writing!");
    }

    for (const auto& driver : data)
    {
        auto write_string = [&](const std::string& str) {
            size_t str_size = str.size();
            out.write(reinterpret_cast<const char*>(&str_size), sizeof(size_t));
            out.write(str.data(), str_size);
        };

        write_string(driver.get_name());
        write_string(driver.get_login());
        write_string(driver.get_password());
        write_string(driver.get_license_number());

        unsigned short rating = driver.get_rating();
        out.write(reinterpret_cast<const char*>(&rating), sizeof(unsigned short));

        Car* car = driver.get_car();
        write_string(car->getBrand());
        write_string(car->getModel());
        write_string(car->getType());

        unsigned short year = car->getYear();
        unsigned int mileage = car->getMileage();

        out.write(reinterpret_cast<const char*>(&year), sizeof(unsigned short));
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
        Driver driver;
        std::string temp_str;
        size_t str_size;
        
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        driver.set_name(temp_str);
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        driver.set_login(temp_str);
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        driver.set_password(temp_str);
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        driver.set_license_number(temp_str);
        
        unsigned short rating;
        in.read(reinterpret_cast<char*>(&rating), sizeof(unsigned short));
        driver.set_rating(rating);
        
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        std::string car_class = temp_str;
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        std::string brand = temp_str;
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        std::string model = temp_str;
        in.read(reinterpret_cast<char*>(&str_size), sizeof(size_t));
        temp_str.resize(str_size);
        in.read(&temp_str[0], str_size);
        std::string type = temp_str;

        unsigned short year;
        in.read(reinterpret_cast<char*>(&year), sizeof(unsigned short));
        unsigned int mileage;
        in.read(reinterpret_cast<char*>(&mileage), sizeof(unsigned int));

        
        Car* CAR = nullptr;
        if (car_class == "econom") {
            CAR = new EconomCar(brand, model, type, year, mileage);
        } else if (car_class == "comfort") {
            CAR = new ComfortCar(brand, model, type, year, mileage);
        } else if (car_class == "business") {
            CAR = new BusinessCar(brand, model, type, year, mileage);
        } else {
            CAR = new Car(brand, model, type, year, mileage);
        }

        driver.set_car(CAR);
        data.push_back(driver);
        
    }

    in.close();
    
}
