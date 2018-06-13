#ifndef CONTACTSMANAGER_H
#define CONTACTSMANAGER_H

#include "Contact.h"
#include "FileContacts.h"
#include "Conversion.h"
#include <vector>

class ContactsManager
{
    public:
        ContactsManager(int loggedUserId, std::string = "contactData.txt");
        void loadContacts();
        void addNewContact();
        void showContacts();
        void deleteContact();
        void editContact();
        void findContactByName();
        void findContactBySurname();
        void clearData();
        void showReturnMessage();
        int  getContactsCount();

    protected:

    private:
        std::vector <Contact> contacts;
        std::vector <int> indicesOfMatchingContacts;
        FileContacts fileContacts;
        int chooseContact();
        Conversion conversion;
        void editDataOfOneContact(int);
        void setLoggedUserId(int);
        int loggedUserId;
};

#endif // CONTACTSMANAGER_H
