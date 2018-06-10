#ifndef CONTACTSMANAGER_H
#define CONTACTSMANAGER_H

#include "Contact.h"
#include "FileContacts.h"
#include "Conversion.h"
#include <vector>

class ContactsManager
{
    public:
        ContactsManager(std::string = "contactData.txt");
        void loadContacts(int loggedUserId);
        void addNewContact(int loggedUserId);
        void showContacts();
        void deleteContact(int loggedUserId);
        void editContact(int loggedUserId);
        void findContactByName();
        void findContactBySurname();
        void clearData();
        void showReturnMessage();
        int getContactsCount();

    protected:

    private:
        std::vector <Contact> contacts;
        std::vector <int> indicesOfMatchingContacts;
        FileContacts fileContacts;
        int chooseContact();
        Conversion conversion;
        void editDataOfOneContact(int);
};

#endif // CONTACTSMANAGER_H
