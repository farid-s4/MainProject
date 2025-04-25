#pragma once
#include <stdexcept>
#include <string>

class Car
{
protected:
    std::string _brand;
    std::string _model;
    std::string _type; 
    unsigned short _year;
    unsigned int _mileage;
public:
    Car();
    Car(const std::string& brand, const std::string& model, const std::string& type, unsigned short year,
        unsigned int mileage);
    Car(const Car& other);
    Car(Car&& other) noexcept;
    Car& operator=(Car&& other) noexcept;
    Car& operator=(const Car& other);
    
    const std::string& getBrand() const;
    const std::string& getModel() const;
    const std::string& getType() const;
    unsigned short getYear() const;
    unsigned int  getMileage() const;
    
    void setBrand(const std::string& brand);
    void setModel(const std::string& model);
    void setType(const std::string& type);
    void setYear(unsigned short year);
    void setMileage(unsigned int mileage);

    virtual double calculate_price(const double& distanse);

    void update_car_info(const std::string& brand, const std::string& model, const std::string& type, unsigned short year, unsigned int mileage);

    bool maintence();
    virtual ~Car(){}
};
