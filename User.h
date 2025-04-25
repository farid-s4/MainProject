/*#pragma once
#include <string>

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
            CAR->setyear(static_cast<unsigned short>(year_));
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
}*/