#include "User.h"

#include <stdexcept>
User::User(): _user_name("Unknown"), _login("Unknown"), _password("Unknown"), _rating(0) {}
User::User(const std::string& user_name, const std::string& login, const std::string& password, unsigned short rating) : _user_name(user_name), _login(login), _password(password), _rating(rating) {}
User::User(const User& other)
    : _user_name(other._user_name),
      _login(other._login),
      _password(other._password),
      _rating(other._rating) {}
User::User(User&& other) noexcept
    : _user_name(std::move(other._user_name)),
      _login(std::move(other._login)),
      _password(std::move(other._password)),
      _rating(other._rating) {}

User& User::operator=(const User& other)
{
    if (this != &other)
    {
        _user_name = other._user_name;
        _login = other._login;
        _password = other._password;
        _rating = other._rating;
    }
    return *this;
}


User& User::operator=(User&& other) noexcept
{
    if (this != &other)
    {
        _user_name = std::move(other._user_name);
        _login = std::move(other._login);
        _password = std::move(other._password);
        _rating = other._rating;
    }
    return *this;
}
void User::set_name(const std::string& name)
{
    _user_name = name;
}
void User::set_login(const std::string& login)
{
    _login = login;
}
void User::set_password(const std::string& password)
{
    _password = password;
}
const std::string& User::get_name() const {
    return _user_name;
}

const std::string& User::get_login() const {
    return _login;
}

const std::string& User::get_password() const {
    return _password;
}
unsigned short User::set_rating(unsigned short rating)
{
    if (rating > 0 && rating <= 10)
    {
        _rating = rating;
        return _rating;
    }
    else
    {
        throw std::invalid_argument("Rating must be between 1 and 10.");
    }
}

unsigned short User::get_rating()
{
    return _rating;
}

