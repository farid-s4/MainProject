#include "User.h"
#include <stdexcept>

User::User()
    : _user_name("Unknown"), _login("Unknown"), _password("Unknown"), _rating(1), _ratingCount(1) {}

User::User(const std::string& user_name, const std::string& login, const std::string& password, unsigned short rating, unsigned short rating_count)
    : _user_name(user_name), _login(login), _password(password), _rating(rating), _ratingCount(1) {}

User::User(const User& other)
    : _user_name(other._user_name),
      _login(other._login),
      _password(other._password),
      _rating(other._rating),
      _ratingCount(other._ratingCount) {}

User::User(User&& other) noexcept
    : _user_name(std::move(other._user_name)),
      _login(std::move(other._login)),
      _password(std::move(other._password)),
      _rating(other._rating),
      _ratingCount(other._ratingCount) {}

User& User::operator=(const User& other)
{
    if (this != &other)
    {
        _user_name = other._user_name;
        _login = other._login;
        _password = other._password;
        _rating = other._rating;
        _ratingCount = other._ratingCount;
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
        _ratingCount = other._ratingCount;
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

const std::string& User::get_name() const
{
    return _user_name;
}

const std::string& User::get_login() const
{
    return _login;
}

const std::string& User::get_password() const
{
    return _password;
}
unsigned short User::get_rating_count() const
{
    return _ratingCount;
}
unsigned short User::set_rating(unsigned short rating)
{
    if (rating > 0 && rating < 11)
    {
        _rating = (_rating * _ratingCount + rating) / (_ratingCount + 1);
        ++_ratingCount;
        return _rating;
    }
    else
    {
        throw std::invalid_argument("Rating must be between 1 and 10.");
    }
}

unsigned short User::get_rating() const
{
    return _rating;
}