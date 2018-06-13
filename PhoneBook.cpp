#include <iostream>
#include <windows.h>
#include "User.h"
#include "UsersManager.h"
#include "File.h"
#include "FileUsers.h"
#include "Contact.h"
#include "ContactsManager.h"

using namespace std;

void showWelcomeMenu()
{
    system("cls");
    cout << "Phone Book" << endl << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. Log in" << endl;
    cout << "9. Exit" << endl << endl;
}

void showUserMenu()
{
    system("cls");
    cout << "Phone Book --> User Menu: " << endl << endl;
    cout << "1. Add new contact" << endl;
    cout << "2. Find contact by name" << endl;
    cout << "3. Find contact by surname" << endl;
    cout << "4. Edit contact" << endl;
    cout << "5. Delete contact" << endl;
    cout << "6. Show all contacts" << endl;
    cout << "7. Change password" << endl;
    cout << "8. Log out" << endl << endl;
}


int main()
{
    UsersManager usersManager;
    string choice;

    while(1)
    {
        showWelcomeMenu();
        cout << "Your choice: ";
        cin.sync();
        getline(cin, choice);
        if ((choice.length() > 1) || (!isdigit(choice[0])))
        {
            choice = "0";
        }

        switch (choice[0])
        {
        case '1':
            usersManager.registerNewUser();
            break;
        case '2':
            usersManager.logging();
            if (usersManager.getLoggedUserId() != 0)
            {
                ContactsManager contactsManager(usersManager.getLoggedUserId());

                while (usersManager.getLoggedUserId() != 0)
                {
                    showUserMenu();
                    cout << "Your choice: ";
                    cin.sync();
                    getline(cin, choice);
                    if ((choice.length() > 1) || (!isdigit(choice[0])))
                    {
                        choice = "0";
                    }

                    switch (choice[0])
                    {
                    case '1':
                        contactsManager.addNewContact();
                        break;
                    case '2':
                        contactsManager.findContactByName();
                        if (contactsManager.getContactsCount() > 0)
                            contactsManager.showReturnMessage();
                        break;
                    case '3':
                        contactsManager.findContactBySurname();
                        if (contactsManager.getContactsCount() > 0)
                            contactsManager.showReturnMessage();
                        break;
                    case '4':
                        contactsManager.editContact();
                        break;
                    case '5':
                        contactsManager.deleteContact();
                        break;
                    case '6':
                        contactsManager.showContacts();
                        if (contactsManager.getContactsCount() > 0)
                            contactsManager.showReturnMessage();
                        break;
                    case '7':
                        usersManager.changePassword();
                        break;
                    case '8':
//                        delete contactsManager;
                        contactsManager.clearData();
                        usersManager.setLoggedUserId(0);
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        Sleep(1000);
                    }
                }
            }
            break;
        case '9':
            system("cls");
            cout << "Good bye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
        }
    }
}
