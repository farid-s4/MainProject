#pragma comment(lib, "rpcrt4.lib")
#include <iostream>
#include <windows.h>
#include <fstream>
class Client;
class Driver;

class Car
{
protected:
    std::string _brand;
    std::string _model;
    std::string _type; //sedan or SUV and other...
    unsigned short _year;
    double _mileage;
public:
    Car() : _brand("Unknown") , _model("Unknown") , _type("Unknown") , _year(0) , _mileage(0){}
    Car(const std::string brand, const std::string model, const std::string type, unsigned short year , double mileage) : _brand(brand) , _model(model) , _type(type), _year(year), _mileage(mileage){}
    Car(const Car& other)
    {
        _brand = other._brand;
        _model = other._model;
        _type = other._type;
        _year = other._year;
        _mileage = other._mileage;
    }
    Car(Car&& other) noexcept
        : _brand(std::move(other._brand)), _model(std::move(other._model)), _type(std::move(other._type)),
          _year(other._year), _mileage(other._mileage) {
        other._year = 0;
        other._mileage = 0;
    }
    Car& operator=(Car&& other) noexcept
    {
        if (this != &other)
        {
            _brand = std::move(other._brand);
            _model = std::move(other._model);
            _type = std::move(other._type);
            _year = other._year;
            _mileage = other._mileage;
            other._brand.clear();
            other._model.clear();
            other._type.clear();
            other._year = 0;
            other._mileage = 0;
            return *this;
        }
        return *this;
        
    }
    Car& operator=(const Car& other)
    {
        if (this != &other) {
            _brand = other._brand;
            _model = other._model;
            _type = other._type;
            _year = other._year;
            _mileage = other._mileage;
        }
        return *this;
    }
    virtual std::string getBrand() const {
        return _brand;
    }

    virtual std::string getModel() const {
        return _model;
    }

    virtual std::string getType() const {
        return _type;
    }

    virtual unsigned short getYear() const {
        return _year;
    }

    virtual double getMileage() const {
        return _mileage;
    }
    virtual double calculate_price(const double& distanse)
    {
        return distanse;
    }
    virtual ~Car(){}
};

class EconomCar : public Car
{
public:
    EconomCar(std::string brand, std::string model, std::string type, unsigned short year, double mileage)
    : Car(brand, model, type, year, mileage) {}

    double calculate_price(const double& distanse) override
    {
        double one_km_price = 2;
        if (distanse > 0)
        {
            return distanse*one_km_price;
        }
        else
        {
            throw std::invalid_argument("Write correct distance.");
        }
    }
    std::string getBrand() const override
    {
        return _brand;
    }

    std::string getModel() const override
    {
        return _model;
    }

    std::string getType() const override
    {
        return _type;
    }

    unsigned short getYear() const override
    {
        return _year;
    }

    double getMileage() const override
    {
        return _mileage;
    }
    EconomCar() = default;
    
};
class ComfortCar : public Car
{
public:
    ComfortCar(std::string brand,std::string model, std::string type, unsigned short year, double mileage){}
    double calculate_price(const double& distanse) override
    {
        double one_km_price = 3.5;
        if (distanse > 0)
        {
            return distanse*one_km_price;
        }
        else
        {
            throw std::invalid_argument("Write correct distance.");
        }
    }
    std::string getBrand() const override
    {
        return _brand;
    }

    std::string getModel() const override
    {
        return _model;
    }

    std::string getType() const override
    {
        return _type;
    }

    unsigned short getYear() const override
    {
        return _year;
    }

    double getMileage() const override
    {
        return _mileage;
    }
};
class BusinessCar : public Car
{
public:
    BusinessCar(std::string brand,std::string model, std::string type, unsigned short year, double mileage){}
    double calculate_price(const double& distanse) override
    {
        double one_km_price = 5;
        if (distanse > 0)
        {
            return distanse*one_km_price;
        }
        else
        {
            throw std::invalid_argument("Write correct distance.");
        }
    }
    std::string getBrand() const override
    {
        return _brand;
    }

    std::string getModel() const override
    {
        return _model;
    }

    std::string getType() const override
    {
        return _type;
    }

    unsigned short getYear() const override
    {
        return _year;
    }

    double getMileage() const override
    {
        return _mileage;
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

    User()
        : _user_name("Unknown"), _login("Unknown"), _password("Unknown"), _rating(0) {}
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
    virtual void rate_driver(Driver& driver,unsigned short rating) = 0;
    virtual void rate_client(Client& client, unsigned short rating) = 0;
    
};
class FileOpenException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "FileOpenException";
    }
};

class Driver : public User {
private:
    Car _car;
    std::string _license_number;

public:
    Driver() : User(), _car(), _license_number("00000000-0000-0000-0000-000000000000") {}

    Driver(Car car, const std::string& user_name, const std::string& login,
           const std::string& password, const std::string& UUID, unsigned short rating): User(std::string(user_name),std::string(login), std::string(password), rating),
          _car(car), _license_number(UUID) {}

    Driver(const Driver& other): User(other), _car(other._car), _license_number(other._license_number) {}
    Driver& operator=(Driver&& other) noexcept
    {
        if (this != &other)
        {
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
            _car = other._car;
            _license_number = other._license_number;
        }
        return *this;
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
    void  generate_license_number()
    {
        UUID uuid;
        UuidCreate(&uuid);

        unsigned char* str;
        UuidToStringA(&uuid, &str);

        _license_number = reinterpret_cast<char*>(str); 
        
        RpcStringFreeA(&str); 
    }
    void rate_client(Client& client ,unsigned short rating) override
    {
        client.set_rating(rating);
    }
    void rate_driver(Driver& driver, unsigned short rating) override
    {
        driver.set_rating(rating);
    }
    void printinfo()
    {
        std::cout << _user_name << '\n' << _login
        <<'\n' << _password <<'\n' << _rating
        <<'\n' << _license_number << '\n' << _car.getBrand()
        << "," << _car.getModel() << "," << _car.getType()
        << "," << _car.getYear() << "," << _car.getMileage() << '\n';
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
        <<'\n' << _license_number << '\n' << _car.getBrand()
        << "," << _car.getModel() << "," << _car.getType()
        << "," << _car.getYear() << "," << _car.getMileage() << '\n'<<'\n';
        out.close();
        return true;
    }
    
};

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

    Client(Client&& other) noexcept :  uuid_(std::move(other.uuid_)){}
    Client& operator=(Client&& other) noexcept
    {
        if (this != &other)
        {
            uuid_ = std::move(other.uuid_);
            return *this;
        }
        return *this;
    }
    Client& operator=(const Client& other)
    {
        if (this != &other)
        {
            uuid_ = other.uuid_;
        }
        return *this;
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
    void genenerate_uuid()
    {
        UUID uuid;
        UuidCreate(&uuid);

        unsigned char* str;
        UuidToStringA(&uuid, &str);

        uuid_ = reinterpret_cast<char*>(str); 
        
        RpcStringFreeA(&str); 
    }
    
    void rate_client(Client& client ,unsigned short rating) override
    {
        client.set_rating(rating);
    }
    void rate_driver(Driver& driver, unsigned short rating) override
    {
        driver.set_rating(rating);
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
        <<'\n' << uuid_ << '\n'<<'\n';
        out.close();
        return true;
    }
};

int main()
{
    try {

        EconomCar a("Toyota", "Corolla", "Sedan", 2020, 50000);
        ComfortCar comfortCar("Honda", "Accord", "Sedan", 2021, 30000);
        BusinessCar businessCar("BMW", "5 Series", "Sedan", 2022, 15000);


        Client client;
        client.genenerate_uuid();


        Driver driver(static_cast<Car>(a), "John Doe", "john123", "securePass", "tempUUID", 5);
        Driver driver2(static_cast<Car>(a), "1", "1", "1", "1", 5);
        Driver driver3(static_cast<Car>(a), "2", "2", "2", "2", 5);
        driver.generate_license_number();
        driver.write_driver("drivers.txt");
        driver2.write_driver("drivers.txt");
        driver3.write_driver("drivers.txt");
        driver.printinfo();
        double distance = 10.0;


        driver.rate_client(client, 8); 
        client.rate_driver(driver, 9); 
        std::cout << driver.get_rating() << '\n';
        std::cout << client.get_rating() << '\n';
        std::cout << "Rating successfully assigned!" << '\n';
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
    }

    return 0;
}
