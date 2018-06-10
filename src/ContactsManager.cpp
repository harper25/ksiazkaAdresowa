#include "ContactsManager.h"
#include <windows.h>
#include <conio.h>
#include <iostream>

ContactsManager::ContactsManager(std::string ifilename)
    : fileContacts(ifilename)
{
}

int ContactsManager::getContactsCount()
{
    return contacts.size();
}

void ContactsManager::loadContacts(int loggedUserId)
{
    contacts = fileContacts.readContactsFromFile(loggedUserId);
}

void ContactsManager::clearData()
{
    contacts.clear();
    indicesOfMatchingContacts.clear();
}

void ContactsManager::addNewContact(int loggedUserId)
{
    std::string name, surname, address, phoneNumber, email;
    system("cls");
    std::cout << "Phone Book --> User Menu --> New contact" << std::endl << std::endl;
    std::cout << "Please, enter a name: ";
    std::cin.sync();
    getline(std::cin, name);
    std::cout << "Please, enter a surname: ";
    std::cin.sync();
    getline(std::cin, surname);
    std::cout << "Please, enter phone number: ";
    std::cin.sync();
    getline(std::cin, phoneNumber);
    std::cout << "Please, enter an email: ";
    std::cin >> email;
    std::cout << "Please, enter an address: ";
    std::cin.sync();
    getline(std::cin, address);
    Contact newContact(loggedUserId, name, surname, phoneNumber, email, address);
    contacts.push_back(newContact);

    fileContacts.addOneContactToContactFile(newContact);

    std::cout << std::endl << "New contact added!";
    Sleep(1000);
}

void ContactsManager::showContacts()
{
    system("cls");
    std::cout << "Phone Book --> User Menu --> All contacts" << std::endl;
    int contactsCount = contacts.size();

    if (contactsCount == 0)
    {
        std::cout << std::endl << "There is no contacts!" << std::endl;
        Sleep(1000);
        return;
    }

    indicesOfMatchingContacts.clear();

    for (int i = 0; i < contactsCount; i++)
    {
        std::cout << std::endl << i+1 << ". ";
        contacts[i].showContact();
        indicesOfMatchingContacts.push_back(i);
    }
}

int ContactsManager::chooseContact()
{
    indicesOfMatchingContacts.clear();
    std::string userInputNumber;
    int numberOfContactToBeDeleted;
    std::string choice;

    std::cout << std::endl << "1. Show all contacts" << std::endl;
    std::cout << "2. Find contact by name" << std::endl;
    std::cout << "3. Find contact by surname" << std::endl;
    std::cout << "4. Return to User Menu" << std::endl;
    std::cout << std::endl << "Your choice: ";

    std::cin.sync();
    getline(std::cin, choice);

    if ((choice.length() != 1) || (!isdigit(choice[0])))
    {
        std::cout << "Invalid input!" << std::endl;
        Sleep(1000);
        return -1;
    }

    switch (choice[0])
    {
    case '1':
        showContacts();
        break;
    case '2':
        findContactByName();
        break;
    case '3':
        findContactBySurname();
        break;
    case '4':
        return -1;
    default:
        std::cout << "Invalid input!" << std::endl;
        Sleep(1000);
        return -1;
    }

    if (indicesOfMatchingContacts.empty())
    {
        return -1;
    }

    std::cout << std::endl << "Choose contact from the list (0 - return to User Menu): ";
    std::cin.sync();
    getline(std::cin,userInputNumber);
    if ((userInputNumber.length() == 1) && (isdigit(userInputNumber[0])))
    {
        numberOfContactToBeDeleted = conversion.string2int(userInputNumber.substr(0,1));
        if (numberOfContactToBeDeleted > indicesOfMatchingContacts.size())
        {
            std::cout << "Invalid input!" << std::endl;
            Sleep(1000);
            return -1;
        }
        else
        {
            return numberOfContactToBeDeleted - 1;
        }
    }
    else
    {
        std::cout << "Invalid input!" << std::endl;
        Sleep(1000);
        return -1;
    }
}

void ContactsManager::deleteContact(int loggedUserId)
{
    system("cls");
    std::cout << "Phone Book --> User Menu --> Delete contact" << std::endl;

    if (contacts.size() == 0)
    {
        std::cout << std::endl << "There is no contacts!" << std::endl;
        Sleep(1000);
        return;
    }

    int numberOfContactToBeDeleted = chooseContact();
    if (numberOfContactToBeDeleted != -1)
    {
        contacts.erase(contacts.begin() + indicesOfMatchingContacts[numberOfContactToBeDeleted]);
        fileContacts.updateContactsFile(contacts, loggedUserId);
        std::cout << "Contact deleted!" << std::endl;
        Sleep(1000);
    }
}


void ContactsManager::editDataOfOneContact(int numberOfContactToBeEdited)
{
    std::string choice;
    std::string attribute;
    while(1)
    {
        system("cls");
        std::cout << "Phone Book --> User Menu --> Edit contact" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Edit name" << std::endl;
        std::cout << "2. Edit surname" << std::endl;
        std::cout << "3. Edit phone number" << std::endl;
        std::cout << "4. Edit email" << std::endl;
        std::cout << "5. Edit address" << std::endl;
        std::cout << "6. Finish and return to User Menu" << std::endl << std::endl;

        contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).showContact();
        std::cout << std::endl << "Your choice: ";

        std::cin.sync();
        getline(std::cin, choice);

        if ((choice.length() != 1) || (!isdigit(choice[0])))
        {
            choice = "0";
        }

        switch(choice[0])
        {
        case '1':
            std::cout << "Please, enter new name: ";
            std::cin.sync();
            getline(std::cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setName(attribute);
            break;
        case '2':
            std::cout << "Please, enter new surname: ";
            std::cin.sync();
            getline(std::cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setSurname(attribute);
            break;
        case '3':
            std::cout << "Please, enter new phone number: ";
            std::cin.sync();
            getline(std::cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setPhoneNumber(attribute);
            break;
        case '4':
            std::cout << "Please, enter new email: ";
            std::cin.sync();
            getline(std::cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setEmail(attribute);
            break;
        case '5':
            std::cout << "Please, enter new address: ";
            std::cin.sync();
            getline(std::cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setAddress(attribute);
            break;
        case '6':
            return;
        default:
            std::cout << "Invalid input!" << std::endl;
            Sleep(1000);
            break;
        }
    }
}

void ContactsManager::editContact(int loggedUserId)
{
    system("cls");
    std::cout << "Phone Book --> User Menu --> Edit contact" << std::endl;

    if (contacts.size() == 0)
    {
        std::cout << std::endl << "There is no contacts!" << std::endl;
        Sleep(1000);
        return;
    }

    int numberOfContactToBeEdited = chooseContact();
    if (numberOfContactToBeEdited != -1)
    {
        editDataOfOneContact(numberOfContactToBeEdited);
        fileContacts.updateContactsFile(contacts, loggedUserId);
        std::cout << "Contact edition finished!" << std::endl;
        Sleep(1000);
    }
}


void ContactsManager::findContactByName()
{
    system("cls");
    std::cout << "Phone Book --> User Menu --> Find contact by name" << std::endl;
    int contactsCount = contacts.size();

    if (contactsCount == 0)
    {
        std::cout << std::endl << "There is no contacts!" << std::endl;
        Sleep(1000);
        return;
    }
    indicesOfMatchingContacts.clear();
    std::string name;
    int matchingContactsCount = 0;
    std::cout << std::endl << "Please, give a name: ";
    std::cin >> name;

    for (int i = 0; i < contactsCount; i++)
    {
        if (contacts[i].getName() == name)
        {
            matchingContactsCount++;
            std::cout << std::endl << matchingContactsCount << ". ";
            contacts[i].showContact();
            indicesOfMatchingContacts.push_back(i);
        }
    }
    std::cout << std::endl << "Contacts found: " << matchingContactsCount << std::endl;
}

void ContactsManager::findContactBySurname()
{
    system("cls");
    std::cout << "Phone Book --> User Menu --> Find contact by surname" << std::endl;
    int contactsCount = contacts.size();

    if (contactsCount == 0)
    {
        std::cout << std::endl << "There is no contacts!" << std::endl;
        Sleep(1000);
        return;
    }
    indicesOfMatchingContacts.clear();
    std::string surname;
    int matchingContactsCount = 0;
    std::cout << std::endl << "Please, give a surname: ";
    std::cin >> surname;

    for (int i = 0; i < contactsCount; i++)
    {
        if (contacts[i].getSurname() == surname)
        {
            matchingContactsCount++;
            std::cout << std::endl << matchingContactsCount << ". ";
            contacts[i].showContact();
            indicesOfMatchingContacts.push_back(i);
        }
    }
    std::cout << std::endl << "Contacts found: " << matchingContactsCount << std::endl;
}

void ContactsManager::showReturnMessage()
{
    std::cout << std::endl << "Press any key to return to User Menu...";
    getch();
}
