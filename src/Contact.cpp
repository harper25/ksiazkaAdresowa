#include "Contact.h"
#include <iostream>

int Contact::nextId = 1;

Contact::Contact(int userId, std::string name, std::string surname,
                std::string phoneNumber, std::string email, std::string address)
{
    setId(nextId++);
    setUserId(userId);
    setName(name);
    setSurname(surname);
    setAddress(address);
    setPhoneNumber(phoneNumber);
    setEmail(email);
}

Contact::Contact(int id, int userId, std::string name, std::string surname,
                std::string phoneNumber, std::string email, std::string address)
                :Contact(userId, name, surname, phoneNumber, email, address)
{
    setId(id);
    if (id >= nextId)
        nextId = id + 1;
}

void Contact::showContact()
{
    std::cout << getName() << " " << getSurname() << std::endl;
    std::cout << "Phone number: " << getPhoneNumber() << std::endl;
    std::cout << "Email: " << getEmail() << std::endl;
    std::cout << "Address: " << getAddress() << std::endl;
}

int Contact::getId()
{
    return id;
}

void Contact::setId(int iid)
{
    id = iid;
}
int Contact::getUserId()
{
    return userId;
}
void Contact::setUserId(int iuserId)
{
    userId = iuserId;
}
std::string Contact::getName()
{
    return name;
}
void Contact::setName(std::string iname)
{
    name = iname;
}
std::string Contact::getSurname()
{
    return surname;
}
void Contact::setSurname(std::string isurname)
{
    surname = isurname;
}
std::string Contact::getAddress()
{
    return address;
}
void Contact::setAddress(std::string iaddress)
{
    address = iaddress;
}
std::string Contact::getPhoneNumber()
{
    return phoneNumber;
}
void Contact::setPhoneNumber(std::string iphoneNumber)
{
    phoneNumber = iphoneNumber;
}
std::string Contact::getEmail()
{
    return email;
}
void Contact::setEmail(std::string iemail)
{
    email = iemail;
}
