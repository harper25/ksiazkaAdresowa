#ifndef CONTACT_H
#define CONTACT_H
#include <string>


class Contact
{
    public:
        Contact(int userId, std::string name, std::string surname,
                std::string phoneNumber, std::string email, std::string address);
        Contact(int id, int userId, std::string name, std::string surname,
                std::string phoneNumber, std::string email, std::string address);
        int getId();
        int getUserId();
        void setUserId(int);
        std::string getName();
        void setName(std::string);
        std::string getSurname();
        void setSurname(std::string);
        std::string getAddress();
        void setAddress(std::string);
        std::string getPhoneNumber();
        void setPhoneNumber(std::string);
        std::string getEmail();
        void setEmail(std::string);
        void showContact();

    protected:

    private:
        static int nextId;
        int id;
        int userId;
        std::string name;
        std::string surname;
        std::string address;
        std::string phoneNumber;
        std::string email;
        void setId(int);
};

#endif // CONTACT_H
