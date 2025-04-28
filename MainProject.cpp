#pragma comment(lib, "rpcrt4.lib")
#include "interface.h"

int main() //CLEAR AND FİX DATA İN READ!
{
    unsigned short choice;
    
    while (true)
    {
        std::cout << "Welcome! Choose an option:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Authorize (Login)\n";
        std::cout << "3. Exit\n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            reg();  
            break;

        case 2:
            authorization(); 
            break;

        case 3:
            std::cout << "Goodbye!\n";
            return 0;
        }
    }

}
