#include "FileContacts.h"
//#include <algorithm>
//#include <cstdio>

FileContacts::FileContacts(std::string ifilename)
{
    filename = ifilename;
}

bool FileContacts::isFileEmpty()
{
    return (contactData.peek() == std::ifstream::traits_type::eof());
}

std::string FileContacts::getFilename()
{
    return filename;
}

void FileContacts::printOneContactToFile(Contact& contact, std::fstream& outputDataStream)
{
    outputDataStream << contact.getId() << "|";
    outputDataStream << contact.getUserId() << "|";
    outputDataStream << contact.getName() << "|";
    outputDataStream << contact.getSurname() << "|";
    outputDataStream << contact.getPhoneNumber() << "|";
    outputDataStream << contact.getEmail() << "|";
    outputDataStream << contact.getAddress() <<  "|" << std::endl;
}

void FileContacts::addOneContactToContactFile(Contact newContact)
{
    contactData.open(filename, std::ios::out | std::ios::app);
    printOneContactToFile(newContact, contactData);
    contactData.close();
}

void FileContacts::updateContactsFile(std::vector <Contact> &contacts, int loggedUserId)
{
    std::fstream newContactData;
    std::string temporaryFilename = "newContactData.txt";
    std::string line;
    newContactData.open(temporaryFilename, std::ios::out);
    contactData.open(filename, std::ios::in);
    int contactsCount = contacts.size();

    for (int i = 0; i < contactsCount; i++)
    {
        printOneContactToFile(contacts[i], newContactData);
    }

    while (getline(contactData,line))
    {
        Contact newContact = readOneContactData(line);
        if (newContact.getUserId() != loggedUserId)
        {
            printOneContactToFile(newContact, newContactData);
        }
    }
    contactData.close();
    newContactData.close();
    std::remove(filename.c_str());
    rename(temporaryFilename.c_str(), filename.c_str());
}

Contact FileContacts::readOneContactData(std::string &line)
{
    std::string sign = "|";
    std::string name, surname, phoneNumber, email, address;
    int id, userId;
    int oldSignPosition = -1;
    int newSignPosition = line.find(sign, 0);
    int numberOfAttribute = 0;
    std::string attribute;

    while(newSignPosition != std::string::npos)
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


std::vector <Contact> FileContacts::readContactsFromFile(int loggedUserId)
{
    std::vector <Contact> contacts;
    std::string line;
    contactData.open(filename, std::ios::in);

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
