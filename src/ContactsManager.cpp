#include "ContactsManager.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

ContactsManager::ContactsManager(int loggedUserId, string ifilename)
    : fileContacts(ifilename)
{
    setLoggedUserId(loggedUserId);
    loadContacts();
}

void ContactsManager::setLoggedUserId(int iloggedUserId)
{
    loggedUserId = iloggedUserId;
}

int ContactsManager::getContactsCount()
{
    return contacts.size();
}

void ContactsManager::loadContacts()
{
    contacts = fileContacts.readContactsFromFile(loggedUserId);
}

void ContactsManager::clearData()
{
    contacts.clear();
    indicesOfMatchingContacts.clear();
    loggedUserId = 0;
}

void ContactsManager::addNewContact()
{
    string name, surname, address, phoneNumber, email;
    system("cls");
    cout << "Phone Book --> User Menu --> New contact" << endl << endl;
    cout << "Please, enter a name: ";
    cin.sync();
    getline(cin, name);
    cout << "Please, enter a surname: ";
    cin.sync();
    getline(cin, surname);
    cout << "Please, enter phone number: ";
    cin.sync();
    getline(cin, phoneNumber);
    cout << "Please, enter an email: ";
    cin >> email;
    cout << "Please, enter an address: ";
    cin.sync();
    getline(cin, address);
    Contact newContact(loggedUserId, name, surname, phoneNumber, email, address);
    contacts.push_back(newContact);

    fileContacts.addOneContactToContactFile(newContact);

    cout << endl << "New contact added!";
    Sleep(1000);
}

void ContactsManager::showContacts()
{
    system("cls");
    cout << "Phone Book --> User Menu --> All contacts" << endl;
    int contactsCount = contacts.size();

    if (contactsCount == 0)
    {
        cout << endl << "There is no contacts!" << endl;
        Sleep(1000);
        return;
    }

    indicesOfMatchingContacts.clear();

    for (int i = 0; i < contactsCount; i++)
    {
        cout << endl << i+1 << ". ";
        contacts[i].showContact();
        indicesOfMatchingContacts.push_back(i);
    }
}

int ContactsManager::chooseContact()
{
    indicesOfMatchingContacts.clear();
    string userInputNumber;
    int numberOfContactToBeDeleted;
    string choice;

    cout << endl << "1. Show all contacts" << endl;
    cout << "2. Find contact by name" << endl;
    cout << "3. Find contact by surname" << endl;
    cout << "4. Return to User Menu" << endl;
    cout << endl << "Your choice: ";

    cin.sync();
    getline(cin, choice);

    if ((choice.length() != 1) || (!isdigit(choice[0])))
    {
        cout << "Invalid input!" << endl;
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
        cout << "Invalid input!" << endl;
        Sleep(1000);
        return -1;
    }

    if (indicesOfMatchingContacts.empty())
    {
        return -1;
    }

    cout << endl << "Choose contact from the list (0 - return to User Menu): ";
    cin.sync();
    getline(cin,userInputNumber);

    for (int i = 0; i < userInputNumber.length(); i++)
    {
        if (!isdigit(userInputNumber[i]))
        {
            cout << "Invalid input!" << endl;
            Sleep(1000);
            return -1;
        }
    }

    numberOfContactToBeDeleted = conversion.string2int(userInputNumber);

    if (numberOfContactToBeDeleted > indicesOfMatchingContacts.size())
    {
        cout << "Invalid input!" << endl;
        Sleep(1000);
        return -1;
    }
    else
    {
        return numberOfContactToBeDeleted - 1;
    }
}

void ContactsManager::deleteContact()
{
    system("cls");
    cout << "Phone Book --> User Menu --> Delete contact" << endl;

    if (contacts.size() == 0)
    {
        cout << endl << "There is no contacts!" << endl;
        Sleep(1000);
        return;
    }

    int numberOfContactToBeDeleted = chooseContact();
    if (numberOfContactToBeDeleted != -1)
    {
        contacts.erase(contacts.begin() + indicesOfMatchingContacts[numberOfContactToBeDeleted]);
        fileContacts.updateContactsFile(contacts, loggedUserId);
        cout << "Contact deleted!" << endl;
        Sleep(1000);
    }
}


void ContactsManager::editDataOfOneContact(int numberOfContactToBeEdited)
{
    string choice;
    string attribute;
    while(1)
    {
        system("cls");
        cout << "Phone Book --> User Menu --> Edit contact" << endl;
        cout << endl;
        cout << "1. Edit name" << endl;
        cout << "2. Edit surname" << endl;
        cout << "3. Edit phone number" << endl;
        cout << "4. Edit email" << endl;
        cout << "5. Edit address" << endl;
        cout << "6. Finish and return to User Menu" << endl << endl;

        contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).showContact();
        cout << endl << "Your choice: ";

        cin.sync();
        getline(cin, choice);

        if ((choice.length() != 1) || (!isdigit(choice[0])))
        {
            choice = "0";
        }

        switch(choice[0])
        {
        case '1':
            cout << "Please, enter new name: ";
            cin.sync();
            getline(cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setName(attribute);
            break;
        case '2':
            cout << "Please, enter new surname: ";
            cin.sync();
            getline(cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setSurname(attribute);
            break;
        case '3':
            cout << "Please, enter new phone number: ";
            cin.sync();
            getline(cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setPhoneNumber(attribute);
            break;
        case '4':
            cout << "Please, enter new email: ";
            cin.sync();
            getline(cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setEmail(attribute);
            break;
        case '5':
            cout << "Please, enter new address: ";
            cin.sync();
            getline(cin, attribute);
            contacts.at(indicesOfMatchingContacts.at(numberOfContactToBeEdited)).setAddress(attribute);
            break;
        case '6':
            return;
        default:
            cout << "Invalid input!" << endl;
            Sleep(1000);
            break;
        }
    }
}

void ContactsManager::editContact()
{
    system("cls");
    cout << "Phone Book --> User Menu --> Edit contact" << endl;

    if (contacts.size() == 0)
    {
        cout << endl << "There is no contacts!" << endl;
        Sleep(1000);
        return;
    }

    int numberOfContactToBeEdited = chooseContact();
    if (numberOfContactToBeEdited != -1)
    {
        editDataOfOneContact(numberOfContactToBeEdited);
        fileContacts.updateContactsFile(contacts, loggedUserId);
        cout << "Contact edition finished!" << endl;
        Sleep(1000);
    }
}


void ContactsManager::findContactByName()
{
    system("cls");
    cout << "Phone Book --> User Menu --> Find contact by name" << endl;
    int contactsCount = contacts.size();

    if (contactsCount == 0)
    {
        cout << endl << "There is no contacts!" << endl;
        Sleep(1000);
        return;
    }
    indicesOfMatchingContacts.clear();
    string name;
    int matchingContactsCount = 0;
    cout << endl << "Please, give a name: ";
    cin >> name;

    for (int i = 0; i < contactsCount; i++)
    {
        if (contacts[i].getName() == name)
        {
            matchingContactsCount++;
            cout << endl << matchingContactsCount << ". ";
            contacts[i].showContact();
            indicesOfMatchingContacts.push_back(i);
        }
    }
    cout << endl << "Contacts found: " << matchingContactsCount << endl;
}

void ContactsManager::findContactBySurname()
{
    system("cls");
    cout << "Phone Book --> User Menu --> Find contact by surname" << endl;
    int contactsCount = contacts.size();

    if (contactsCount == 0)
    {
        cout << endl << "There is no contacts!" << endl;
        Sleep(1000);
        return;
    }
    indicesOfMatchingContacts.clear();
    string surname;
    int matchingContactsCount = 0;
    cout << endl << "Please, give a surname: ";
    cin >> surname;

    for (int i = 0; i < contactsCount; i++)
    {
        if (contacts[i].getSurname() == surname)
        {
            matchingContactsCount++;
            cout << endl << matchingContactsCount << ". ";
            contacts[i].showContact();
            indicesOfMatchingContacts.push_back(i);
        }
    }
    cout << endl << "Contacts found: " << matchingContactsCount << endl;
}

void ContactsManager::showReturnMessage()
{
    cout << endl << "Press any key to return to User Menu...";
    getch();
}
