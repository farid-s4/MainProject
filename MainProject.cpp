#pragma comment(lib, "rpcrt4.lib")
#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Car.h"
#include "CarType.h"
class Client;
class Driver;


class CarManager
{
    private:
    std::vector<Car*> cars;
    public:
    CarManager() : cars(){}
    CarManager(std::vector<Car*> cars) : cars(cars){}
    CarManager(const CarManager& other) : cars(other.cars) {}
    CarManager& operator=(const CarManager& other)
    {
        if (this != &other)
        {
            cars = other.cars;
            return *this;
        }
        return *this;
    }
    CarManager(CarManager&& other) noexcept : cars(std::move(other.cars)) {}
    CarManager& operator=(CarManager&& other) noexcept
    {
        if (this != &other)
        {
            cars = std::move(other.cars);
            return *this;
        }
        return *this;
    }
    void redact_car(unsigned int index, std::string brand, std::string model, std::string type, unsigned short year, unsigned int mileage)
    {
        if (index < cars.size())
        {
            cars[index]->update_car_info(brand, model, type, year, mileage);
        }
        
    }
    bool maintence(int index)
    {
        if (index < cars.size())
        {
            if (cars[index]->maintence())
            {
                return true;
            }
            
        }
        return false;
    }
};

class User
{
protected:
    std::string _user_name;
    std::string _login;
    std::string _password;
    unsigned short _rating;
public:
    virtual ~User() = default;

    User(): _user_name("Unknown"), _login("Unknown"), _password("Unknown"), _rating(0) {}
    User(const std::string& user_name, const std::string& login, const std::string& password, unsigned short rating) : _user_name(user_name), _login(login), _password(password), _rating(rating) {}
    User(const User& other)
        : _user_name(other._user_name),
          _login(other._login),
          _password(other._password),
          _rating(other._rating) {}
    User(User&& other) noexcept
        : _user_name(std::move(other._user_name)),
          _login(std::move(other._login)),
          _password(std::move(other._password)),
          _rating(other._rating) {}
    
    User& operator=(const User& other)
    {
        if (this != &other)
        {
            _user_name = other._user_name;
            _login = other._login;
            _password = other._password;
            _rating = other._rating;
        }
        return *this;
    }


    User& operator=(User&& other) noexcept
    {
        if (this != &other)
        {
            _user_name = std::move(other._user_name);
            _login = std::move(other._login);
            _password = std::move(other._password);
            _rating = other._rating;
        }
        return *this;
    }
    void set_name(const std::string& name)
    {
        _user_name = name;
    }
    void set_login(const std::string& login)
    {
        _login = login;
    }
    void set_password(const std::string& password)
    {
        _password = password;
    }
    const std::string& get_name() const {
        return _user_name;
    }

    const std::string& get_login() const {
        return _login;
    }

    const std::string& get_password() const {
        return _password;
    }
    unsigned short set_rating(unsigned short rating)
    {
        if (rating > 0 && rating <= 10)
        {
            _rating = rating;
            return _rating;
        }
        else
        {
            throw std::invalid_argument("Rating must be between 1 and 10.");
        }
    }
    
    unsigned short get_rating()
    {
        return _rating;
    }
    virtual void rate_driver(Driver& driver,unsigned short rating) {}
    virtual void rate_client(Client& client, unsigned short rating) {}
    
};
class FileOpenException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "FileOpenException";
    }
};
class Driver : public User {
private:
    Car* _car;
    std::string _license_number;

public:
    Driver() : User(), _car(), _license_number("00000000-0000-0000-0000-000000000000") {}

    Driver(Car* car, const std::string& user_name, const std::string& login,
           const std::string& password, const std::string& UUID, unsigned short rating): User(std::string(user_name),std::string(login), std::string(password), rating),
          _car(car), _license_number(UUID) {}

    Driver(const Driver& other): User(other), _car(other._car), _license_number(other._license_number) {}

    Driver(Driver&& other) noexcept : User(std::move(other))
    {
        _car = std::move(other._car);
        _license_number = std::move(other._license_number);
    }
    Driver& operator=(Driver&& other) noexcept
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
    Driver& operator=(const Driver& other) 
    {
        if (this != &other)
        {
            User::operator=(other);
            _car = other._car;
            _license_number = other._license_number;
        }
        return *this;
    }
    void set_license_number(const std::string& number)
    {
        _license_number = number;
    }
    void set_car(Car* car)
    {
        _car = car;
    }
    const std::string& get_license_number() const {
        return _license_number;
    }

    Car* get_car() const {
        return _car;
    }
    void  generate_license_number()
    {
        UUID uuid;
        UuidCreate(&uuid);

        unsigned char* str;
        UuidToStringA(&uuid, &str);

        _license_number = reinterpret_cast<char*>(str); 
        
        RpcStringFreeA(&str); 
    }
    unsigned short count = 0;
    void rate_driver(Driver& driver, unsigned short rating) override
    {
        if (count == 0)
        {
            driver.set_rating(rating);
        }
        count += 1;
        driver.set_rating((_rating + rating) / 2);
    }
    void printinfo()
    {
        std::cout << _user_name << '\n' << _login
        <<'\n' << _password <<'\n' << _rating
        <<'\n' << _license_number << '\n' << _car->getBrand()
        << "," << _car->getModel() << "," << _car->getType()
        << "," << _car->getYear() << "," << _car->getMileage() << '\n' << "##########" << '\n';
    }
    
    bool write_driver(const std::string& filename)
    {
        std::ofstream out(filename, std::ios::app);
        if (!out)
        {
            throw FileOpenException();
        }
        out << _user_name << '\n' << _login
        <<'\n' << _password <<'\n' << _rating
        <<'\n' << _license_number << '\n' << _car->getBrand()
        << "," << _car->getModel() << "," << _car->getType()
        << "," << _car->getYear() << "," << _car->getMileage() << '\n'<< "##########" << '\n';
        out.close();
        return true;
    }
    
};

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
        throw FileOpenException();
    }
}
void write_drivers(std::string filename, std::vector<Driver>& data)
{
    std::ofstream out(filename, std::ios::out);
    if (!out)
    {
        throw FileOpenException();
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
class Client : public User
{
private:
    std::string uuid_;
public:
    Client() : uuid_("00000000-0000-0000-0000-000000000000"){}
    Client(std::string UUID) : uuid_(UUID){}
    Client(Car car, const std::string& user_name, const std::string& login,
           const std::string& password, const std::string& UUID, unsigned short rating): User(std::string(user_name),std::string(login), std::string(password), rating),
          uuid_(UUID) {}
    Client(const Client& other) : User(other), uuid_(other.uuid_){}
    Client(Client&& other) noexcept : User(std::move(other)),  uuid_(std::move(other.uuid_)){}
    Client& operator=(Client&& other) noexcept
    {
        if (this != &other)
        {
            User::operator=(std::move(other));
            uuid_ = std::move(other.uuid_);
            return *this;
        }
        return *this;
    }
    Client& operator=(const Client& other)
    {
        if (this != &other)
        {
            User::operator=(other);
            uuid_ = other.uuid_;
        }
        return *this;
    }
    void set_uuid(std::string UUID)
    {
        uuid_ = UUID;
    }
    const std::string& get_uuid()
    {
        return uuid_;
    }
    void genenerate_uuid()
    {
        UUID uuid;
        UuidCreate(&uuid);

        unsigned char* str;
        UuidToStringA(&uuid, &str);

        uuid_ = reinterpret_cast<char*>(str); 
        
        RpcStringFreeA(&str);
    }
    
    unsigned short count = 0;
    void rate_client(Client& client, unsigned short rating) override
    {
        if (count == 0)
        {
            client.set_rating(rating);
        }
        count += 1;
        client.set_rating((_rating + rating) / 2);
        
    }
    
    bool write_client(const std::string& filename)
    {
        std::ofstream out(filename, std::ios::app);
        if (!out)
        {
            throw FileOpenException();
        }
        out << _user_name << '\n' << _login
        <<'\n' << _password <<'\n' << _rating
        <<'\n' << uuid_ << '\n' <<"##########" << '\n';
        out.close();
        return true;
    }
};

void read_clients(std::string filename, std::vector<Client>& data)
{
    std::ifstream file(filename); 
    std::string name, login, password, ratingSTR, uuid, line;
    unsigned short rating;
    Client client;

    if (file.is_open()) {
        while (std::getline(file, name) && std::getline(file, login) && std::getline(file, password) && std::getline(file, ratingSTR) &&  std::getline(file, uuid) && std::getline(file, line)) {
            
            client.set_name(name);
            client.set_login(login);
            client.set_password(password);
            int temp_rating = std::stoi(ratingSTR);
            client.set_rating(rating = static_cast<unsigned short>(temp_rating));
            client.set_uuid(uuid);
            data.push_back(client);
        }
        file.close(); 
    } else {
        throw FileOpenException();
    }
}

void write_clients(std::string filename, std::vector<Client>& data)
{
    std::ofstream out(filename, std::ios::out);
    if (!out)
    {
        throw FileOpenException();
    }
    
    for (int i = 0; i < data.size(); i++)
    {
        out << data[i].get_name() << '\n' << data[i].get_login()
        <<'\n' << data[i].get_password() <<'\n' << data[i].get_rating()
        <<'\n' << data[i].get_uuid() << '\n' << "##########" << '\n';
    }
    out.close();
}
enum class TripStatus { Created, InProgress, Completed };
class Trip
{
private:
    std::string _first_point;
    std::string _last_point;
    Driver _driver;
    Client _client;
    TripStatus _status;
    double _price;
public:
    Trip() : _first_point("unknown"), _last_point("unknown"), _driver(), _client(), _status(TripStatus::Created), _price(0.0) {}
    
    Trip(std::string first_point, std::string last_point,Driver driver ,Client client, TripStatus status, double price)
    : _first_point(first_point), _last_point(last_point), _driver(driver), _client(client), _status(status), _price(price) {}
    
    Trip(const Trip& other) : _first_point(other._first_point), _last_point(other._last_point), _driver(other._driver), _client(other._client), _status(other._status), _price(other._price) {}
    Trip& operator=(const Trip& other)
    {
        if (this != &other)
        {
            _first_point = other._first_point;
            _last_point = other._last_point;
            _driver = other._driver;
            _client = other._client;
            _status = other._status;
            _price = other._price;
        }
        return *this;
    }
    void set_first_point(std::string first_point)
    {
        _first_point = first_point;
    }
    void set_last_point(std::string last_point)
    {
        _last_point = last_point;
    }
    void set_driver(Driver driver)
    {
        _driver = driver;
    }
    void set_client(Client client)
    {
        _client = client;
    }
    void set_status(TripStatus status)
    {
        _status = status;
    }
    void set_price(double price)
    {
        _price = price;
    }
    std::string get_first_point()
    {
        return _first_point;
    }
    std::string get_last_point()
    {
        return _last_point;
    }
    Driver get_driver()
    {
        return _driver;
    }
    std::string get_driver_name()
    {
        return _driver.get_name();
    }
    unsigned short get_driver_rating()
    {
        return _driver.get_rating();
    }
    Client get_client()
    {
        return _client;
    }
    TripStatus get_status()
    {
        return _status;
    }
    double get_price()
    {
        return _price;
    }
    
    bool create_order(std::string first, std::string last, Driver driver, Client client, unsigned short order_rating)
    {
        if (order_rating == driver.get_rating())
        {
            _first_point = first;
            _last_point = last;
            _driver = driver;
            _client = client;
            _status = TripStatus::InProgress;
            _price = 0.0;
            return true;
        }
        return false;
    }
    void calculate_price(Driver driver,const double distance)
    {
        Car* car = _driver.get_car();
        if (car) {
            _price = car->calculate_price(distance);
        }
        _status = TripStatus::Completed;
    }
    
};

void write_orders(const std::string& filename, std::vector<Trip>& data)
{
    std::ofstream out(filename);

    if (!out)
    {
        throw FileOpenException();
    }
    for (int i = 0; i < data.size(); i++)
    {
        out << data[i].get_first_point() <<'\n' <<data[i].get_last_point() <<'\n'<< data[i].get_price() <<'\n'<< data[i].get_driver_name() << '\n' << data[i].get_driver_rating()<<'\n'<< "----------" << '\n';
    }
    out.close();
}

int main()
{
    try {
        std::vector<Client> clients;
        
        EconomCar a("Toyota", "Corolla", "Sedan", 2020, 50000);
        BusinessCar comfortCar("Honda", "Accord", "Sedan", 2021, 30000);
        ComfortCar businessCar("BMW", "5 Series", "Sedan", 2022, 15000);
 
 
        Client client;
        client.genenerate_uuid();
 
 
        Driver driver(&a, "John Doe", "john123", "securePass", "tempUUID", 5);
        Driver driver2(&comfortCar, "1", "1", "1", "1", 5);
        Driver driver3(&businessCar, "2", "2", "2", "2", 5);
        driver.generate_license_number();
        
        std::vector<Trip> trips;
        Trip trip;
        driver.printinfo();
        trip.create_order("28 may", "Genclik", driver, client, 5);
        trip.calculate_price(driver, 2);
        trips.push_back(trip);
        std::cout<<trips[0].get_driver_name();
        write_orders("orders.txt", trips);
    }
    catch (const std::exception& ex) {
        std::cerr << "error: " << ex.what() << '\n';
    }
 
    return 0;
}
