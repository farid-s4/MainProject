#include "interface.h"
std::vector<Driver> drivers;
std::vector<Client> clients;
std::vector<Trip> trips;
void clearInputBuffer() {
    while (std::cin.get() != '\n');
}
void loadClients()
{
    try
    {
        read_clients(R"(AllData/clients.bin)",clients);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
void unloadClients()
{
    try
    {
        write_clients("AllData/clients.bin",clients);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
void load_drivers()
{
    try
    {
        read_drivers("AllData/drivers.bin",drivers);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
void unload_drivers()
{
    try
    {
        write_drivers("AllData/drivers.bin",drivers);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void load_trips()
{
    try
    {
        read_orders("AllData/orders.txt",trips);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
void unload_trips()
{
    try
    {
        write_orders("AllData/orders.txt",trips);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
bool isValidPassword(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasLetter = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (char ch : password) {

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            hasLetter = true;
        }
        else if (ch >= '0' && ch <= '9') {
            hasDigit = true;
        }

        else {
            hasSpecial = true;
        }
    }

    return hasLetter && hasDigit && hasSpecial;
}
void reg()
{
    while (true)
    {
        unsigned short choose;
        std::cout << "Tell me who are you client or driver? 1/2" << '\n';
        std::cin >> choose;
        
        if (choose == 1)
        {
            std::string name, login, password;
            std::cout << "What is your name?\n";
            std::cin >> name;
            std::cout << "What is your login?\n";
            std::cin >> login;
            
            do {
                std::cout << "What is your password?\n";
                std::cin >> password;
                if (!isValidPassword(password))
                {
                    std::cout << "Unsafe password, please try again!\n";
                }
            }
            while (!isValidPassword(password));
            
            std::cout << "Correct password!\n";

            loadClients();
            Client client;
            client.set_login(login);
            client.set_name(name);
            client.set_password(password);
            client.set_rating(10);
            client.genenerate_uuid();
            clients.push_back(client);
            unloadClients();
            std::cout << "Correct registration!\n";
            break;
        }
        else if (choose == 2)
        {
            std::string user_name, login, password, license_number;
            std::string car_brand, car_model, car_type;
            unsigned short rating, _year;
            unsigned int mileage;
            int car_type_choose;
            std::cout << "Enter your name: ";
            std::cin >> user_name;

            std::cout << "Enter your login: ";
            std::cin >> login;

            do {
                std::cout << "Enter your password: ";
                std::cin >> password;
                if (!isValidPassword(password)) {
                    std::cout << "Password is unsafe, please try again (at least 8 characters, letter, digit, special symbol).\n";
                }
            } while (!isValidPassword(password));
            
            std::cout << "Enter your car brand: ";
            std::cin >> car_brand;

            std::cout << "Enter your car model: ";
            std::cin >> car_model;

            std::cout << "Enter your car type (econom, comfort or business): ";
            std::cin >> car_type_choose;
            switch (car_type_choose)
            {
                case 1:
                    car_type = "econom";
                break;
                case 2:
                    car_type = "comfort";
                break;
                case 3:
                    car_type = "business";
                break;
                default: car_type = "econom";
            }
            std::cout << "Enter your car manufacture year: ";
            std::cin >> _year;

            std::cout << "Enter your car mileage (km): ";
            std::cin >> mileage;

            
            load_drivers();
            Car* CAR;
            if (car_type == "econom") {
                CAR = new EconomCar(car_brand, car_model, car_type, _year, mileage);
            } else if (car_type == "comfort") {
                CAR = new ComfortCar(car_brand, car_model, car_type, _year, mileage);
            } else if (car_type == "business") {
                CAR = new BusinessCar(car_brand, car_model, car_type, _year, mileage);
            } else {
                CAR = new Car(car_brand, car_model, car_type, _year, mileage);
            }
            
            Driver driver;
            driver.set_car(CAR);
            driver.set_login(login);
            driver.set_password(password);
            driver.set_rating(10);
            driver.set_name(user_name);
            driver.generate_license_number();
            drivers.push_back(driver);
            unload_drivers();
            delete CAR;
            break;
        }
        else
        {
            std::cout << "Please choose 1 (client) or 2 (driver)!\n";
        }
    }
}
void authorization()
{
    while (true)
    {
        unsigned short choose;
        std::cout << "Tell me who are you client or driver? 1/2" << '\n';
        std::cin >> choose;
        if (choose != 1 && choose != 2)
        {
            return;
        }
        switch (choose)
        {
        case 1:
        {
            std::string login;
            std::string password;
            std::cout << "Enter login to authorization\n";
            std::cin >> login;
            std::cout << "Enter password to authorization\n";
            std::cin >> password;
            loadClients();
            Client client;

                bool found = false;
                for (unsigned int i = 0; i < clients.size(); i++)
                {
                    if (clients[i].get_login() == login && clients[i].get_password() == password)
                    {
                        client = clients[i];
                        found = true;
                        break; 
                    }
                }

                if (!found)
                {
                    std::cout << "Wrong login or password!\n";
                    return;
                }

            while (true)
            {
                std::cout << "Choose what you want to do? (1: Book a ride / 2: View my rides / 3: Rate the driver / 4: Log out)\n";
                std::cin >> choose;
                if (choose != 1 && choose != 2 && choose != 3 && choose != 4)
                {
                    break;
                }
                switch (choose)
                {
                case 1:
                {
                    std::string firstP;
                    std::string lastP;
                    double distance;
                    unsigned short car_type_choose;
                    std::string car_type;
                    unsigned short rating;

                    std::cout << "Enter a distance for the trip:\n";
                    std::cin >> distance;

                    std::cout << "What car type do you want? (1: Econom / 2: Comfort / 3: Business)\n";
                    std::cin >> car_type_choose;
                    std::cin.ignore();

                    std::cout << "Enter first position for trip:\n";
                    std::getline(std::cin, firstP);

                    std::cout << "Enter last position for trip:\n";
                    std::getline(std::cin, lastP);

                    switch (car_type_choose)
                    {
                    case 1:
                        car_type = "econom";
                        break;
                    case 2:
                        car_type = "comfort";
                        break;
                    case 3:
                        car_type = "business";
                        break;
                    default:
                        car_type = "econom";
                    }

                    std::cout << "What driver rating do you want?\n";
                    std::cin >> rating;

                    Driver driver;
                    load_drivers();
                    bool driverFound = false;
                    for (auto& d : drivers)
                    {
                        if (d.get_rating() == rating && d.get_car()->getType() == car_type)
                        {
                            driver = d;
                            driverFound = true;
                            break;
                        }
                    }

                    if (!driverFound)
                    {
                        std::cout << "No drivers matching criteria!\n";
                        break;
                    }

                    Trip trip(firstP, lastP, driver, client, TripStatus::Created, distance);
                    trip.create_order(firstP, lastP, driver, client, rating);
                    trip.calculate_price(driver, distance);
                    load_trips();
                    trips.push_back(trip);
                    unload_trips();

                    std::cout << "Driver name: " << driver.get_name() << '\n';
                    break;
                }
                case 2:
                {
                    load_trips();
                    for (size_t i = 0; i < trips.size(); i++)
                    {
                        if (login == trips[i].get_client().get_login())
                        {
                            std::cout << "Order price: " << trips[i].get_price() << '\n'
                                      << "First point: " << trips[i].get_first_point() << '\n'
                                      << "Last point: " << trips[i].get_last_point() << '\n';
                        }
                    }
                    break;
                }
                case 3:
                {
                    load_drivers();
                    unsigned short rate = 0;
                    std::string driver_name;
                    std::cout << "Enter the rating for driver:\n";
                    std::cin >> rate;
                    std::cout << "Enter driver name:\n";
                    std::cin >> driver_name;

                    for (auto& d : drivers)
                    {
                        if (d.get_name() == driver_name)
                        {
                            d.set_rating(rate);
                        }
                    }
                    unload_drivers();
                    break;
                }
                case 4:
                {
                    std::cout << "Exiting...\n";
                    return;
                }
                default:
                    std::cout << "Invalid choice!\n";
                    break;
                }
            }
            break;
        }
        case 2:
        {
            std::string login;
            std::string password;
            std::cout << "Enter login to authorization\n";
            std::cin >> login;
            std::cout << "Enter password to authorization\n";
            std::cin >> password;
            load_drivers();
            Driver* driver = nullptr;

            bool found = false;
            for (unsigned int i = 0; i < drivers.size(); i++)
            {
                if (drivers[i].get_login() == login && drivers[i].get_password() == password)
                {
                    driver = &drivers[i];
                    found = true;
                    break; 
                }
            }
            if (!found)
            {
                std::cout << "Wrong login or password!\n";
                return;
            }

            while (true)
            {
                std::cout << "Choose what you want to do? (1: Check orders / 2: Complete order / 3: Check rating / 4: Log out)\n";
                std::cin >> choose;
                if (choose != 1 && choose != 2 && choose != 3 && choose != 4)
                {
                    break;
                }
                switch (choose)
                {
                case 1:
                {
                    load_trips();
                    for (auto& trip : trips)
                    {
                        if (trip.get_driver().get_login() == driver->get_login())
                        {
                            std::cout << "Order Created\n";
                        }
                        else if (trip.get_status() == TripStatus::InProgress)
                        {
                            std::cout << "Order In Progress\n";
                        }
                        else if (trip.get_status() == TripStatus::Completed)
                        {
                            std::cout << "Order Completed\n";
                        }
                    }
                        
                    break;
                }
                case 2:
                {
                    load_trips();
                    for (auto& trip : trips)
                    {
                        if (trip.get_driver().get_login() == driver->get_login())
                        {
                            trip.set_status(TripStatus::Completed);
                        }
                    }
                    std::cout << "Orders completed.\n";
                    
                    break;
                }
                case 3:
                {
                    std::cout << "Your rating: " << driver->get_rating() << '\n';
                    break;
                }
                case 4:
                {
                    std::cout << "Logging out...\n";
                    return;
                }
                default:
                    std::cout << "Invalid choice!\n";
                    break;
                }
            }
            break;
        }
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}

void print_drivers()
{
    load_drivers();
    for (unsigned int i = 0; i < drivers.size(); i++)
    {
        std::cout << drivers[i].get_name() << '\n';
        std::cout << drivers[i].get_login() << '\n';
        std::cout << drivers[i].get_password() << '\n';
        std::cout << drivers[i].get_rating() << '\n';
        std::cout << drivers[i].get_car()->getType() << '\n';
        std::cout << drivers[i].get_car()->getModel() << '\n';
        std::cout << drivers[i].get_car()->getBrand() << '\n';
        std::cout << drivers[i].get_car()->getMileage() << '\n';
    }
}
