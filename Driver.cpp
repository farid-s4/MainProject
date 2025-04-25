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
void Driver::rate_driver(Driver& driver, unsigned short rating) 
{
    if (count == 0)
    {
        driver.set_rating(rating);
    }
    count += 1;
    driver.set_rating((_rating + rating) / 2);
}
void Driver::printinfo()
{
    std::cout << _user_name << '\n' << _login
    <<'\n' << _password <<'\n' << _rating
    <<'\n' << _license_number << '\n' << _car->getBrand()
    << "," << _car->getModel() << "," << _car->getType()
    << "," << _car->getYear() << "," << _car->getMileage() << '\n' << "##########" << '\n';
}

bool Driver::write_driver(const std::string& filename)
{
    std::ofstream out(filename, std::ios::app);
    if (!out)
    {
        throw std::exception();
    }
    out << _user_name << '\n' << _login
    <<'\n' << _password <<'\n' << _rating
    <<'\n' << _license_number << '\n' << _car->getBrand()
    << "," << _car->getModel() << "," << _car->getType()
    << "," << _car->getYear() << "," << _car->getMileage() << '\n'<< "##########" << '\n';
    out.close();
    return true;
}

void read_drivers(std::string filename, std::vector<Driver>& data)
{
    std::ifstream file(filename); 
    std::string name, login, password, license_number, car, ratingSTR, line;
    std::string brand, model, type, year_str, mileage_str;
    unsigned short rating;
    Driver driver;
    Car* CAR;
    if (file.is_open()) {
        while (std::getline(file, name) && std::getline(file, login) && std::getline(file, password) &&  std::getline(file, ratingSTR)&& std::getline(file, license_number) && std::getline(file, car) && std::getline(file, line)) { 
            driver.set_name(name);
            driver.set_login(login);
            driver.set_password(password);
            int temp_rating = std::stoi(ratingSTR);
            driver.set_rating(rating = static_cast<unsigned short>(temp_rating));
            driver.set_license_number(license_number);
            std::stringstream ss(car);
            std::getline(ss, brand, ',');
            std::getline(ss, model, ',');
            std::getline(ss, type, ',');
            std::getline(ss, year_str, ',');
            std::getline(ss, mileage_str, ',');
            int year_ = std::stoi(year_str);
            int mileage_ = std::stoi(mileage_str);
            if (type == "econom") {
                CAR = new EconomCar(brand, model, type, year_, mileage_);
            } else if (type == "comfort") {
                CAR = new ComfortCar(brand, model, type, year_, mileage_);
            } else if (type == "business") {
                CAR = new BusinessCar(brand, model, type, year_, mileage_);
            } else {
                CAR = new Car(brand, model, type, year_, mileage_);
            }
            CAR->setBrand(brand);  
            CAR->setModel(model);
            CAR->setType(type);
            CAR->setYear(static_cast<unsigned short>(year_));
            CAR->setMileage(static_cast<unsigned int>(mileage_));
            driver.set_car(CAR);
            data.push_back(driver);
            
        }

        file.close(); 
    } else {
        throw std::exception();
    }
}
void write_drivers(std::string filename, std::vector<Driver>& data)
{
    std::ofstream out(filename, std::ios::out);
    if (!out)
    {
        throw std::exception();
    }
    
    for (int i = 0; i < data.size(); i++)
    {
        out << data[i].get_name() << '\n' << data[i].get_login()
        <<'\n' << data[i].get_password() <<'\n' << data[i].get_rating()
        <<'\n' << data[i].get_license_number() << '\n';
        const Car* car = data[i].get_car();
        out << car->getBrand() << ','
            << car->getModel() << ','
            << car->getType() << ','
            << car->getYear() << ','
            << car->getMileage() << '\n' << "##########" << '\n';
    }
    out.close();
}