#include "interface.h"

std::vector<Driver> drivers;
std::vector<Client> clients;
std::vector<Trip> trips;

void clearInputBuffer() {
    while (std::cin.get() != '\n');
}

void loadClients() {
    try {
        read_clients("AllData/clients.bin", clients);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void unloadClients() {
    try {
        write_clients("AllData/clients.bin", clients);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void loadDrivers() {
    try {
        read_drivers("AllData/drivers.bin", drivers);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void unloadDrivers() {
    try {
        write_drivers("AllData/drivers.bin", drivers);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void loadTrips() {
    try {
        read_orders("AllData/orders.txt", trips);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void unloadTrips() {
    try {
        write_orders("AllData/orders.txt", trips);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

bool isValidPassword(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasLetter = false, hasDigit = false, hasSpecial = false;
    for (char ch : password) {
        if (std::isalpha(ch)) hasLetter = true;
        else if (std::isdigit(ch)) hasDigit = true;
        else hasSpecial = true;
    }
    return hasLetter && hasDigit && hasSpecial;
}

void registerClient() {
    loadClients();
    bool flag = true;
    std::string name, login, password;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    while (true)
    {
        std::cout << "Enter your login (no spaces allowed): ";
        std::getline(std::cin, login);
        
        if (login.find(' ') != std::string::npos)
        {
            std::cout << "Login cannot contain spaces. Please try again.\n";
        }
        else
        {
            break; 
        }
    }
    
    bool loginExists = false;
    for (const auto& client : clients) {
        if (client.get_login() == login) {
            loginExists = true;
            break;
        }
    }
    if (loginExists) {
        std::cout << "Login already in use.\n";
        return;
    }

    do {
        while (true)
        {
            std::cout << "Enter your password (no spaces allowed): ";
            std::getline(std::cin, password);
        
            if (login.find(' ') != std::string::npos)
            {
                std::cout << "Password cannot contain spaces. Please try again.\n";
            }
            else
            {
                break; 
            }
        }
        
        if (!isValidPassword(password)) {
            std::cout << "Password is unsafe (min 8 chars, letter, digit, special char).\n";
        }
    } while (!isValidPassword(password));

    Client newClient;
    newClient.set_name(name);
    newClient.set_login(login);
    newClient.set_password(password);
    newClient.set_rating(10);
    newClient.genenerate_uuid();
    clients.push_back(newClient);
    
    unloadClients();
    std::cout << "Client registered successfully.\n";
}

void registerDriver() {
    loadDrivers();
    
    std::string name, login, password, brand, model, carType;
    std::string carTypeChoice;
    unsigned short carChoice;
    unsigned short year;
    unsigned int mileage;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    while (true)
    {
        std::cout << "Enter your login (no spaces allowed): ";
        std::getline(std::cin, login);
        
        if (login.find(' ') != std::string::npos)
        {
            std::cout << "Login cannot contain spaces. Please try again.\n";
        }
        else
        {
            break; 
        }
    }

    bool loginExists = false;
    for (const auto& driver : drivers) {
        if (driver.get_login() == login) {
            loginExists = true;
            break;
        }
    }
    if (loginExists) {
        std::cout << "Login already in use.\n";
        return;
    }

    do {
        while (true)
        {
            std::cout << "Enter your password (no spaces allowed): ";
            std::getline(std::cin, password);
        
            if (login.find(' ') != std::string::npos)
            {
                std::cout << "Password cannot contain spaces. Please try again.\n";
            }
            else
            {
                break; 
            }
        }
        
        if (!isValidPassword(password)) {
            std::cout << "Password is unsafe (min 8 chars, letter, digit, special char).\n";
        }
    } while (!isValidPassword(password));

    std::cout << "Enter your car brand: ";
    std::getline(std::cin, brand);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter your car model: ";
    std::getline(std::cin, model);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Choose car type (1 - Econom, 2 - Comfort, 3 - Business): ";
    std::cin >> carTypeChoice;
    if (carTypeChoice == "1")
    {
        carChoice = 1;
    }
    if (carTypeChoice == "2")
    {
        carChoice = 2;
    }
    if (carTypeChoice == "3")
    {
        carChoice = 3;
    }
    
    while (true) {
        std::cout << "Enter car manufacture year: ";
        std::cin >> year;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter a valid year (numbers only).\n";
        } else {
            break; 
        }
    }

    
    while (true) {
        std::cout << "Enter car mileage (km): ";
        std::cin >> mileage;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter mileage in digits only.\n";
        } else {
            break;
        }
    }

    switch (carChoice) {
        case 1: carType = "econom"; break;
        case 2: carType = "comfort"; break;
        case 3: carType = "business"; break;
        default: carType = "econom"; break;
    }

    Car* car = nullptr;
    if (carType == "econom") car = new EconomCar(brand, model, carType, year, mileage);
    else if (carType == "comfort") car = new ComfortCar(brand, model, carType, year, mileage);
    else if (carType == "business") car = new BusinessCar(brand, model, carType, year, mileage);

    Driver newDriver;
    newDriver.set_name(name);
    newDriver.set_login(login);
    newDriver.set_password(password);
    newDriver.set_rating(10);
    newDriver.set_car(car);
    newDriver.generate_license_number();

    drivers.push_back(newDriver);
    unloadDrivers();

    delete car;
    std::cout << "Driver registered successfully.\n";
}

void registration() {
    std::string choice;
    std::cout << "Who are you? (1 - Client, 2 - Driver): ";
    std::cin >> choice;

    if (choice == "1" || choice == "client" || choice == "Client") {
        registerClient();
    } else if (choice == "2" || choice == "driver" || choice == "Driver") {
        registerDriver();
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void authorization() {
    std::string choice;
    std::cout << "Who are you? (1 - Client, 2 - Driver): ";
    std::cin >> choice;

    if (choice == "1" || choice == "client" || choice == "Client") {
        loadClients();
        std::string login, password;
        
        while (true)
        {
            std::cout << "Enter your login (no spaces allowed): ";
            std::getline(std::cin, login);
        
            if (login.find(' ') != std::string::npos)
            {
                std::cout << "Login cannot contain spaces. Please try again.\n";
            }
            else
            {
                break; 
            }
        }
        while (true)
        {
            std::cout << "Enter your password (no spaces allowed): ";
            std::getline(std::cin, password);
        
            if (login.find(' ') != std::string::npos)
            {
                std::cout << "Password cannot contain spaces. Please try again.\n";
            }
            else
            {
                break; 
            }
        }

        bool found = false;
        Client authorizedClient;
        for (const auto& client : clients) {
            if (client.get_login() == login && client.get_password() == password) {
                authorizedClient = client;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Wrong login or password.\n";
            return;
        }

        while (true) {
            std::cout << "\n1 - Book ride\n2 - View trips\n3 - Rate Driver\n4 - Exit\nChoice: ";
            std::cin >> choice;
            if (choice == "1") {
                loadDrivers();
                loadTrips();

                std::string firstPoint, lastPoint;
                double distance;
                std::string carTypeChoice;
                std::string car_case_shoose;
                int carType;
                while (true) {
                    std::cout << "Enter distance (km): ";
                    std::cin >> distance;

                    if (std::cin.fail() || distance <= 0) {
                        std::cin.clear(); 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                        std::cout << "Invalid input. Please enter a positive number for distance.\n";
                    } else {
                        break;
                    }
                }

                std::cout << "Choose car type (1 - Econom, 2 - Comfort, 3 - Business): ";
                std::cin >> car_case_shoose;
                std::cin.ignore();
                std::cout << "Enter starting point: ";
                std::getline(std::cin, firstPoint);
                std::cout << "Enter destination point: ";
                std::getline(std::cin, lastPoint);

                if (car_case_shoose == "1")
                {
                    carType = 1;
                }
                if (car_case_shoose == "2")
                {
                    carType = 2;
                }
                if (car_case_shoose == "3")
                {
                    carType = 3;
                }
                
                switch (carType) {
                    case 1: carTypeChoice = "econom"; break;
                    case 2: carTypeChoice = "comfort"; break;
                    case 3: carTypeChoice = "business"; break;
                    default: carTypeChoice = "econom"; break;
                }

                bool driverFound = false;
                Driver selectedDriver;
                for (const auto& driver : drivers) {
                    if (driver.get_car()->getType() == carTypeChoice) {
                        selectedDriver = driver;
                        driverFound = true;
                        break;
                    }
                }

                if (!driverFound) {
                    std::cout << "No drivers available.\n";
                    return;
                }

                Trip trip(firstPoint, lastPoint, selectedDriver, authorizedClient, TripStatus::Created, distance);
                trip.calculate_price(selectedDriver, distance);
                trips.push_back(trip);
                unloadTrips();
                
                std::cout << "Trip booked successfully with driver: " << selectedDriver.get_name() << '\n';

            }
            else if (choice == "2") {
                loadTrips();
                bool foundTrips = false;
                for (auto& trip : trips) {
                    if (trip.get_client().get_login() == authorizedClient.get_login()) {
                        std::cout << "Trip from " << trip.get_first_point()
                                  << " to " << trip.get_last_point()
                                  << " costs " << trip.get_price() << '\n';
                        foundTrips = true;
                    }
                }
                if (!foundTrips) {
                    std::cout << "No trips found.\n";
                }
            }
            else if (choice == "3")
            {
                loadDrivers();
                std::string driverName;
                unsigned short rating = 0;

                
                while (true) {
                    std::cout << "Enter rating (1 - 10): ";
                    std::cin >> rating;

                    if (std::cin.fail()) {
                        std::cin.clear(); 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                        std::cout << "Invalid input. Please enter a number from 1 to 10.\n";
                        continue;
                    }

                    if (rating < 1 || rating > 10) {
                        std::cout << "Rating must be between 1 and 10.\n";
                        continue;
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    break;
                }

                std::cout << "Enter driver name: ";
                std::getline(std::cin, driverName); 

                Driver* selectedDriver = nullptr;

                for (auto& driver : drivers) {
                    if (driver.get_name() == driverName) {
                        selectedDriver = &driver;
                        break;
                    }
                }

                if (!selectedDriver) {
                    std::cout << "No driver with that name found.\n";
                    return;
                }

                selectedDriver->set_rating(rating);
                std::cout << "Trip booked successfully with driver: " << selectedDriver->get_name() << '\n';
                unloadDrivers();
            }
            else if (choice == "4")
            {
                return;
            }
        }
    } else if (choice == "2" || choice == "driver" || choice == "Driver") {
        loadDrivers();
        std::string login, password;

        while (true)
        {
            std::cout << "Enter your login (no spaces allowed): ";
            std::getline(std::cin, login);
        
            if (login.find(' ') != std::string::npos)
            {
                std::cout << "Login cannot contain spaces. Please try again.\n";
            }
            else
            {
                break; 
            }
        }
        while (true)
        {
            std::cout << "Enter your password (no spaces allowed): ";
            std::getline(std::cin, password);
        
            if (login.find(' ') != std::string::npos)
            {
                std::cout << "Password cannot contain spaces. Please try again.\n";
            }
            else
            {
                break; 
            }
        }
        
        Driver* authorizedDriver = nullptr;
        for (auto& driver : drivers) {
            if (driver.get_login() == login && driver.get_password() == password) {
                authorizedDriver = &driver;
                break;
            }
        }
        if (!authorizedDriver) {
            std::cout << "Wrong login or password.\n";
            return;
        }

        while (true) {
            std::cout << "\n1 - View orders\n2 - Complete order\n3 - Check rating\n4 - Logout\nChoice: ";
            std::cin >> choice;
            if (choice == "1") {
                loadTrips();
                for (auto& trip : trips) {
                    std::cout<< trip.get_first_point() << "->" << trip.get_last_point() << '\n' << trip.get_price() << '\n';
                }
            }
            else if (choice == "2") {
                loadTrips();
                for (auto& trip : trips) {
                    if (trip.get_driver().get_login() == authorizedDriver->get_login()) {
                        trip.set_status(TripStatus::Completed);
                    }
                }
                unloadTrips();
                std::cout << "All your trips are now marked as Completed.\n";
            }
            else if (choice == "3") {
                std::cout << "Your rating: " << authorizedDriver->get_rating() << '\n';
            }
            else if (choice == "4") {
                std::cout << "Logging out...\n";
                break;
            }
            else {
                std::cout << "Invalid choice.\n";
            }
        }
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void printDrivers() {
    loadDrivers();
    for (const auto& driver : drivers) {
        std::cout << driver.get_name() << ", "
                  << driver.get_login() << ", "
                  << driver.get_car()->getBrand() << " "
                  << driver.get_car()->getModel() << " ("
                  << driver.get_car()->getType() << ")\n";
    }
}
