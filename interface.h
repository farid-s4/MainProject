#pragma once
#include "Client.h"
#include "Driver.h"
#include "Trip.h"
#include "User.h"
#include <iostream>
#pragma once

#include <iostream>
#include <vector>
#include <string>


class Driver;
class Client;
class Trip;
class Car;
class EconomCar;
class ComfortCar;
class BusinessCar;


extern std::vector<Driver> drivers;
extern std::vector<Client> clients;
extern std::vector<Trip> trips;


void clearInputBuffer();
void loadClients();
void unloadClients();
void loadDrivers();
void unload_drivers();
void load_trips();
void unload_trips();


void registration();
void authorization();


void print_drivers();


bool isValidPassword(const std::string& password);


void read_clients(const std::string& filename, std::vector<Client>& clients);
void write_clients(const std::string& filename, const std::vector<Client>& clients);


void read_drivers(const std::string& filename, std::vector<Driver>& drivers);
void write_drivers(const std::string& filename, const std::vector<Driver>& drivers);


void read_orders(const std::string& filename, std::vector<Trip>& trips);
void write_orders(const std::string& filename, const std::vector<Trip>& trips);

void cleanup();
void adminMenu();