#pragma comment(lib, "rpcrt4.lib")
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Car.h"
#include "CarType.h"
#include "Driver.h"
#include "Client.h"
#include "Trip.h"

int main() //CLEAR AND FİX DATA İN READ!
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
