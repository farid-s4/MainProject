#pragma comment(lib, "Rpcrt4.lib")
#include <iostream>
#include "interface.h"

int main() {
    std::cout << "Welcome to the Taxi Service!\n";

    while (true) {
        std::cout << "\nPlease choose an option:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Authorization\n";
        std::cout << "3. AdminMenu\n";
        std::cout << "4. Exit\n";
        std::cout << "Your choice: ";

        std::string choice;
        std::cin >> choice;

        if (choice == "1") {
            registration();
        }
        else if (choice == "2") {
            authorization();
        }
        else if (choice == "3")
        {
            adminMenu();
        }
        else if (choice == "4") {
            std::cout << "Exiting the program...\n";
            break;
        }
        else {
            std::cout << "Invalid input. Please enter 1, 2, or 3.\n";
        }
    }
    
    return 0;
}
