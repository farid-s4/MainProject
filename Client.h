#pragma once
#include <fstream>
#include <sstream>

#include "User.h"
#include "Car.h"
#include "CarType.h"
#include <string>
#include  <vector>

class Client : public User
{
private:
    std::string uuid_;
public:
    Client();
    Client(std::string UUID);
    Client(const std::string& user_name, const std::string& login,
           const std::string& password, const std::string& UUID, unsigned short rating, unsigned short ratingCount);
    Client(const Client& other);
    Client(Client&& other) noexcept;
    Client& operator=(Client&& other) noexcept;
    Client& operator=(const Client& other);

    void set_uuid(std::string UUID);
    const std::string& get_uuid();
    
    void genenerate_uuid();
    unsigned short count = 0;

    void print_info() const;

    const std::string get_name();
};

void read_clients(const std::string& filename, std::vector<Client>& data);
void write_clients(std::string filename, std::vector<Client>& data);
