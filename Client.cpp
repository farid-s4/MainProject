#include "Client.h"

#include <iostream>
#include <windows.h>


Client::Client() : uuid_("00000000-0000-0000-0000-000000000000"){}
Client::Client(std::string UUID) : uuid_(UUID){}
Client::Client(const std::string& user_name, const std::string& login,
       const std::string& password, const std::string& UUID, unsigned short rating, unsigned short ratingCount)
    : User(user_name, login, password, rating, ratingCount),
      uuid_(UUID) {}

Client::Client(const Client& other) : User(other), uuid_(other.uuid_){}
Client::Client(Client&& other) noexcept : User(std::move(other)),  uuid_(std::move(other.uuid_)){}
Client& Client::operator=(Client&& other) noexcept
{
    if (this != &other)
    {
        User::operator=(std::move(other));
        uuid_ = std::move(other.uuid_);
        return *this;
    }
    return *this;
}
Client& Client::operator=(const Client& other)
{
    if (this != &other)
    {
        User::operator=(other);
        uuid_ = other.uuid_;
    }
    return *this;
}
void Client::set_uuid(std::string UUID)
{
    uuid_ = UUID;
}
const std::string Client::get_name()
{
    return _user_name;
}
const std::string& Client::get_uuid()
{
    return uuid_;
}
void Client::genenerate_uuid()
{
    UUID uuid;
    UuidCreate(&uuid);

    unsigned char* str;
    UuidToStringA(&uuid, &str);

    uuid_ = reinterpret_cast<char*>(str); 
    
    RpcStringFreeA(&str);
}


void Client::print_info() const
{
    std::cout << _login << std::endl;
    std::cout << _user_name << std::endl;
    std::cout << _rating << std::endl;
    std::cout << _password << std::endl;
    std::cout << uuid_ << std::endl;
}

void write_clients(std::string filename, std::vector<Client>& data)
{
    std::ofstream out(filename, std::ios::binary);

    if (!out)
    {
        throw std::exception();
    }

    for (int i = 0; i < data.size(); i++)
    {
        size_t user_name_size = data[i].get_name().size();
        size_t login_size = data[i].get_login().size();
        size_t password_size = data[i].get_password().size();
        size_t uuiq_size = data[i].get_uuid().size();
        out.write(reinterpret_cast<char*>(&user_name_size), sizeof(size_t));
        out.write(data[i].get_name().c_str(), user_name_size);

        out.write(reinterpret_cast<char*>(&login_size), sizeof(size_t));
        out.write(data[i].get_login().c_str(), login_size);

        out.write(reinterpret_cast<char*>(&password_size), sizeof(size_t));
        out.write(data[i].get_password().c_str(), password_size);

        out.write(reinterpret_cast<char*>(&uuiq_size), sizeof(size_t));
        out.write(data[i].get_uuid().c_str(), uuiq_size);

        unsigned short rating = data[i].get_rating();
        out.write(reinterpret_cast<char*>(&rating), sizeof(unsigned short));

        unsigned short ratingCount = data[i].get_rating_count(); 
        out.write(reinterpret_cast<const char*>(&ratingCount), sizeof(unsigned short));
    }
    out.close();
}

void read_clients(const std::string& filename, std::vector<Client>& data) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        throw std::runtime_error("Can not open file");
    }

    while (fin.peek() != EOF) {
        size_t user_name_size, login_size, password_size, uuid_size;
        std::string user_name, login, password, uuid;
        unsigned short rating,ratingCount;

        if (!fin.read(reinterpret_cast<char*>(&user_name_size), sizeof(size_t))) break;
        user_name.resize(user_name_size);
        if (!fin.read(&user_name[0], user_name_size)) break;

        if (!fin.read(reinterpret_cast<char*>(&login_size), sizeof(size_t))) break;
        login.resize(login_size);
        if (!fin.read(&login[0], login_size)) break;

        if (!fin.read(reinterpret_cast<char*>(&password_size), sizeof(size_t))) break;
        password.resize(password_size);
        if (!fin.read(&password[0], password_size)) break;

        if (!fin.read(reinterpret_cast<char*>(&uuid_size), sizeof(size_t))) break;
        uuid.resize(uuid_size);
        if (!fin.read(&uuid[0], uuid_size)) break;

        if (!fin.read(reinterpret_cast<char*>(&rating), sizeof(unsigned short))) break;

        if (!fin.read(reinterpret_cast<char*>(&ratingCount), sizeof(unsigned short))) break;

        Client client(user_name, login, password, uuid, rating, ratingCount);
        data.push_back(client);
    }

    if (!fin.eof()) {
        throw std::runtime_error("Error in read file");
    }
}
