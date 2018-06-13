#include "FileContacts.h"
using namespace std;

FileContacts::FileContacts(string ifilename)
{
    filename = ifilename;
}

bool FileContacts::isFileEmpty()
{
    return (contactData.peek() == ifstream::traits_type::eof());
}

string FileContacts::getFilename()
{
    return filename;
}

void FileContacts::printOneContactToFile(Contact& contact, fstream& outputDataStream)
{
    outputDataStream << contact.getId() << "|";
    outputDataStream << contact.getUserId() << "|";
    outputDataStream << contact.getName() << "|";
    outputDataStream << contact.getSurname() << "|";
    outputDataStream << contact.getPhoneNumber() << "|";
    outputDataStream << contact.getEmail() << "|";
    outputDataStream << contact.getAddress() <<  "|" << endl;
}

void FileContacts::addOneContactToContactFile(Contact newContact)
{
    contactData.open(filename, ios::out | ios::app);
    printOneContactToFile(newContact, contactData);
    contactData.close();
}

void FileContacts::updateContactsFile(vector <Contact> &contacts, int loggedUserId)
{
    fstream newContactData;
    string temporaryFilename = "newContactData.txt";
    string line;
    newContactData.open(temporaryFilename, ios::out);
    contactData.open(filename, ios::in);
    int contactsCount = contacts.size();
    int indexOfContact = 0;

    while (getline(contactData,line))
    {
        Contact oldContact = readOneContactData(line);
        if (oldContact.getUserId() != loggedUserId)
        {
            printOneContactToFile(oldContact, newContactData);
        }
        else
        {
            if (indexOfContact < contactsCount)
            {
                if (oldContact.getId() == contacts[indexOfContact].getId())
                {
                    printOneContactToFile(contacts[indexOfContact], newContactData);
                    indexOfContact++;
                }
            }
        }
    }
    while (indexOfContact < contactsCount)
    {
        printOneContactToFile(contacts[indexOfContact], newContactData);
        indexOfContact++;
    }


//    for (int i = 0; i < contactsCount; i++)
//    {
//        printOneContactToFile(contacts[i], newContactData);
//    }
//
//    while (getline(contactData,line))
//    {
//        Contact newContact = readOneContactData(line);
//        if (newContact.getUserId() != loggedUserId)
//        {
//            printOneContactToFile(newContact, newContactData);
//        }
//    }
    contactData.close();
    newContactData.close();
    remove(filename.c_str());
    rename(temporaryFilename.c_str(), filename.c_str());
}

Contact FileContacts::readOneContactData(string &line)
{
    string sign = "|";
    string name, surname, phoneNumber, email, address;
    int id, userId;
    int oldSignPosition = -1;
    int newSignPosition = line.find(sign, 0);
    int numberOfAttribute = 0;
    string attribute;

    while(newSignPosition != string::npos)
    {
        numberOfAttribute++;
        attribute = line.substr(oldSignPosition + 1, newSignPosition - oldSignPosition - 1);

        switch(numberOfAttribute)
        {
        case 1:
            id = conversion.string2int(attribute);
            break;
        case 2:
            userId = conversion.string2int(attribute);
            break;
        case 3:
            name = attribute;
            break;
        case 4:
            surname = attribute;
            break;
        case 5:
            phoneNumber = attribute;
            break;
        case 6:
            email = attribute;
            break;
        case 7:
            address = attribute;
            break;
        }
        oldSignPosition = newSignPosition;
        newSignPosition = line.find(sign,oldSignPosition+1);
    }

    Contact newContact(id, userId, name, surname, phoneNumber, email, address);
    return newContact;
}


vector <Contact> FileContacts::readContactsFromFile(int loggedUserId)
{
    vector <Contact> contacts;
    string line;
    contactData.open(filename, ios::in);

    if (!isFileEmpty())
    {
        while(getline(contactData, line))
        {
            Contact newContact = readOneContactData(line);
            if (newContact.getUserId() == loggedUserId)
            {
                contacts.push_back(newContact);
            }
        }
    }
    contactData.close();
    return contacts;
}
