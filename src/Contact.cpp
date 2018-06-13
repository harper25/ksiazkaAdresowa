#include "Contact.h"
#include <iostream>
using namespace std;

int Contact::nextId = 1;

Contact::Contact(int userId, string name, string surname,
                string phoneNumber, string email, string address)
{
    setId(nextId++);
    setUserId(userId);
    setName(name);
    setSurname(surname);
    setAddress(address);
    setPhoneNumber(phoneNumber);
    setEmail(email);
}

Contact::Contact(int id, int userId, string name, string surname,
                string phoneNumber, string email, string address)
{
    setId(id);
    setUserId(userId);
    setName(name);
    setSurname(surname);
    setAddress(address);
    setPhoneNumber(phoneNumber);
    setEmail(email);
    if (id >= nextId)
        nextId = id + 1;
}

void Contact::showContact()
{
    cout << getName() << " " << getSurname() << endl;
    cout << "Phone number: " << getPhoneNumber() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Address: " << getAddress() << endl;
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
string Contact::getName()
{
    return name;
}
void Contact::setName(string iname)
{
    name = iname;
}
string Contact::getSurname()
{
    return surname;
}
void Contact::setSurname(string isurname)
{
    surname = isurname;
}
string Contact::getAddress()
{
    return address;
}
void Contact::setAddress(string iaddress)
{
    address = iaddress;
}
string Contact::getPhoneNumber()
{
    return phoneNumber;
}
void Contact::setPhoneNumber(string iphoneNumber)
{
    phoneNumber = iphoneNumber;
}
string Contact::getEmail()
{
    return email;
}
void Contact::setEmail(string iemail)
{
    email = iemail;
}
