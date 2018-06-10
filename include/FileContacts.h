#ifndef FILECONTACTS_H
#define FILECONTACTS_H

#include <File.h>
#include "Contact.h"
#include "Conversion.h"
#include <string>
#include <fstream>
#include <vector>

class FileContacts : public File
{
    public:
        FileContacts(std::string);
        std::string getFilename();
        bool isFileEmpty();
        void updateContactsFile(std::vector <Contact> &contacts, int loggedUserId);
        void addOneContactToContactFile(Contact newContact);
        std::vector <Contact> readContactsFromFile(int loggedUserId);

    protected:

    private:
        std::string filename;
        std::fstream contactData;
        Contact readOneContactData(std::string&);
        Conversion conversion;
        void printOneContactToFile(Contact&, std::fstream&);

};

#endif // FILECONTACTS_H
