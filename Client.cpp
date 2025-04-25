#include "Client.h"

#include <windows.h>


Client::Client() : uuid_("00000000-0000-0000-0000-000000000000"){}
Client::Client(std::string UUID) : uuid_(UUID){}
Client::Client(Car car, const std::string& user_name, const std::string& login,
       const std::string& password, const std::string& UUID, unsigned short rating): User(std::string(user_name),std::string(login), std::string(password), rating),
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


void Client::rate_client(Client& client, unsigned short rating) 
{
    if (count == 0)
    {
        client.set_rating(rating);
    }
    count += 1;
    client.set_rating((_rating + rating) / 2);
    
}

bool Client::write_client(const std::string& filename)
{
    std::ofstream out(filename, std::ios::app);
    if (!out)
    {
        throw std::exception();
    }
    out << _user_name << '\n' << _login
    <<'\n' << _password <<'\n' << _rating
    <<'\n' << uuid_ << '\n' <<"##########" << '\n';
    out.close();
    return true;
}

void read_clients(std::string filename, std::vector<Client>& data)
{
    std::ifstream file(filename); 
    std::string name, login, password, ratingSTR, uuid, line;
    unsigned short rating;
    Client client;

    if (file.is_open()) {
        while (std::getline(file, name) && std::getline(file, login) && std::getline(file, password) && std::getline(file, ratingSTR) &&  std::getline(file, uuid) && std::getline(file, line)) {
            
            client.set_name(name);
            client.set_login(login);
            client.set_password(password);
            int temp_rating = std::stoi(ratingSTR);
            client.set_rating(rating = static_cast<unsigned short>(temp_rating));
            client.set_uuid(uuid);
            data.push_back(client);
        }
        file.close(); 
    } else {
        throw std::exception();
    }
}

void write_clients(std::string filename, std::vector<Client>& data)
{
    std::ofstream out(filename, std::ios::out);
    if (!out)
    {
        throw std::exception();
    }
    
    for (int i = 0; i < data.size(); i++)
    {
        out << data[i].get_name() << '\n' << data[i].get_login()
        <<'\n' << data[i].get_password() <<'\n' << data[i].get_rating()
        <<'\n' << data[i].get_uuid() << '\n' << "##########" << '\n';
    }
    out.close();
}