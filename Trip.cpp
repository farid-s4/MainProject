#include "Trip.h"


Trip::Trip() : _first_point("unknown"), _last_point("unknown"), _driver(), _client(), _status(TripStatus::Created), _price(0.0) {}

Trip::Trip(std::string first_point, std::string last_point,Driver driver ,Client client, TripStatus status, double price)
: _first_point(first_point), _last_point(last_point), _driver(driver), _client(client), _status(status), _price(price) {}

Trip::Trip(const Trip& other) : _first_point(other._first_point), _last_point(other._last_point), _driver(other._driver), _client(other._client), _status(other._status), _price(other._price) {}
Trip& Trip::operator=(const Trip& other)
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
void Trip::set_first_point(std::string first_point)
{
    _first_point = first_point;
}
void Trip::set_last_point(std::string last_point)
{
    _last_point = last_point;
}
void Trip::set_driver(Driver driver)
{
    _driver = driver;
}
void Trip::set_client(Client client)
{
    _client = client;
}
void Trip::set_status(TripStatus status)
{
    _status = status;
}
void Trip::set_price(double price)
{
    _price = price;
}
std::string Trip::get_first_point()
{
    return _first_point;
}
std::string Trip::get_last_point()
{
    return _last_point;
}
Driver Trip::get_driver()
{
    return _driver;
}
std::string Trip::get_driver_name()
{
    return _driver.get_name();
}
unsigned short Trip::get_driver_rating()
{
    return _driver.get_rating();
}
Client Trip::get_client()
{
    return _client;
}
TripStatus Trip::get_status()
{
    return _status;
}
double Trip::get_price()
{
    return _price;
}

bool Trip::create_order(std::string first, std::string last, Driver driver, Client client, unsigned short order_rating)
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
void Trip::calculate_price(Driver driver,const double distance)
{
    Car* car = _driver.get_car();
    if (car) {
        _price = car->calculate_price(distance);
    }
    _status = TripStatus::Completed;
}


void write_orders(const std::string& filename, std::vector<Trip>& data)
{
    std::ofstream out(filename);

    if (!out)
    {
        throw std::exception();
    }
    for (int i = 0; i < data.size(); i++)
    {
        out << data[i].get_first_point() <<'\n' <<data[i].get_last_point() <<'\n'<< data[i].get_price() <<'\n'<< data[i].get_driver_name() << '\n' << data[i].get_driver_rating()<<'\n'<< "----------" << '\n';
    }
    out.close();
}