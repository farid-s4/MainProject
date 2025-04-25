#pragma once

#include <fstream>
#include <sstream>

#include "Driver.h"
#include "Car.h"
#include "Client.h"
#include "CarType.h"
#include <string>
#include  <vector>
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
    Trip();
    
    Trip(std::string first_point, std::string last_point,Driver driver ,Client client, TripStatus status, double price);
    
    Trip(const Trip& other);
    Trip& operator=(const Trip& other);
    
    void set_first_point(std::string first_point);
    void set_last_point(std::string last_point);
    void set_driver(Driver driver);
    void set_client(Client client);
    void set_status(TripStatus status);
    void set_price(double price);

    std::string get_first_point();
    std::string get_last_point();
    std::string get_driver_name();
    
    Driver get_driver();
    Client get_client();
    TripStatus get_status();

    unsigned short get_driver_rating();
    double get_price();
    bool create_order(std::string first, std::string last, Driver driver, Client client, unsigned short order_rating);
    void calculate_price(Driver driver,const double distance);

    
};

void write_orders(const std::string& filename, std::vector<Trip>& data);