#pragma once
#include <string>
class Driver;
class Client;
class User
{
protected:
    std::string _user_name;
    std::string _login;
    std::string _password;
    unsigned short _rating;
public:
    virtual ~User() = default;

    User();
    User(const std::string& user_name, const std::string& login, const std::string& password, unsigned short rating);
    User(const User& other);
    User(User&& other) noexcept;
    User& operator=(const User& other);
    User& operator=(User&& other) noexcept;
    
    void set_name(const std::string& name);
    void set_login(const std::string& login);
    void set_password(const std::string& password);

    const std::string& get_name() const;
    const std::string& get_login() const;
    const std::string& get_password() const;

    unsigned short set_rating(unsigned short rating);
    unsigned short get_rating() const;


    virtual void rate_driver(Driver& driver,unsigned short rating) {}
    virtual void rate_client(Client& client, unsigned short rating) {}
    
};